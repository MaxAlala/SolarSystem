package in.ezeon.capp.test;

import in.ezeon.capp.config.SpringRootConfig;
import in.ezeon.capp.dao.UserDAO;
import in.ezeon.capp.domain.worker;
import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

/**
 *
 * @author Vikram
 */
public class TestUserDAOUpdate {
    public static void main(String[] args) {
        ApplicationContext ctx = new AnnotationConfigApplicationContext(SpringRootConfig.class);
        UserDAO userDAO=ctx.getBean(UserDAO.class);
        //TODO: the worker details will be taken from Update worker Profile Page
        worker u=new worker();
        u.setUserId(2);
        u.setName("Amit Sinha");
        u.setPhone("9303580884");
        u.setEmail("amit.sinha@ezeon.net");
        u.setAddress("Mumbai, MS");        
        u.setRole(1);//Admin Role 
        u.setLoginStatus(1); //Active
        
        userDAO.update(u);
        System.out.println("--------Data Updated------");
    }    
}
