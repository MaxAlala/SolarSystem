package starter;

import com.jfoenix.controls.JFXPasswordField;
import com.jfoenix.controls.JFXTextField;
import connection.SignIn;
import connection.SignUp;
import javafx.event.ActionEvent;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.stage.Stage;

import javafx.scene.Node;

public class ControllerStarter {

    @FXML
    private JFXPasswordField password;

    @FXML
    private JFXTextField email;

    @FXML
    Label badPassword;

    @FXML
    private void handleButtonAction(ActionEvent event) throws IOException {

//            Parent page = FXMLLoader.load(getClass().getResource("../mainMenu/sampleMenu.fxml"));
//            Scene tableScene = new Scene(page);
//            Stage window = (Stage)((Node)event.getSource()).getScene().getWindow();
//            window.setScene(tableScene);
//            window.show();
    }

    @FXML
    private void signUp(ActionEvent event) throws IOException {
        if (email.getText().equals("") || password.getText().equals("")) {
            badPassword.setText("fill all fields");
        } else {
            boolean wasSuccess = SignUp.signUp(email.getText(), password.getText());
            System.out.println(wasSuccess);
//            if (wasSuccess) {
                Parent page = FXMLLoader.load(getClass().getResource("../mainMenu/sampleMenu.fxml"));
                Scene tableScene = new Scene(page);
                Stage window = (Stage) ((Node) event.getSource()).getScene().getWindow();
                window.setScene(tableScene);
                window.getScene().getStylesheets().add("css/GeomStyle.css");
                window.show();
//            } else
                badPassword.setText("something went wrong!");
        }
    }

    @FXML
    private void signIn(ActionEvent event) throws IOException {
        if (email.getText().equals("") || password.getText().equals("")) {
            badPassword.setText("fill all fields");
        } else {

            boolean wasSuccess = SignIn.signIn(email.getText(), password.getText());

            if (wasSuccess) {
                Parent page = FXMLLoader.load(getClass().getResource("../mainMenu/sampleMenu.fxml"));
                Scene tableScene = new Scene(page);
                Stage window = (Stage) ((Node) event.getSource()).getScene().getWindow();
                window.setScene(tableScene);
                window.getScene().getStylesheets().add("css/GeomStyle.css");
                window.show();
            } else
                badPassword.setText("something went wrong!");

        }


    }

}
