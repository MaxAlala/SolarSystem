package mainMenu;

import connection.StateOfauthentication;
import flappybird.FlappyBird;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.stage.Stage;

import java.awt.*;
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

public class ControllerMenu implements Initializable {

    @FXML
    private Label login;

    @FXML
    private Button account;

//    ControllerMenu(){
//        login.setText(StateOfauthentication.getLogin());
//    }
    @FXML
    private void BAction(ActionEvent event) throws IOException {

        Parent page = FXMLLoader.load(getClass().getResource("../account/AccountView.fxml"));
        Scene tableScene = new Scene(page);
        Stage window = (Stage)((Node)event.getSource()).getScene().getWindow();
        window.setScene(tableScene);
        window.getScene().getStylesheets().add("css/GeomStyle.css");
        window.show();
    }

    @FXML
    private void outAction(ActionEvent event) throws IOException {
        Parent page = FXMLLoader.load(getClass().getResource("../starter/sampleStarter.fxml"));
        Scene tableScene = new Scene(page);
        Stage window = (Stage)((Node)event.getSource()).getScene().getWindow();
        window.setScene(tableScene);
        window.getScene().getStylesheets().add("css/GeomStyle.css");
        window.show();
    }

    @FXML
    private void FlappyAction(ActionEvent event) throws Exception {

        Parent page = FXMLLoader.load(getClass().getResource("../flappybird/FlappyGameMenu.fxml"));
        Scene tableScene = new Scene(page);
        Stage window = (Stage) ((Node) event.getSource()).getScene().getWindow();
        window.setScene(tableScene);
        window.getScene().getStylesheets().add("css/GeomStyle.css");
        window.show();
    }

    @FXML
    private void CountAction(ActionEvent event) throws Exception {

        Parent page = FXMLLoader.load(getClass().getResource("../countGame/CountGameMenu.fxml"));
        Scene tableScene = new Scene(page);
        Stage window = (Stage) ((Node) event.getSource()).getScene().getWindow();
        window.setScene(tableScene);
        window.getScene().getStylesheets().add("css/GeomStyle.css");
        window.show();
    }

    @FXML
    private void MemoryPuzzle(ActionEvent event) throws Exception{

        Parent page = FXMLLoader.load(getClass().getResource("../memorypuzzle/MemoryPuzzleMenu.fxml"));
        Scene tableScene = new Scene(page);
        Stage window = (Stage)((Node)event.getSource()).getScene().getWindow();
        window.setScene(tableScene);
        window.getScene().getStylesheets().add("css/GeomStyle.css");
        window.show();
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        login.setText(StateOfauthentication.getLogin());
    }
}
