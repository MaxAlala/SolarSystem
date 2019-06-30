package flappybird;

import com.sun.org.apache.xpath.internal.SourceTree;
import connection.*;
import data.DataStore;
import data.ScoreElement;
import flappybird.res.Resourses;
import javafx.animation.*;
import javafx.application.Application;
import javafx.beans.property.SimpleDoubleProperty;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import javafx.scene.shape.Path;
import javafx.scene.shape.Shape;
import javafx.scene.transform.Rotate;
import javafx.stage.Stage;
import javafx.util.Duration;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Locale;
import java.util.logging.Logger;


public class FlappyBird extends Application {  // das coolste Spiel aller Zeiten!!! JEDER MAN LIEBT ES!
    // JAAAAAAAWOLL gewiss
    private static Logger log = Logger.getLogger(FlappyBird.class.getName());

    private final double width = 1000, height = 400; // set screen size
    Resourses res = new Resourses();
    Pane decke;
    boolean gameOver = false;
    private boolean incrementOnce = true;
    int score = 0;
    int highScore = 0;
    double FPS_30 = 30;
    int counter_30FPS = 0, counter_3FPS = 0;
    Bird bird;
    TranslateTransition jump;
    TranslateTransition fall;
    RotateTransition rotator;
    ArrayList<TwoTubes> listOfTubes = new ArrayList<>();
    ArrayList<Cloud> listOfClouds = new ArrayList<>();
    ScoreLabel scoreLabel = new ScoreLabel(width, 0);

    Timeline gameLoop;

    @Override
    public void start(Stage primaryStage) {
        decke = new Pane();
        decke.setStyle("-fx-background-color: #FF059F"); //4EC0CA
        Scene scene = new Scene(decke, width, height);
        primaryStage.setTitle("Flappy bird");
        primaryStage.setScene(scene);
        primaryStage.show();
        StartLabel startLabel = new StartLabel(450, 100);


        initGame();
        decke.getChildren().add(startLabel);
        startLabel.setText("   " + StateOfauthentication.getLogin() + ", Shall we begin? "+ "\n      Best score: " + highScore);
        decke.getChildren().get(1).setOpacity(0);
        gameOver = true;
        gameLoop.stop();
        // menu_vvv
//        addMenuToRoot();
        // menu_^^^
        decke.setPrefSize(width, height);
        decke.setOnMouseClicked(e -> {
            if (!gameOver) {
                jumpflappy();
            } else {
                initializeGame();
            }
        });
    }

    public static void main(String[] args) {
        launch(args);
    }

    private void updateCounters() {
        if (counter_30FPS % 4 == 0) {
            bird.refreshBird();
            counter_30FPS = 1;
        }
        counter_30FPS++;
    }

    private void jumpflappy() {
        rotator.setDuration(Duration.millis(100));
        rotator.setToAngle(-40);
        rotator.stop();
        rotator.play();
        jump.setByY(-50);
        jump.setCycleCount(1);
        bird.jumping = true;
        fall.stop();
        jump.stop();
        jump.play();
        jump.setOnFinished((finishedEvent) -> {
            rotator.setDuration(Duration.millis(500));
            rotator.setToAngle(40);
            rotator.stop();
            rotator.play();
            bird.jumping = false;
            fall.play();
        });
    }


    private void changeGame(int jump2, int fall2) {
        jump = new TranslateTransition(Duration.millis(jump2), bird.getGraphics());//450
        fall = new TranslateTransition(Duration.millis(fall2 * height), bird.getGraphics());
        jump.setInterpolator(Interpolator.LINEAR);
        fall.setByY(height + 20);

    }

    private void checkCollisions() {
        TwoTubes tube = listOfTubes.get(0);
        if (tube.getTranslateX() < 35 && incrementOnce) {
            score++;
//            changeGame(100, 13);
//
//
//            int random_number = 1 + (int) (Math.random() * 3);
//
//            if(random_number == 1 ){       //speed + slow
//                changeGame(100, 13);
//            }else
//            if(random_number == 2 ){       //speed + slow
//                changeGame(400, 7);
//            }else
//            if(random_number == 3 ) {       //speed + slow
//                changeGame(250, 150);
//            }


            scoreLabel.setText("Score: " + score);
            incrementOnce = false;
        }
        Path p1 = (Path) Shape.intersect(bird.getBounds(), tube.topBody);
        Path p2 = (Path) Shape.intersect(bird.getBounds(), tube.topHead);
        Path p3 = (Path) Shape.intersect(bird.getBounds(), tube.lowerBody);
        Path p4 = (Path) Shape.intersect(bird.getBounds(), tube.lowerHead);
        boolean intersection = !(p1.getElements().isEmpty()
                && p2.getElements().isEmpty()
                && p3.getElements().isEmpty()
                && p4.getElements().isEmpty());
        if (bird.getBounds().getCenterY() + bird.getBounds().getRadiusY() > height || bird.getBounds().getCenterY() - bird.getBounds().getRadiusY() < 0) {
            intersection = true;
        }
        if (intersection) {
            GameOverLabel gameOverLabel = new GameOverLabel(500, 150);
//            gameOverLabel.getScene().ge
            highScore = highScore < score ? score : highScore;
            saveYourScore(score);
//            saveHighScore();
                // add to menu button
            String string = null;

            if(score == 0){
                int random_number1 = 1 + (int) (Math.random() * 9);
                switch(random_number1){
                    case 1:
                        string = "failure.., ";
                        break;
                    case 2:
                        string = "Pfff,";
                        break;
                    case 3:
                        string = "waste time.., ";
                        break;
                    case 4:
                        string = "i dont like you,";
                        break;
                    case 5:
                        string = "pesky.., ";
                        break;
                    case 6:
                        string = "desperate.., ";
                        break;
                    case 7:
                        string = "dorky..,";
                        break;
                    case 8:
                        string = "brat.., ";
                        break;
                    case 9:
                        string = "your destiny.., ";
                        break;
                }

            } else
                if(score > 15 ){
                    int random_number1 = 1 + (int) (Math.random() * 10);
                    switch(random_number1){
                        case 1:
                            string = "OMG, ";
                            break;
                        case 2:
                            string = "ТЫ ЛУЧШИЙ ДРУЖОК, ";
                            break;
                        case 3:
                            string = "YOU GOD,";
                            break;
                        case 4:
                            string = "take pie from shelf, ";
                            break;
                        case 5:
                            string = "O my god, ";
                            break;
                        case 6:
                            string = "Take sweets from the shelf, ";
                            break;
                        case 7:
                            string = "i wanna you, ";
                            break;

                        case 8:
                            string = "OOOO!,";
                            break;
                        case 9:
                            string = "OOOOOOOOO!,";
                            break;
                        case 10:
                            string = "ォー!!,";
                            break;

                    }
                } else
                    if( score>0 && score <= 5){
                        int random_number1 = 1 + (int) (Math.random() * 7);
                        switch(random_number1){
                            case 1:
                                string = "typical.., ";
                                break;
                            case 2:
                                string = "simple enough,";
                                break;
                            case 3:
                                string = "go on,";
                                break;
                            case 4:
                                string = "okeey,";
                                break;
                            case 5:
                                string = "go on,";
                                break;
                            case 6:
                                string = "try again,";
                                break;
                            case 7:
                                string = "okee,";
                                break;
                        }
                        }else
                    if( score>5 && score <= 15){
                        int random_number1 = 1 + (int) (Math.random() * 7);
                        switch(random_number1){
                            case 1:
                                string = "01010101.., ";
                                break;
                            case 2:
                                string = "...,";
                                break;
                            case 3:
                                string = "JUPITER,";
                                break;
                            case 4:
                                string = "go on,";
                                break;
                            case 5:
                                string = "DRUZHKO1,";
                                break;
                            case 6:
                                string = "simple enough,";
                                break;
                            case 7:
                                string = "easy to achieve,";
                                break;
                        }
                    }


            gameOverLabel.setText("    "+ string + StateOfauthentication.getLogin() +"!!\n Try again. Result: " + score + "\nYour best one: " + highScore);
//             addMenuToRoot();
            decke.getChildren().add(gameOverLabel);
            decke.getChildren().get(1).setOpacity(0);
            gameOver = true;
            gameLoop.stop();
        }
    }

//     void addMenuToRoot(){
//         HBox hbox = new HBox();
//         Button toMenu = new Button("Menu");
//         toMenu.setOnAction(e -> {
//             Parent page1 = null;
//             try {
//                 page1 = FXMLLoader.load(getClass().getResource("../mainMenu/sampleMenu.fxml"));
//             } catch (IOException e1) {
//                 e1.printStackTrace();
//             }
//             Scene tableScene = new Scene(page1);
//             Stage window = (Stage)((Node)e.getSource()).getScene().getWindow();
//             window.setScene(tableScene);
//             window.show();
//         });
//
//
//         Button closeTheApllication = new Button("closeApp");
//         closeTheApllication.setOnAction(e ->{
//             System.exit(1);
//         });
//
//
//         hbox.getChildren().addAll(toMenu, closeTheApllication);
//         root.getChildren().add(hbox);
//     }

    void initializeGame() {
        listOfTubes.clear();
        listOfClouds.clear();
        decke.getChildren().clear();
        bird.getGraphics().setTranslateX(100);
        bird.getGraphics().setTranslateY(150);
        scoreLabel.setOpacity(0.8);
        scoreLabel.setText("Result: 0");
        decke.getChildren().addAll(bird.getGraphics(), scoreLabel);
        for (int i = 0; i < 5; i++) {
            Cloud cloud = new Cloud();
            cloud.setX(Math.random() * width);
            cloud.setY(Math.random() * height * 0.5 + 0.1);
            listOfClouds.add(cloud);
            decke.getChildren().add(cloud);
        }
        for (int i = 0; i < 5; i++) {
            SimpleDoubleProperty y = new SimpleDoubleProperty(0);
            y.set(decke.getHeight() * Math.random() / 2.0);
            TwoTubes tube = new TwoTubes(y, decke, false, false);
            tube.setTranslateX(i * (width / 4 + 10) + 400);
            listOfTubes.add(tube);
            decke.getChildren().add(tube);
        }
        score = 0;
        incrementOnce = true;
        gameOver = false;
        bird.jumping = false;
        fall.stop();
        fall.play();
        gameLoop.play();
    }

    void initGame() {
        bird = new Bird(res.birdImgs);
        rotator = new RotateTransition(Duration.millis(500), bird.getGraphics());//500
        jump = new TranslateTransition(Duration.millis(150), bird.getGraphics());//450
        fall = new TranslateTransition(Duration.millis(5 * height), bird.getGraphics());
        jump.setInterpolator(Interpolator.LINEAR);
        fall.setByY(height + 20);
        rotator.setCycleCount(1);
        bird.getGraphics().setRotationAxis(Rotate.Z_AXIS);
        gameLoop = new Timeline(new KeyFrame(Duration.millis(300 / FPS_30), new EventHandler<ActionEvent>() { //400

            public void handle(ActionEvent e) {
                updateCounters();
                checkCollisions();
                if (listOfTubes.get(0).getTranslateX() <= -width / 12.3) { // 12.3
                    listOfTubes.remove(0);
                    SimpleDoubleProperty y = new SimpleDoubleProperty(0);
                    y.set(decke.getHeight() * Math.random() / 2.0);
                    TwoTubes tube;
                    if (Math.random() < 0.4) {
                        tube = new TwoTubes(y, decke, true, false);
                    } else if (Math.random() > 0.85) {
                        tube = new TwoTubes(y, decke, true, true);
                    } else {
                        tube = new TwoTubes(y, decke, false, false);
                    }
                    tube.setTranslateX(listOfTubes.get(listOfTubes.size() - 1).getTranslateX() + (width / 4 + 10));
                    listOfTubes.add(tube);
                    incrementOnce = true;
                    decke.getChildren().remove(7);
                    decke.getChildren().add(tube);
                }
                for (int i = 0; i < listOfTubes.size(); i++) {
                    if (listOfClouds.get(i).getX() < -listOfClouds.get(i).getImage().getWidth() * listOfClouds.get(i).getScaleX()) {
                        listOfClouds.get(i).setX(listOfClouds.get(i).getX() + width + listOfClouds.get(i).getImage().getWidth() * listOfClouds.get(i).getScaleX());
                    }
                    listOfClouds.get(i).setX(listOfClouds.get(i).getX() - 1);
                    listOfTubes.get(i).setTranslateX(listOfTubes.get(i).getTranslateX() - 2);
                }
            }
        }));
        gameLoop.setCycleCount(-1);
        loadHighScore();
        initializeGame();

    }

    void loadHighScore() {
        try {
            GetGlobalPosition getGlobalPosition = new GetGlobalPosition();
            System.out.println(getGlobalPosition.getResults(0));
            GetBestScore getBestScore = new GetBestScore();
            ScoreElement scoreElement = getBestScore.getResults(0, "month");
            highScore = scoreElement.getScore();
            log.info("SUCCESS LOAD HIGH SCORE.");
            System.out.println(highScore);
        } catch (Exception e) {
            e.printStackTrace();
            log.info("ERROR LOAD HIGH SCORE.");
        }

    }

    void saveYourScore(int score){ // WORK WITH SCORE ON SERVER SIDE
        try {
            Date date = new Date();
            DateFormat format = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss", Locale.ENGLISH);

            ScoreElement scoreElement = new ScoreElement(score, date, 0, StateOfauthentication.getLogin());

            DataStore.flappyData.add(scoreElement);
            PostResults.postData(score, 0);
            Files.write(Paths.get("src/flappyScore.txt"), (score + "\n").getBytes(), StandardOpenOption.APPEND);
            log.info("SUCCESS SAVE SCORE.");
//            if(DataStore.flappyData.size() >= 5){
//                if(PostResults.postArray(DataStore.flappyData) == true)
//                DataStore.flappyData.clear(); else {
//                    System.out.println("someErrorInPost");
//                }
//            }


        } catch (IOException e) {
            e.printStackTrace();
        }
    }

//    void saveHighScore() {
//        try {
//            DataOutputStream out = new DataOutputStream(new FileOutputStream("highScore.score"));
//            System.out.println(highScore);
//            out.writeInt(highScore);
//            out.flush();
//        } catch (Exception e) {
//        }
//    }
}
