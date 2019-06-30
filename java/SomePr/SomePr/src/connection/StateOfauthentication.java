package connection;

public class StateOfauthentication {
    public static boolean isSignedUp;
    private static String login;
    private static String password;

    public static boolean isIsSignedUp() {
        return isSignedUp;
    }

    public static void setIsSignedUp(boolean isSignedUp) {
        StateOfauthentication.isSignedUp = isSignedUp;
    }

    public static  String getLogin() {
        return login;
    }

    public static void setLogin(String login) {
        StateOfauthentication.login = login;
    }

    public static String getPassword() {
        return password;
    }

    public static void setPassword(String password) {
        StateOfauthentication.password = password;
    }
}
