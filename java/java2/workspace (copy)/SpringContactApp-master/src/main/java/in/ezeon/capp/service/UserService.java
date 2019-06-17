package in.ezeon.capp.service;

import in.ezeon.capp.domain.worker;
import in.ezeon.capp.exception.UserBlockedException;
import java.util.List;

/**
 *
 * @author Vikram
 */
public interface UserService {
    
    public static final Integer LOGIN_STATUS_ACTIVE=1;
    public static final Integer LOGIN_STATUS_BLOCKED=2;
    
    public static final Integer ROLE_ADMIN=1;
    public static final Integer ROLE_USER=2;
    
    
    /**
     * The method handle the worker registration task.
     * @param u the new worker detail as worker Object.
     */
    public void register(worker u);
    
    /**
     * The method handles login operation(authentication) using given credentials,
     * it returns worker object when success and null when failed. 
     * When worker account is blocked an exception will be thrown by this method.
     * @param loginName
     * @param password
     * @return 
     * @throws in.ezeon.capp.exception.UserBlockedException When worker account is  blocked.
     */
    public worker login(String loginName, String password) throws UserBlockedException;
    
    /**
     * Call this method to get list of registered users.
     * @return 
     */
    public List<worker> getUserList();
    
    /**
     * This method change the worker login status for details passed as argument.
     * @param userId
     * @param loginStatus 
     */
    public void changeLoginStatus(Integer userId, Integer loginStatus);    
    
    /**
     * Check the username availability.
     * @param username
     * @return 
     */
    public Boolean isUsernameExist(String username);
   
}
