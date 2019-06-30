package flappybird;

import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.Pane;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.stage.Stage;

import java.io.IOException;

public class ScoreLabel extends Pane {

    Text status = new Text("Result: 0");

    public ScoreLabel(double x, double y) {

        setPrefHeight(200); // 100
        setPrefWidth(300);  // 300
        setTranslateX(x - 310);//310
        setTranslateY(y + 10);
        setStyle("-fx-background-color: #CCC;"
                + "-fx-background-radius:20px");
        setOpacity(0.8);
        status.setTranslateY(60);
        status.setTranslateX(70);
//        Button toMenu = new Button("Wish go to menu&");
//        toMenu.setStyle("-fx-background-color: #CCC;"
//                + "-fx-background-radius:20px");
//        getChildren().add(toMenu);
        getChildren().addAll(status);
        status.setFont(Font.font(Font.getDefault().getName(), FontWeight.BOLD, 22));
//        status.setFill(new Color(107 / 255.0, 162 / 255.0, 252 / 255.0, 1.0));
    }

    public void addMenuButton() {
        Button toMenu = new Button("wish go to the menu?");
        toMenu.setFont(Font.font(Font.getDefault().getName(), FontWeight.BOLD, 32));
        toMenu.setStyle("-fx-background-color: #CCC;"
                + "-fx-background-radius:20px");

        toMenu.setLayoutX(20);
        toMenu.setLayoutY(120);

        toMenu.setOnAction(e -> {

            Parent page1 = null;
            try {
                page1 = FXMLLoader.load(getClass().getResource("../flappybird/FlappyGameMenu.fxml"));
            } catch (IOException e1) {
                e1.printStackTrace();
            }
            Scene tableScene = new Scene(page1);
            Stage window = (Stage) ((Node) e.getSource()).getScene().getWindow();
            window.setScene(tableScene);
            window.getScene().getStylesheets().add("css/GeomStyle.css");
            window.show();
        });

        getChildren().add(toMenu);

    }

    public void setText(String message) {
        status.setText(message);
    }
}

class GameOverLabel extends ScoreLabel {

    public GameOverLabel(double x, double y) {
        super(x, y);
        setPrefWidth(400);
        setTranslateX(x - 150);
        status.setTranslateX(100);
        addMenuButton();
    }

}

class StartLabel extends ScoreLabel {
    public StartLabel(double x, double y) {
        super(x, y);
        setPrefWidth(400);
        setTranslateX(x - 150);
        status.setTranslateX(100);
        addMenuButton();
    }
}
