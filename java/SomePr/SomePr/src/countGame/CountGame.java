package countGame;

import connection.PostResults;
import connection.StateOfauthentication;
import data.DataStore;
import data.ScoreElement;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.stage.Stage;
import javafx.util.Duration;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;
import java.util.Random;

public class CountGame {
    private int scores;
    private int a;
    private int b;
    private String signs[] = {"+", "*", "-", "/"};
    private boolean isStarted = false;
    private int amount;

    @FXML
    private Button startButton;
    @FXML
    private Button restartButton;
    @FXML
    private Label numberA;

    @FXML
    private Label numberB;
    @FXML
    private Label score;
    @FXML
    private Label time;
    @FXML
    private Label yourScore;
    @FXML
    private TextField answer;
    @FXML
    private Label sign;

    @FXML
    public void start(Stage stage) throws IOException {
        Parent page = FXMLLoader.load(getClass().getResource("../countGame/sampleCountGame.fxml"));
        Scene tableScene = new Scene(page);
        stage.setScene(tableScene);
        stage.getScene().getStylesheets().add("css/GeomStyle.css");
        stage.show();
    }

    @FXML
    public void toMenu(ActionEvent event) throws IOException {
        Parent page = FXMLLoader.load(getClass().getResource("../countGame/CountGameMenu.fxml"));
        Scene tableScene = new Scene(page);
        Stage window = (Stage) ((Node) event.getSource()).getScene().getWindow();
        window.setScene(tableScene);
        window.getScene().getStylesheets().add("css/GeomStyle.css");
        window.show();
    }

    @FXML
    private void restartAction(ActionEvent event) throws IOException {
        Stage window = (Stage) ((Node) event.getSource()).getScene().getWindow();
        CountGame game = new CountGame();
        game.start(window);
    }

    @FXML
    public void enterAction(KeyEvent keyEvent) {
        if (keyEvent.getCode() == KeyCode.ENTER && isStarted && !this.answer.getText().equals("")) {
            amount++;
            int rightAnswer = 0;
            switch (sign.getText()) {
                case "+":
                    rightAnswer = a + b;
                    break;
                case "*":
                    rightAnswer = a * b;
                    break;
                case "-":
                    rightAnswer = a - b;
                    break;
                case "/":
                    rightAnswer = a / b;
                    break;
            }
            if (answer.getText().equals("" + rightAnswer)) {
                scores++;
            }
            this.score.setText(scores + "/" + amount);
            this.answer.setText("");
            int i = new Random().nextInt(4);
            this.sign.setText(signs[i]);
            full(signs[i]);
        }
    }

    @FXML
    public void startAction() {
        answer.requestFocus();
        isStarted = true;
        int i = new Random().nextInt(4);
        this.sign.setText(signs[i]);
        full(signs[i]);
        int[] time = {60}; //Чтобы внутри события был доступен, делаем в виде массива.
        Timeline timeline = new Timeline(
                new KeyFrame(
                        Duration.millis(1000), //1000 мс
                        ae -> {
                            if (this.time.getText().equals("1")) {
                                try {
                                    resultWindow();
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                            }
                            time[0]--;
                            this.time.setText("" + time[0]);
                        }
                )
        );
        if (this.time.getText().equals("60")) {
            timeline.setCycleCount(60); //Ограничим число повторений
            timeline.play(); //Запускаем
        }
        this.startButton.setVisible(false);
        this.startButton.setDisable(true);
        this.restartButton.setDisable(false);
    }

    public void full(String sign) {
        a = new Random().nextInt(100) + 1;
        switch (sign) {
            case "+":
                b = new Random().nextInt(100) + 1;
                break;
            case "*":
                b = new Random().nextInt(40) + 1;
                break;
            case "-":
                b = new Random().nextInt(a) + 1;
                break;
            case "/":
                b = new Random().nextInt(a) + 1;
                while (a % b != 0) {
                    b = new Random().nextInt(a) + 1;
                }
                break;
        }
        this.numberA.setText("" + a);
        this.numberB.setText("" + b);
    }

    @FXML
    private void resultWindow() throws IOException {
        this.answer.setVisible(false);
        this.numberA.setVisible(false);
        this.numberB.setVisible(false);
        this.sign.setVisible(false);
        this.yourScore.setLayoutY(300);
        int result = this.scores * 100 - (this.amount - this.scores) * 50;
        if (result < 0) result = 0;
        this.score.setText(result + "");
        this.score.setLayoutY(300);
        this.time.setVisible(false);
        Files.write(Paths.get("src/score.txt"), (result + "\n").getBytes(), StandardOpenOption.APPEND);


        Date date = new Date();                // WORK WITH SCORE ON SERVER SIDE
        DateFormat format = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss", Locale.ENGLISH);
        ScoreElement scoreElement = new ScoreElement(result, date, 2, StateOfauthentication.getLogin());

        DataStore.countData.add(scoreElement);
        PostResults.postData(result, 2);
    }
}
