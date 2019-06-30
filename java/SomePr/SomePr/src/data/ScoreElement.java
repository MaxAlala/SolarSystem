package data;

import java.util.Date;

public class ScoreElement {
    int score;
    Date date;
    int gameName; // 0 - flappy, 1 - arithm, 2 - memory
    String owner;

    public ScoreElement() {

    }

    public ScoreElement(int score, Date date, int gameName, String owner) {
        this.score = score;
        this.date = date;
        this.gameName = gameName;
        this.owner = owner;
    }

    @Override
    public String toString() {
        return "ScoreElement{" +
                "score=" + score +
                ", date=" + date +
                ", gameName=" + gameName +
                ", owner='" + owner + '\'' +
                '}';
    }

    public String getOwner() {
        return owner;
    }

    public void setOwner(String owner) {
        this.owner = owner;
    }

    public int getScore() {
        return score;
    }

    public void setScore(int score) {
        this.score = score;
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public int getGameName() {
        return gameName;
    }

    public void setGameName(int gameName) {
        this.gameName = gameName;
    }
}
