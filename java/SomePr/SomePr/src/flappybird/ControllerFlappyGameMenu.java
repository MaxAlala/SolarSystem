package flappybird;

import countGame.CountGame;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import results.ResultGame;

import java.io.IOException;


public class ControllerFlappyGameMenu {
    @FXML
    private void MenuAction(ActionEvent event) throws IOException {
        Parent page = FXMLLoader.load(getClass().getResource("../mainMenu/sampleMenu.fxml"));
        Scene tableScene = new Scene(page);
        Stage window = (Stage) ((Node) event.getSource()).getScene().getWindow();
        window.setScene(tableScene);
        window.getScene().getStylesheets().add("css/GeomStyle.css");
        window.show();
    }

    @FXML
    private void scoreAction(ActionEvent event) throws IOException {
        ResultGame.setGameName("Flappy Bird");
        ResultGame.setPath("flappyScore");
        ResultGame.setMenuPath("../flappybird/FlappyGameMenu.fxml");
        ResultGame.setGametype(0);
        Parent page = FXMLLoader.load(getClass().getResource("../results/Results.fxml"));
        Scene tableScene = new Scene(page);
        Stage window = (Stage) ((Node) event.getSource()).getScene().getWindow();
        window.setScene(tableScene);
        window.getScene().getStylesheets().add("css/cssBlue.css");
        window.show();
    }

    @FXML
    private void startAction(ActionEvent event) throws IOException {
        Stage window = (Stage)((Node)event.getSource()).getScene().getWindow();
        FlappyBird game = new FlappyBird();
        game.start(window);
    }

}
