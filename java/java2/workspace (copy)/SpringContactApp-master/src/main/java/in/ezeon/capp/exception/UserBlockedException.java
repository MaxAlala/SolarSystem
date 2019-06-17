package in.ezeon.capp.exception;

/**
 *
 * @author Vikram
 */
public class UserBlockedException extends Exception{
    /**
     * Creates worker object without error description.
     */
    public UserBlockedException() {
    }
    /**
     * Creates worker object with error description.
     */
    public UserBlockedException(String errDesc) {
        super(errDesc);
    }    
}
