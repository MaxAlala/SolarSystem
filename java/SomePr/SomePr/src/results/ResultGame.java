package results;

public class ResultGame {
    private static String GameName;
    private static String Path;
    private static String MenuPath;
    private static int gametype;

    public static int getGametype() {
        return gametype;
    }

    public static void setGametype(int gametype) {
        ResultGame.gametype = gametype;
    }

    public static String getMenuPath() {
        return MenuPath;
    }

    public static void setMenuPath(String menuPath) {
        MenuPath = menuPath;
    }

    public static String getGameName() {
        return GameName;
    }

    public static void setGameName(String gameName) {
        GameName = gameName;
    }

    public static String getPath() {
        return Path;
    }

    public static void setPath(String path) {
        Path = path;
    }
}
