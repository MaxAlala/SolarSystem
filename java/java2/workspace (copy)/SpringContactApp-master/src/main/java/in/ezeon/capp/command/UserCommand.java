package in.ezeon.capp.command;

import in.ezeon.capp.domain.worker;

/**
 *
 * @author Vikram
 */
public class UserCommand {
    worker worker;
    //TODO: more fieds if required

    public worker getUser() {
        return worker;
    }

    public void setUser(worker worker) {
        this.worker = worker;
    }
    
    
}
