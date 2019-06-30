package memorypuzzle;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.*;

import connection.PostResults;
import connection.StateOfauthentication;
import data.DataStore;
import data.ScoreElement;
import javafx.animation.FadeTransition;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import javafx.util.Duration;


public class MPGame {
    @FXML
    private Label startbutton;
    @FXML
    private Button restartbutton;
    @FXML
    private AnchorPane mainpane;
    @FXML
    private Label time;
    private List<Tile> tiles;
    private static final int NUM_OF_PAIRS = 8;
    private static final int NUM_PER_ROW = 4;
    private static int pairsopened = 0;
    private Tile selected = null;
    private int clickCount = 2;
    private Timeline timeline;
    public int counter = 0;

    private Parent createContent(AnchorPane root) throws IOException {
        counter = 0;
        int[] time = {0};
        timeline = new Timeline(
                new KeyFrame(
                        Duration.millis(1000),
                        (ActionEvent ae) -> {
                            time[0]++;
                            this.time.setText("" + time[0]);
                        }
                )
        );

        timeline.setCycleCount(60);
        timeline.play();

        char c = 'A';
        tiles = new ArrayList<>();
        for (int i = 0; i < NUM_OF_PAIRS; i++) {
            tiles.add(new Tile(i + 1));
            tiles.add(new Tile(i + 1));
            c++;
        }

        Collections.shuffle(tiles);

        for (int i = 0; i < tiles.size(); i++) {
            Tile tile = tiles.get(i);

            tile.setTranslateX(50 + 100 * (i % NUM_PER_ROW));
            tile.setTranslateY(200 + 100 * (i / NUM_PER_ROW));
            root.getChildren().add(tile);
        }

        return root;
    }

    @FXML
    private void restart() throws Exception {
        for (Tile tile : tiles) {
            tile.close();
        }
        tiles.clear();
        pairsopened = 0;
        start();
    }

    @FXML
    public void start() throws Exception {
        if (timeline != null) {
            time.setText("0");
            timeline.stop();
        }
        pairsopened = 0;
        createContent(mainpane);
        startbutton.setVisible(false);
        restartbutton.setDisable(false);

    }

    @FXML
    private void goback(ActionEvent event) throws IOException {
        Parent page1 = FXMLLoader.load(getClass().getResource("../memorypuzzle/MemoryPuzzleMenu.fxml"));
        Scene tableScene = new Scene(page1);
        Stage window = (Stage) ((Node) event.getSource()).getScene().getWindow();
        window.setScene(tableScene);
        window.getScene().getStylesheets().add("css/GeomStyle.css");
        window.show();
    }

    private class Tile extends StackPane {
        boolean active = true;
        private Text text = new Text();
        private ImageView imageView;

        public Tile(int v) {
            String value = v + "";
            Rectangle border = new Rectangle(100, 100);
            border.setFill(null);
            border.setStroke(Color.BLACK);
            text.setText(value);
            File file = new File("src/memorypuzzle/data/" + value + ".jpg");
            Image image = new Image(file.toURI().toString());
            imageView = new ImageView(image);
            getChildren().addAll(border, imageView);
            counter++;
            setOnMouseClicked(this::handleMouseClick);
            close();
        }

        public synchronized void handleMouseClick(MouseEvent event) {
            if (active) {
                if (isOpen() || clickCount == 0)
                    return;

                clickCount--;
                if (selected == null) {
                    selected = this;
                    open(() -> {
                    });
                } else {
                    open(() -> {
                        if (!hasSameValue(selected)) {
                            selected.close();
                            this.close();
                        } else {
                            pairsopened++;
                            if (pairsopened == NUM_OF_PAIRS) {
                                timeline.stop();
                                Parent page1 = null;
                                try {
                                    page1 = FXMLLoader.load(getClass().getResource("MPFinalWindow.fxml"));
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }

                                Scene tableScene = new Scene(page1);
                                Stage window = (Stage) ((Node) event.getSource()).getScene().getWindow();
                                window.setScene(tableScene);
                                window.getScene().getStylesheets().add("css/GeomStyle.css");
                                window.show();
                                int score = (60 - Integer.parseInt(time.getText())) * 15;
                                MPFinalWindow.setScores(score);
                                try {
                                    Files.write(Paths.get("src/memoryPuzzleScore.txt"), (score + "\n").getBytes(), StandardOpenOption.APPEND);

                                    Date date = new Date();
                                    DateFormat format = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss", Locale.ENGLISH);

                                    ScoreElement scoreElement = new ScoreElement(score, date, 1, StateOfauthentication.getLogin());

                                    //DataStore.memoryData.add(scoreElement);
                                    PostResults.postData(score, 1);

                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                            }
                        }
                        selected = null;
                        clickCount = 2;
                    });
                }
            }
        }

        public boolean isOpen() {
            return text.getOpacity() == 1;
        }

        public synchronized void open(Runnable action) {
            FadeTransition ft = new FadeTransition(Duration.seconds(0.001), text);
            ft.setToValue(1);
            ft.setOnFinished(e -> {
                action.run();
                active=false;
            });
            ft.play();
            FadeTransition ft1 = new FadeTransition(Duration.seconds(0.001), imageView);
            ft1.setFromValue(0);
            ft1.setToValue(1);
            //ft1.setOnFinished(e -> action.run());
            ft1.play();

        }

        public synchronized void close() {
            FadeTransition ft = new FadeTransition(Duration.seconds(0.8), text);
            ft.setToValue(0);
            ft.play();

            FadeTransition ft1 = new FadeTransition(Duration.seconds(0.9), imageView);
            ft1.setFromValue(1);
            ft1.setToValue(0);
            ft1.setOnFinished(e -> {
                active=true;
            });
            ft1.play();

        }

        public boolean hasSameValue(Tile other) {
            return text.getText().equals(other.text.getText());
        }
    }
}
