package account;

public class GameInformation {
    private String name;
    private int game_type;

    public GameInformation(String name, int game_type) {
        this.name = name;
        this.game_type = game_type;
    }

    public int getGame_type() {

        return game_type;
    }

    public void setGame_type(int game_type) {
        this.game_type = game_type;
    }
    /*
    что-то еще
     */

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}
