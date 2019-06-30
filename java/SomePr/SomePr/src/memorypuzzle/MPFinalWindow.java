package memorypuzzle;

import javafx.event.Event;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.text.Font;
import javafx.stage.Stage;

import javafx.scene.input.MouseEvent;

import java.io.IOException;



public class MPFinalWindow {
    public static int scores;
    @FXML
    public Label scoresview;
    @FXML
    public void onStart(){
        scoresview.setText(String.valueOf(scores));
    }

    public static void setScores(int scores) {
        MPFinalWindow.scores = scores;
    }

    @FXML
    private void goback(Event event) throws IOException {
        Parent page1 = FXMLLoader.load(getClass().getResource("../memorypuzzle/MemoryPuzzleMenu.fxml"));
        Scene tableScene = new Scene(page1);
        Stage window = (Stage)((Node)event.getSource()).getScene().getWindow();
        window.setScene(tableScene);
        window.getScene().getStylesheets().add("css/GeomStyle.css");
        window.show();
    }
}
