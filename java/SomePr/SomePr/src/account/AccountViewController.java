package account;

import connection.GetBestScore;
import connection.GetGlobalPosition;
import connection.StateOfauthentication;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.URL;
import java.text.ParseException;
import java.util.LinkedList;
import java.util.ResourceBundle;

public class AccountViewController implements Initializable {
    @FXML
    private AnchorPane root;
    @FXML
    private Label dayrecord;
    @FXML
    private Label monthrecord;
    @FXML
    private Label personalrecord;
    @FXML
    private Label worldrate;
    @FXML
    private Label GameName;

    private LinkedList<GameInformation> list = new LinkedList<>();
    private byte indexofgame=0;

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        GameInformation game1 = new GameInformation("Arithmetic",2);
        GameInformation game2 = new GameInformation("Flappy Bird",0);
        GameInformation game3 = new GameInformation("Memory Puzzle",1);
        list.add(game1);
        list.add(game2);
        list.add(game3);
        try {
            personalrecord.setText(String.valueOf(GetBestScore.getResults(2,"none").getScore()));
        } catch (Exception e) {
            personalrecord.setText("NONE");

            //e.printStackTrace();
        }
        try {
            dayrecord.setText(String.valueOf(GetBestScore.getResults(2,"day").getScore()));
        } catch (Exception e) {
           dayrecord.setText("NONE");

            e.printStackTrace();
        }
        try {
            monthrecord.setText(String.valueOf(GetBestScore.getResults(2, "month").getScore()));
        } catch (Exception e) {
            monthrecord.setText("NONE");

           // e.printStackTrace();
        }
        try {
            worldrate.setText(String.valueOf(GetGlobalPosition.getResults(2)));
        } catch (Exception e) {
            worldrate.setText("NONE");

           // e.printStackTrace();
        }

    }

    @FXML
    private void goback(ActionEvent event) throws IOException {
        Parent page1 = FXMLLoader.load(getClass().getResource("../mainMenu/sampleMenu.fxml"));
        Scene tableScene = new Scene(page1);
        Stage window = (Stage)((Node)event.getSource()).getScene().getWindow();
        window.setScene(tableScene);
        window.getScene().getStylesheets().add("css/GeomStyle.css");
        window.show();
    }

    @FXML
    private void nextgame(){
        indexofgame++;
        if(indexofgame==3)
            indexofgame=0;
        GameName.setText(list.get(indexofgame).getName());
        try {
            personalrecord.setText(String.valueOf(GetBestScore.getResults(list.get(indexofgame).getGame_type(),"none").getScore()));

        } catch (Exception e) {
            personalrecord.setText("NONE");
           // e.printStackTrace();
        }
        try {
            dayrecord.setText(String.valueOf(GetBestScore.getResults(list.get(indexofgame).getGame_type(),"day").getScore()));
        } catch (Exception e) {
            dayrecord.setText("NONE");
            e.printStackTrace();
        }
        try {
            monthrecord.setText(String.valueOf(GetBestScore.getResults(list.get(indexofgame).getGame_type(),"month").getScore()));
        } catch (Exception e) {
            monthrecord.setText("NONE");

            //e.printStackTrace();
        }
        try {
            worldrate.setText(String.valueOf(GetGlobalPosition.getResults(list.get(indexofgame).getGame_type())));
        } catch (Exception e) {
            worldrate.setText("NONE");

            //e.printStackTrace();
        }
    }
}
