package in.ezeon.capp.controller;

import in.ezeon.capp.command.LoginCommand;
import in.ezeon.capp.command.UserCommand;
import in.ezeon.capp.domain.worker;
import in.ezeon.capp.exception.UserBlockedException;
import in.ezeon.capp.service.UserService;
import javax.servlet.http.HttpSession;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.DuplicateKeyException;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

/**
 *
 * @author Vikram
 */
@Controller
public class UserController {

    @Autowired
    private UserService userService;

    @RequestMapping(value = {"/", "/index"})
    public String index(Model m) {
        m.addAttribute("command", new LoginCommand());
        return "index"; //JSP - /WEB-INF/view/index.jsp
    }

    @RequestMapping(value = "/login", method = RequestMethod.POST)
    public String handleLogin(@ModelAttribute("command") LoginCommand cmd, Model m, HttpSession session) {
        try {
            worker loggedInUser = userService.login(cmd.getLoginName(), cmd.getPassword());
            if (loggedInUser == null) {
                //FAILED
                //add error message and go back to login-form
                m.addAttribute("err", "Login Failed! Enter valid credentials.");
                return "index";//JSP - Login FORM
            } else //SUCCESS
            //check the role and redirect to a appropriate dashboard 
            {
                if (loggedInUser.getRole().equals(UserService.ROLE_ADMIN)) {
                    //add worker detail in session (assign session to logged in worker)
                    addUserInSession(loggedInUser, session);
                    return "redirect:admin/dashboard";
                } else if (loggedInUser.getRole().equals(UserService.ROLE_USER)) {
                    //add worker detail in session (assign session to logged in worker)
                    addUserInSession(loggedInUser, session);
                    return "redirect:worker/dashboard";
                } else {
                    //add error message and go back to login-form
                    m.addAttribute("err", "Invalid worker ROLE");
                    return "index";//JSP - Login FORM
                }
            }
        } catch (UserBlockedException ex) {
            //add error message and go back to login-form
            m.addAttribute("err", ex.getMessage());
            return "index";//JSP - Login FORM
        }
    }

    @RequestMapping(value = "/logout")
    public String logout(HttpSession session) {
        session.invalidate();
        return "redirect:index?act=lo";
    }

    @RequestMapping(value = "/worker/dashboard")
    public String userDashboard() {
        return "dashboard_user"; //JSP
    }

    @RequestMapping(value = "/admin/dashboard")
    public String adminDashboard() {
        return "dashboard_admin"; //JSP
    }

    @RequestMapping(value = "/admin/users")
    public String getUserList(Model m) {
        m.addAttribute("userList", userService.getUserList());
        return "users"; //JSP
    }

    @RequestMapping(value = "/reg_form")
    public String registrationForm(Model m) {
        UserCommand cmd = new UserCommand();
        m.addAttribute("command", cmd);
        return "reg_form";//JSP
    }

    @RequestMapping(value = "/register")
    public String registerUser(@ModelAttribute("command") UserCommand cmd, Model m) {
        try {
            worker worker = cmd.getUser();
            worker.setRole(UserService.ROLE_USER);
            worker.setLoginStatus(UserService.LOGIN_STATUS_ACTIVE);
            userService.register(worker);
            return "redirect:index?act=reg"; //Login Page
        } catch (DuplicateKeyException e) {
            e.printStackTrace();
            m.addAttribute("err", "Username is already registered. Please select another username.");
            return "reg_form";//JSP
        }
    }

    private void addUserInSession(worker u, HttpSession session) {
        session.setAttribute("worker", u);
        session.setAttribute("userId", u.getUserId());
        session.setAttribute("role", u.getRole());
    }

    @RequestMapping(value = "/admin/change_status")
    @ResponseBody
    public String changeLoginStatus(@RequestParam Integer userId, @RequestParam Integer loginStatus) {
        try {
            userService.changeLoginStatus(userId, loginStatus);
            return "SUCCESS: Status Changed";
        } catch (Exception e) {
            e.printStackTrace();
            return "ERROR: Unable to Change Status";
        }
    }
    
    @RequestMapping(value = "/check_avail")
    @ResponseBody
    public String checkAvailability(@RequestParam String username) {
        if(userService.isUsernameExist(username)){
            return "This username is already taken. Choose another name";
        }else{
            return "Yes! You can take this";
        }
    }
    
}
