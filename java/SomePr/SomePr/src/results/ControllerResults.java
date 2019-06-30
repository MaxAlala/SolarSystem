package results;

import connection.GetResult;
import connection.StateOfauthentication;
import data.ScoreElement;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.chart.BarChart;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.text.ParseException;
import java.util.*;

public class ControllerResults implements Initializable {
    @FXML
    public void toMenu(ActionEvent event) throws IOException {
        Parent page1 = FXMLLoader.load(getClass().getResource(ResultGame.getMenuPath()));
        Scene tableScene = new Scene(page1);
        Stage window = (Stage) ((Node) event.getSource()).getScene().getWindow();
        window.setScene(tableScene);
        window.getScene().getStylesheets().add("css/GeomStyle.css");
        window.show();
    }

    @FXML
    private AnchorPane root;


    @Override
    public void initialize(URL location, ResourceBundle resources) {
        try {
            try {
                showResults();
            } catch (ParseException e) {
                e.printStackTrace();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @FXML
    private void showResults() throws IOException, ParseException {
        BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream("src/"+ResultGame.getPath()+".txt")));
        String line = br.readLine();
        int k = 0;

        CategoryAxis xAxis    = new CategoryAxis();
        xAxis.setLabel("Date");
        NumberAxis yAxis = new NumberAxis();
        BarChart barChart = new BarChart(xAxis, yAxis);
        XYChart.Series dataSeries1 = new XYChart.Series();
        dataSeries1.setName("Results for last 9 games");


        ArrayList<ScoreElement> ll =  GetResult.getResults(ResultGame.getGametype(),9);
        String ss;
        String date;
        for(int i = ll.size() -1; i >-1; i--) {
            k++;
            date=ll.get(i).getDate().toString();

            ss="";
            for(int j =4;j<10;j++){
                ss=ss+date.charAt(j);

            }

            dataSeries1.getData().add(new XYChart.Data(ss, ll.get(i).getScore()));

        }
        barChart.setTranslateY(100);
        barChart.getData().add(dataSeries1);
        VBox vbox = new VBox(barChart);
        vbox.setAlignment(Pos.BOTTOM_CENTER);
        root.getChildren().add(vbox);
    }
}
