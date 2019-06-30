
package starter;

import table.impls.CollectionAddressBook;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;


public class Starter extends Application {
    public static CollectionAddressBook addressBookImpl = new CollectionAddressBook();

    public void start(Stage stage) throws Exception {
        Parent root = FXMLLoader.load(getClass().getResource("sampleStarter.fxml"));

        Scene scene = new Scene(root);
        stage.setScene(scene);
        stage.setResizable(false);
        stage.sizeToScene();
        stage.getScene().getStylesheets().add("css/GeomStyle.css");
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }

}
