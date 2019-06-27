package com.example.sweater.controller;

import com.example.sweater.domain.*;

import com.example.sweater.repos.GroupRepo;
import com.example.sweater.repos.PersonalMessageRepo;
import com.example.sweater.repos.SkillRepo;
import com.example.sweater.service.UserService;
import com.google.common.collect.Sets;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.security.core.annotation.AuthenticationPrincipal;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import javax.validation.Valid;
import java.io.File;
import java.io.IOException;
import java.util.*;

@Controller
@RequestMapping("/user")
public class UserController {

    @Autowired
    private UserService userService;

    @Autowired
    private GroupRepo groupRepo;

    @Autowired
    private SkillRepo skillRepo;

    @Autowired
    private PersonalMessageRepo personalMessageRepo;

    @Value("${upload.path}")
    private String uploadPath;

    @GetMapping("mymessages")
    public String mymessages(
//            @PathVariable() User user,
            @AuthenticationPrincipal User cur_user,
            Model model)

    {
        List<PersonalMessage> list = (List<PersonalMessage>) personalMessageRepo.findAllByAuthor(cur_user);
        List<PersonalMessage> list2 = (List<PersonalMessage>) personalMessageRepo.findAllByReceiver(cur_user);

        model.addAttribute("fromme",list);
        model.addAttribute("tome",list2);

        return "mymessages";
    }
    @GetMapping("getalluser")
    public String getalluser(
            @RequestParam(required = false, defaultValue = "") String filter,
            @AuthenticationPrincipal User cur_user,
            Model model) {
        List<User> users = userService.findAll();
        model.addAttribute("groups", groupRepo.findGroupsByAuthor(cur_user));
        model.addAttribute("users",users);
        return "allusers";
    }

    @GetMapping("searchbyusername")
    public String searchbyusername(
            @RequestParam(required = false, defaultValue = "") String filter,
            @AuthenticationPrincipal User cur_user,
            Model model) {
        System.out.println(filter + " Filter!");
        List<User> users = userService.findAllByUsername(filter);
        model.addAttribute("users",users);
        model.addAttribute("filter",filter);
        return "allusers";
    }

    @GetMapping("searchbyskill")
    public String searchbyskill(
            @RequestParam(required = false, defaultValue = "") String filter,
            @AuthenticationPrincipal User cur_user,
            Model model) {
            Skill sk = skillRepo.findSkillByName(filter);
            if(sk == null){ model.addAttribute("users",null);}else{
        List<User> users = userService.findUserBySkill(sk.getId());
        model.addAttribute("users",users);
                model.addAttribute("filter",filter);
            }
        return "allusers";
    }

    @GetMapping("sendmessage/{user}")
    public String sendmessage(
            @PathVariable() User user,
            @AuthenticationPrincipal User cur_user,
            Model model) {
            model.addAttribute("receiver",user);

        return "sendmessage";
    }

    @PostMapping("sendmessage")
    public String sendmessage(
            @AuthenticationPrincipal User cur_user,
            @Valid PersonalMessage message,
            @RequestParam(value = "receiver") User user,
            BindingResult bindingResult,
            Model model
    ) throws IOException {
        message.setAuthor(cur_user);
        System.out.println(user.getUsername() + " username!");
        message.setReceiver(user);


        if (bindingResult.hasErrors()) {
            Map<String, String> errorsMap = ControllerUtils.getErrors(bindingResult);
            model.mergeAttributes(errorsMap);
            model.addAttribute("message", message);
        } else {
            model.addAttribute("message", null);
            personalMessageRepo.save(message);
        }


        Iterable<Skill> groups = skillRepo.findAll();
        model.addAttribute("skill", groups);
        return "redirect:/user/profile/";
    }

//    @PostMapping("/main/{user}")
//    public String add2(
//            @PathVariable User user,
//            @RequestParam("file") MultipartFile file,
//            @AuthenticationPrincipal User cur_user,
//            @Valid Message message,
//            BindingResult bindingResult,
//            Model model
//    ) throws IOException {
//        System.out.println("i am HEEEEEEEEEEEEEEEEEEEEEEEEREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE3339999");
//        return getString(file, cur_user, message, bindingResult, model, user);
//    }
//
    @PostMapping("addtogroup")
    public String addtogroup(
            @RequestParam(value = "group") Group group,
            @RequestParam(value = "user") User user,
            @AuthenticationPrincipal User cur_user
    ) throws IOException {
        group.getParticipants().add(user);
    groupRepo.save(group);
        return "redirect:/user/addtogroup/"+user.getId();
    }

    @GetMapping("addtogroup/{user}")
    public String addtogroup(
            @PathVariable User user,
            @AuthenticationPrincipal User cur_user,
            Model model
    ) throws IOException {

//        List list = new ArrayList(cur_user.getGroups());
        List list = (List) groupRepo.findUsersGroup(cur_user.getId());
//        System.out.println(list.size() + " ls");
//        System.out.println(cur_user.getGroups().size() + " ls");
        list.removeAll((List)groupRepo.findUsersGroup(user.getId()));
        List list2 = (List) groupRepo.findUsersGroup(cur_user.getId());
        list2.retainAll((List)groupRepo.findUsersGroup(user.getId()));
        System.out.println("list2 = " + list2 + " list1 = " + list);
//        System.out.println(cur_user.getGroups().size());
        model.addAttribute("groups", list);
        model.addAttribute("groupstodelete", list2);
        return "addtogroup";

    }

    @PostMapping("deleteskill")
    public String deleteskill(
            @RequestParam(value = "skill") Skill skill,
            @AuthenticationPrincipal User cur_user
    ) throws IOException {
        skill.getParticipants().remove(cur_user);
        skillRepo.save(skill);
        return "redirect:/user/profile";
    }

    @PostMapping("addskill")
    public String addskill(
            @RequestParam(value = "skill") Skill skill,
//            @RequestParam(value = "user") User user,
            @AuthenticationPrincipal User cur_user
    ) throws IOException {
        System.out.println(skill+ "////////////////////!@#");
        skill.getParticipants().add(cur_user);
//        cur_user.getSkills().add(skill);
//        userService.save(cur_user);
//        group.getParticipants().add(user);
        skillRepo.save(skill);
        return "redirect:/user/profile";
    }

    @PostMapping("deletefromgroup")
    public String deletefromgroup(
            @RequestParam(value = "group") Group group,
            @RequestParam(value = "user") User user,
            @AuthenticationPrincipal User cur_user
    ) throws IOException {

        group.getParticipants().remove(user);
        groupRepo.save(group);
        return "redirect:/user/addtogroup/"+user.getId();
    }
    @PostMapping("createskill")
    public String createskill(
            @AuthenticationPrincipal User cur_user,
            @Valid Skill skill,
            BindingResult bindingResult,
            Model model
    ) throws IOException {
        skill.setAuthor(cur_user);


        if (bindingResult.hasErrors()) {
            Map<String, String> errorsMap = ControllerUtils.getErrors(bindingResult);
            model.mergeAttributes(errorsMap);
            model.addAttribute("skill", skill);
        } else {
            model.addAttribute("skill", null);
            skillRepo.save(skill);
        }
        Iterable<Skill> groups = skillRepo.findAll();
        model.addAttribute("skill", groups);
        return "redirect:/user/profile/";
    }
    @PostMapping("creategroup")
    public String creategroup(
            @RequestParam("file") MultipartFile file,
            @AuthenticationPrincipal User cur_user,
            @Valid Group group,
            BindingResult bindingResult,
            Model model
    ) throws IOException {
//        System.out.println("i am HEEEEEEEEEEEEEEEEEEEEEEEEREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE333");
        group.getParticipants().add(cur_user);
        groupRepo.save(group);
    return getString(file, cur_user, group, bindingResult, model, null);
    }

    private  String getString(@RequestParam("file") MultipartFile file, @AuthenticationPrincipal User cur_user, @Valid Group group, BindingResult bindingResult, Model model, User user) throws IOException {
        group.setAuthor(cur_user);
        if (bindingResult.hasErrors()) {
            Map<String, String> errorsMap = ControllerUtils.getErrors(bindingResult);
            model.mergeAttributes(errorsMap);
            model.addAttribute("group", group);
            System.out.println("/////////222");
        } else {


            if (file != null && !file.getOriginalFilename().isEmpty()) {
                File uploadDir = new File(uploadPath);

                if (!uploadDir.exists()) {
                    uploadDir.mkdir();
                }

                String uuidFile = UUID.randomUUID().toString();
                String resultFileName = uuidFile + "." + file.getOriginalFilename();
                System.out.println(uploadPath + "/////////");
                System.out.println(resultFileName + "/////////");

                file.transferTo(new File(uploadPath + "\\" + resultFileName));
                group.setFilename(resultFileName);
            }
            System.out.println( "/////////333");
            model.addAttribute("group", null);
            System.out.println(group.getFilename());
            groupRepo.save(group);
        }

        Iterable<Group> groups = groupRepo.findAll();
        model.addAttribute("group", groups);
        if(user != null) return "redirect:/user/profile/"; else
            return "redirect:/user/profile";
    }


//    @PostMapping("profile")
//    public String updateGroup(
//            @AuthenticationPrincipal User user,
//            @RequestParam String password,
//            @RequestParam String email
//    ) {
//        userService.updateProfile(user, password, email);
//
//        return "redirect:/user/profile";
//    }


    @PreAuthorize("hasAuthority('ADMIN')")
    @GetMapping
    public String userList(Model model) {
        model.addAttribute("users", userService.findAll());

        return "userList";
    }

    @PreAuthorize("hasAuthority('ADMIN')")
    @GetMapping("{user}")
    public String userEditForm(@PathVariable User user, Model model) {
        model.addAttribute("user", user);
        model.addAttribute("roles", Role.values());

        return "userEdit";
    }

    @PreAuthorize("hasAuthority('ADMIN')")
    @PostMapping
    public String userSave(
            @RequestParam String username,
            @RequestParam Map<String, String> form,
            @RequestParam("userId") User user
    ) {
        userService.saveUser(user, username, form);

        return "redirect:/user";
    }

    @GetMapping("profile")
    public String getProfile(Model model, @AuthenticationPrincipal User user) {
        model.addAttribute("username", user.getUsername());
//        model.addAttribute("user", user);
//        Iterable<Group> it = groupRepo.findAll();
//        Iterable<Group> authors = groupRepo.findGroupsByAuthor(user);
//        Set<Group> set = Sets.newHashSet(it);
//
//        Iterable<Skill> it2 = skillRepo.findAll();
//        Iterable<Skill> authors2 = skillRepo.findSkillByAuthor(user);
//        Set<Skill> setS = Sets.newHashSet(it2);
//
//
//        Set<Group> ag = Sets.newHashSet(authors);
//        Set<Skill> ag2 = Sets.newHashSet(authors2);
//        set.removeAll(ag);
//
//        Iterable<Group> i1 = set;
//        setS.removeAll(ag2);
//        Iterable<Skill> i2 = setS;


        model.addAttribute("email", user.getEmail());
        model.addAttribute("username", user.getUsername());
        model.addAttribute("groups",groupRepo.findnotUsersGroup(user.getId()));
        model.addAttribute("skills",skillRepo.findnotUsersSkills(user.getId()));
        model.addAttribute("yourgroups",groupRepo.findUsersGroup(user.getId()));
        model.addAttribute("yourskills",skillRepo.findUsersSkills(user.getId()));
        return "profile";
    }

    @PostMapping("profile")
    public String updateProfile(
            @AuthenticationPrincipal User user,
            @RequestParam String password,
            @RequestParam String email,
            @RequestParam String aboutme
    ) {
        userService.updateProfile(user, password, email);
        user.setAboutme(aboutme);
        userService.save(user);
        return "redirect:/user/profile";
    }

    @GetMapping("subscribe/{user}")
    public String subscribe(
            @AuthenticationPrincipal User currentUser,
            @PathVariable User user
    ) {
        userService.subscribe(currentUser, user);
        return "redirect:/main/" + user.getId();
    }

    @GetMapping("unsubscribe/{user}")
    public String unsubscribe(
            @AuthenticationPrincipal User currentUser,
            @PathVariable User user
    ) {
        userService.unsubscribe(currentUser, user);

        return "redirect:/main/" + user.getId();
    }

    @GetMapping("{type}/{user}/list")
    public String userList(
            Model model,
            @PathVariable User user,
            @PathVariable String type
    ) {
        model.addAttribute("userChannel", user);
        model.addAttribute("type", type);

        if ("subscriptions".equals(type)) {
            model.addAttribute("users", user.getSubscriptions());
        } else {
            model.addAttribute("users", user.getSubscribers());
        }
        return "subscriptions";
    }
}

