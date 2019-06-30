package memorypuzzle;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import results.ResultGame;

import java.io.IOException;

public class MenuController {
    @FXML
    private void start(ActionEvent event) throws Exception{
        Parent page1 = FXMLLoader.load(getClass().getResource("../memorypuzzle/MPGame.fxml"));
        Scene tableScene = new Scene(page1);
        Stage window = (Stage)((Node)event.getSource()).getScene().getWindow();
        window.setScene(tableScene);
        window.getScene().getStylesheets().add("css/GeomStyle.css");
        window.show();
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
    private void scoreAction(ActionEvent event) throws IOException {
        ResultGame.setGameName("Memory Puzzle");
        ResultGame.setPath("memoryPuzzleScore");
        ResultGame.setMenuPath("../memorypuzzle/MemoryPuzzleMenu.fxml");
        ResultGame.setGametype(1);
        Parent page = FXMLLoader.load(getClass().getResource("../results/Results.fxml"));
        Scene tableScene = new Scene(page);
        Stage window = (Stage) ((Node) event.getSource()).getScene().getWindow();
        window.setScene(tableScene);
        window.getScene().getStylesheets().add("css/cssGreen.css");
        window.show();
    }
}
