package sample;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.Priority;
import javafx.scene.paint.Color;
import network.TCPConnection;
import network.TCPConnectionListener;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

public class Controller implements Initializable, TCPConnectionListener {

   private int newbie = 15, profi = 8;
    private int last_newbie = 0, last_profi = 0, left_newbie = 0, left_profi = 0;
   private int lift = 1, hotel = 1, pro_track = 1, newbie_track = 1, restaurant = 1;
   private int credits = 250000, popularity = 40, ad_exp = 50000;
    private int total_client = newbie + profi;

    private int lift_exp, hotel_exp, pro_track_exp, newbie_track_exp,
    restaurant_exp;
    private int total_exp = lift_exp + hotel_exp + pro_track_exp + newbie_track_exp +
            restaurant_exp + ad_exp;


    private int build_limit = 2;
    private int day = 0;

     private final int  newbie_track_ab =25;
    private final int  profi_track_ab =20;
    private final int  ski_lift_ab =35;
    private final int  restaurant_ab = 60;
    private final int  hotel_ab =90;
    private int hotel_maintainance = 12500;
    private int restaurant_maintainance = 10000;
    private int ski_lift_maintainance = 12000;
    private int profi_track_maintainance = 9000;
    private int newbie_track_maintainance = 8000;



    private int angryCoef = 0;

    private void newDay(){
        credits = credits + (newbie*2000 + profi * 4000) - (newbie_track*newbie_track_maintainance + pro_track*profi_track_maintainance) - (lift*ski_lift_maintainance + restaurant * restaurant_maintainance + hotel * hotel_maintainance) - ad_exp;
        build_limit = 2;
        if(day == 20 || credits < -150000){
            main_text_win.setText("this is end");
            ObservableList<String> list = FXCollections.observableArrayList(
                    "end");
            listView.setItems(list);
        }else{


        ObservableList<String> list = FXCollections.observableArrayList(
                 "Rest somewhere and finish this day", "Talk to the experts");
        listView.setItems(list);
        day++;
        newClients();

        checkCoefPopularity();
            int minus_pop =((int) (Math.random() * 7));
        popularity-=minus_pop;
        int plus_pop_ad = (2*ad_exp/10000 +(int) (Math.random() * (ad_exp/10000*5)));
            System.out.println(minus_pop + " " + plus_pop_ad);
        popularity+=plus_pop_ad;
            System.out.println(angryCoef);
        if(popularity>100)popularity = 100;
        if(popularity<0)popularity = 0;
            renewalOfNoteBook();
        main_text_win.setText("Today is new " +day+" day of your resort management. \n" +
                "You're in your office with the report in front of your eyes: \n" +
                "Beginners - initial number: " + last_newbie+ ", left:" + left_newbie +", arrived:" +(newbie-last_newbie + left_newbie) + "now: "+newbie+ "\n" +
                "Pros - initial number: " + last_profi+ ", left:" + left_profi +", arrived:" +(profi-last_profi+ left_profi) + "now: "+profi+ "\n" +
                "\n" +
                "Money received:" +
                "from beginners: "+newbie*2000 +"\n" +
                "from pros: "+profi*4000 +"\n" +
                "Money spent on: \n" +
                "track maintenance: "+ (newbie_track*newbie_track_maintainance+pro_track*profi_track_maintainance)+" cr \n" +
                "Constructions:    " + (lift*ski_lift_maintainance + restaurant * restaurant_maintainance + hotel * hotel_maintainance)+" cr.\n" +

                "advertising: " + ad_exp + "cr \n" +
                "Money on the account: " + credits +" cr"
        );
        }

    }

    private void checkCoefPopularity(){
        angryCoef = 0;
        if(newbie>newbie_track_ab*newbie_track) angryCoef +=  newbie - newbie_track_ab*newbie_track;
        if(profi>profi_track_ab*pro_track) angryCoef +=  profi - profi_track_ab*pro_track;
        if (total_client > ski_lift_ab*lift) angryCoef += total_client - ski_lift_ab*lift;
        if(total_client > restaurant_ab* restaurant) angryCoef +=total_client - restaurant * restaurant_ab;
        if(total_client > hotel_ab* hotel) angryCoef +=total_client - hotel * hotel_ab;

    }
    @FXML
    private  Label main_text_win;
    @FXML
    private  Label l_hotel;
    @FXML
    private  Label l_newbie;
    @FXML
    private  Label l_profi;
    @FXML
    private  Label l_pro_track;
    @FXML
    private  Label l_newbie_track;
    @FXML
    private  Label l_restaurant;
    @FXML
    private  Label l_credits;
    @FXML
    private  Label l_lift;
    @FXML
    private  Label l_pop;
    @FXML
    private  Label l_total_client;
    @FXML
    private  Label l_ad_exp;

    @FXML
    private  ListView listView;

    @FXML
            private ImageView imageView;

    ObservableList<String> data;


    private int getClientsTOPersent(int total_ability, int current){
        return (int)100/total_ability*current;
    }

    @FXML
    private void handleButtonAction(ActionEvent event) {
        System.out.println("You clicked me!");
        main_text_win.setText("Hello World!");

    }


    class XCell extends ListCell<String> {
        HBox hbox = new HBox();
//        Label label2 = new Label("");

        Pane pane = new Pane();
         public XCell() {
             super();
             button.setMaxWidth(1391);
             button.setPrefWidth(1391);
//            button.setText();
             button.setTextFill(Color.web("#FAEBD7"));
//            label2.setTextFill(Color.web("#FAEBD7"));
             hbox.getChildren().addAll(pane, button);
             HBox.setHgrow(pane, Priority.ALWAYS);
             button.setOnAction(event -> {
                 String text = ((Button)event.getSource()).getText();
                 System.out.println(text + " "+ text.equals("call main-manager of this resort"));
                 if(text.equals("call main engineer of this resort")){ //AAA main-engineer
                     getListView().getItems().removeAll();
                     ObservableList<String> list = null;
                     if(build_limit != 0)
                    list = FXCollections.observableArrayList(
                            "build hotel", "build restaurant", "build ski track for beginners","build ski track for pros", "build ski lift","Ok. Thanks");
                     else list = FXCollections.observableArrayList(
                             "Ok. Thanks");


                     listView.setItems(list);
                     main_text_win.setText("A big emotionless man - the constructor manager - made a brief report on the situation: \n" +
                             "- We can construct up to two building per day. Such speed can gained due to the section technology that allows assembling structures out of separate sections. We can assemble the following structures: \n" +
                             "1) Hotel - costs 110.000 cr, accommodates 60 people. \n" +
                             "2) Restaurant - costs 80.000 cr, feeds 30 people.\n" +
                             "3) Track for beginners - costs 45.000 cr, receives 25 beginners. \n" +
                             "4) Track for pros - costs 60.000 cr, receives 20 pros. \n" +
                             "5)Ski lift - costs 105.000 cr, holds 50 people. \n" +
                             "Count of building that we can build today is "+build_limit+ ".");
                 }if(text.equals("call main economist of this resort")){ //CCC main-economist
                     getListView().getItems().removeAll();
                     ObservableList<String> list = FXCollections.observableArrayList(
                             "Take a loan", "Ok. Thanks");
                     main_text_win.setText("The economist turned out to be a man of immense format whose report was brief and to the point: \n" +
                             "-At present the following of tourists are sppending their vacations at the resort: "+ total_client+ " (beginners: "+newbie+"; pros: "+ profi +")."+"\n" +
                             "The hotels are "+ getClientsTOPersent(hotel*hotel_ab, total_client) +" % full. \n " +
                             "The restaurants serve "+restaurant*restaurant_ab +" people. \n" +
                             "The number of ski lifts is enough to hold "+ lift*ski_lift_ab + " clients. \n" +
                             "The track receive " + newbie +" beginners and " + profi +" pros.");
                     listView.setItems(list);

                 }if(text.equals("call main PR-manager of this resort")){ //DDD main-PR-manager
                     getListView().getItems().removeAll();
                     ObservableList<String> list = FXCollections.observableArrayList(
                             "pay 0", "pay 10k","pay 20k","pay 30k", "pay 40k", "pay 50k", "Ok. Thanks");
                     listView.setItems(list);

                     main_text_win.setText("A merry young man was responsible for the resort advertising. His report was the following: \n" +
                             "- At the present time the resort's popularity is equal to" + popularity + "%. The influx of tourists depends on it; besides, if the" +
                             "popularity percentage falls down to 0, they can close the doors! \n" +
                             "\n" +
                             "Any new structure add 2-5% to the popularity, and if this structure is used by the tourists, it adds 5-10% to the popularity. Each disappointed beginner who left the resort, takes 1% from the popularity, \n and each pro takes 2%. The clients can annoyed by the lack of restaurants, ski lifts or needed tracks. Though mind that not all leaving clients are disappointed. \n" +
                             "\n" +
                             "   Besides, the resort`s popularity loses 5-10% per day just for no reason. This is why it needs advertising. Every 10.000 cr. spent on advertising per day, add 3-5% to the resort`s popularity. Unfortunately,\n Trigit-augro, regulations won`t let us spend more then 50.000 cr per day on advertising. \n" +
                             "\n" +
                             "The current advertising expenses are equal to" + ad_exp + " cr per day.");

                 } if(text.equals("call main accountant of this resort")){ //EEE renewal
                 getListView().getItems().removeAll();
                 ObservableList<String> list = FXCollections.observableArrayList(
                          "Ok. Thanks");
                 listView.setItems(list);
                 main_text_win.setText("   The neat accountant prepared the balance for you: \n" +
                         "\n" +
                         "Balance as of this day: " + credits + " cr.\n" +
                         " ----------------------------------------------- \n" +
                         "                         DEBIT             CREDIT\n"+
                         "Tourists:              "+ (newbie*2000 + profi * 4000)+"cr.\n" +
                         "Track maintenance:                         " + (newbie_track*newbie_track_maintainance + pro_track*profi_track_maintainance)+"cr.\n" +
                         "Advertising:                               " + ad_exp+ " cr. \n" +
                         "Constructions:                             " + (lift*ski_lift_maintainance + restaurant * restaurant_maintainance + hotel * hotel_maintainance)+" cr.\n" +
                         "------------------------------------------------ " +
                         "Balance as of tomorrow: "+ (credits + (newbie*2000 + profi * 4000) - (newbie_track*newbie_track_maintainance + pro_track*profi_track_maintainance) - (lift*ski_lift_maintainance + restaurant * restaurant_maintainance + hotel * hotel_maintainance)) +" cr \n");

             }if(text.equals("Ok. Thanks")){ //EEE renewal
                     getListView().getItems().removeAll();
                     ObservableList<String> list = FXCollections.observableArrayList(
                             "call main accountant of this resort", "call main manager of this resort", "call main engineer of this resort", "call main PR-manager of this resort", "call main economist of this resort","Rest somewhere and finish this day");
                     listView.setItems(list);

                     main_text_win.setText("Hmm. Work, work, work. As one said.");

                 }if(text.equals("build ski track for beginners")){ //build track
                     if(checkMoney(45000)) {
                         popularity+=((int) (Math.random() *5));
                         credits -= 45000;
                         newbie_track++;
                         build_limit--;
                         renewalOfNoteBook();
                         getListView().getItems().removeAll();
                         ObservableList<String> list = FXCollections.observableArrayList("Ok. Thanks");
                         listView.setItems(list);

                         main_text_win.setText("Construction was built.");
                     }else{
                         notEnoughMoney();
                     }
                 }if(text.equals("build ski track for pros")){ //build track
                     if(checkMoney(60000)) {
                         popularity+=((int) (Math.random() *6));
                         credits -= 60000;
                         pro_track++;
                         build_limit--;
                         renewalOfNoteBook();

                         getListView().getItems().removeAll();
                         ObservableList<String> list = FXCollections.observableArrayList("Ok. Thanks");
                         listView.setItems(list);

                         main_text_win.setText("Construction was built.");
                     }else{
                         notEnoughMoney();
                     }
                 }if(text.equals("build restaurant")){ //build track
                     if(checkMoney(80000)) {
                         popularity+=((int) (Math.random() *9));
                         credits -= 80000;
                         restaurant++;
                         build_limit--;
                         renewalOfNoteBook();


                         getListView().getItems().removeAll();
                         ObservableList<String> list = FXCollections.observableArrayList("Ok. Thanks");
                         listView.setItems(list);

                         main_text_win.setText("Construction was built.");
                     } else{
                         notEnoughMoney();
                     }

                 }if(text.equals("build ski lift")){ //build track
                     if(checkMoney(105000)) {
                         popularity+=((int) (Math.random() *8));

                         lift++;
                         build_limit--;
                         credits -= 105000;
                         renewalOfNoteBook();

                         getListView().getItems().removeAll();
                         ObservableList<String> list = FXCollections.observableArrayList("Ok. Thanks");
                         listView.setItems(list);

                         main_text_win.setText("Construction was built.");
                     }else{
                         notEnoughMoney();
                     }
                 }if(text.equals("build hotel")){ //build track
                     if(checkMoney(110000)) {
                         popularity+=((int) (Math.random() *10));
                         hotel++;
                         build_limit--;
                         credits -= 110000;
                         renewalOfNoteBook();

                         getListView().getItems().removeAll();
                         ObservableList<String> list = FXCollections.observableArrayList("Ok. Thanks");
                         listView.setItems(list);

                         main_text_win.setText("Construction was built.");
                     } else{
                         notEnoughMoney();
                     }
                 }if(text.equals("Rest somewhere and finish this day")){ //renewal

                     newDay();


                 }if(text.equals("Talk to the experts")){ //experts

                     ObservableList<String> list = FXCollections.observableArrayList(
                             "call main accountant of this resort", "call main manager of this resort", "call main engineer of this resort","call main PR-manager of this resort","call main economist of this resort","Rest somewhere and finish this day");
                     listView.setItems(list);

                     main_text_win.setText("Hmm. Work, work, work. As one said.");

                 }if(text.equals("pay 0")){ //experts
                     ad_exp = 0;
                     renewalOfNoteBook();
                     ObservableList<String> list = FXCollections.observableArrayList("Ok. Thanks");
                     listView.setItems(list);

                     main_text_win.setText("-Done.");

                 }if(text.equals("pay 10k")){ //experts
                     ad_exp = 10000;
                     renewalOfNoteBook();
                     ObservableList<String> list = FXCollections.observableArrayList("Ok. Thanks");
                     listView.setItems(list);

                     main_text_win.setText("-Done.");

                 }if(text.equals("pay 20k")){ //experts
                     ad_exp = 20000;
                     renewalOfNoteBook();
                     ObservableList<String> list = FXCollections.observableArrayList("Ok. Thanks");
                     listView.setItems(list);

                     main_text_win.setText("-Done.");

                 }if(text.equals("pay 30k")){ //experts
                     ad_exp = 30000;
                     renewalOfNoteBook();
                     ObservableList<String> list = FXCollections.observableArrayList("Ok. Thanks");
                     listView.setItems(list);

                     main_text_win.setText("-Done.");

                 }if(text.equals("pay 40k")){ //experts
                     ad_exp = 40000;
                     renewalOfNoteBook();
                     ObservableList<String> list = FXCollections.observableArrayList("Ok. Thanks");
                     listView.setItems(list);

                     main_text_win.setText("-Done.");

                 }if(text.equals("pay 50k")){ //experts
                     ad_exp = 50000;
                     renewalOfNoteBook();
                     ObservableList<String> list = FXCollections.observableArrayList("Ok. Thanks");
                     listView.setItems(list);

                     main_text_win.setText("-Done.");

                 }
                     });//  "pay 0", "pay 10k","pay 20k","pay 30k", "pay 40k", "pay 50k", "Ok. Thanks");

         }

          private void notEnoughMoney() {
              ObservableList<String> list = FXCollections.observableArrayList("Ok. Thanks");
              main_text_win.setText("Not enough money.");
          }


          private boolean checkMoney(int needMoney){
            return (credits >= needMoney);
         }
        Button button = new Button("Del");


        @Override
        protected void updateItem(String item, boolean empty) {
            super.updateItem(item, empty);
            setText(null);
            setGraphic(null);

            if (item != null && !empty) {
                button.setText(item);
                setGraphic(hbox);
            }
        }
    }

//    @FXML
//    private  Label l_hotel;
//    @FXML
//    private  Label l_newbie;
//    @FXML
//    private  Label l_profi;
//    private  Label l_pro_track;
//    private  Label l_newbie_track;
//    private  Label l_restaurant;
//    private  Label l_credits;
//    private  Label l_lift;
//    private  Label l_pop;
//    private  Label l_total_client;
//    private  Label l_ad_exp;

    @Override
    public void initialize(URL url, ResourceBundle rb) {

        ObservableList<String> list = FXCollections.observableArrayList(
                "call main accountant of this resort", "call main manager of this resort", "call main engineer of this resort", "call main PR-manager of this resort", "call main economist of this resort","Rest somewhere and finish this day");
        listView.setItems(list);
        listView.setCellFactory(param -> new XCell());

        renewalOfNoteBook();


//        File file = new File("src/pictures/build.jpg");
//        Image image = new Image(file.toURI().toString(),350, 380, false,false);
//        imageView.setImage(image);


        try {
            connection = new TCPConnection(this, "10.17.43.102", 8189);
        } catch (IOException e) {

            e.printStackTrace();

        }



    }

    private void renewalOfNoteBook() {
        l_hotel.setText("Hotels: " + hotel + " (" + hotel*hotel_ab + " beds)");
        l_newbie.setText("Beginners: " + newbie);
        l_profi.setText("Pros: " + profi);
        l_pro_track.setText("pro tracks: " + pro_track + " (" + pro_track*profi_track_ab+")" );
        l_newbie_track.setText("newbie tracks: " + newbie_track + " (" + newbie_track*newbie_track_ab+ ")");
        l_restaurant.setText("Restaurants: " + restaurant + " (" + restaurant*restaurant_ab+" seats)");
        l_credits.setText("Money on the account: " + credits+ " cr");
        l_lift.setText("lifts(" + lift + "): " + lift*ski_lift_ab);
        l_pop.setText("Popularity of the resort: " + popularity +" %");
        l_total_client.setText("TOTAL NUMBER OF VISITORS: " + total_client);
        l_ad_exp.setText("Advertising expenses: " + ad_exp +" cr");
    }



    private void newClients(){
        last_newbie = newbie;
        last_profi = profi;
        newbie = newbie + ((int) (Math.random() * popularity / 4));
        profi = profi +(0+ (int) (Math.random() * popularity/6));
        left_newbie = (0+ (int) (Math.random() * (double)last_newbie/100*(100-popularity + angryCoef)));
        left_profi = (0+ (int) (Math.random() * (double)last_profi/100*(100-popularity+ angryCoef)));

        newbie-=left_newbie;
        profi-=left_profi;
        total_client=newbie+profi;
        System.out.println("again minus pop " + ((left_newbie + left_profi*2)/3));
        popularity -= (left_newbie + left_profi*2)/3;


    }


    /////////////////////////// SOckets

    @FXML
    private TextField inputName;
    @FXML
    private Button button1;
    @FXML
    private TextField inputText;
    @FXML
    private TextArea text;


    TCPConnection connection;

    private synchronized void printMsg(String msg) {
        Platform.runLater(() -> {

            text.appendText(msg + "\n");
//	 awesome short !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        });

    }
    @Override
    public void onConnectionReady(TCPConnection tcpConnection) {
        // TODO Auto-generated method stub
        printMsg("connection ready...");
    }

    @Override
    public void onReceiveString(TCPConnection tcpConnection, String value) {
        printMsg(value);

    }

    @Override
    public void onDisconnect(TCPConnection tcpConnection) {
        // TODO Auto-generated method stub
        printMsg("connection closed");
    }

    @Override
    public void onException(TCPConnection tcpConnection, Exception e) {
        // TODO Auto-generated method stub
        printMsg("connection exception: " + e);
    }
    @FXML
    private void ActionPerformed(ActionEvent event) throws IOException {
        System.out.println("tsetsetse");
        String msg = inputText.getText();
        if(msg.equals("")) return;
        inputText.setText(null);
        connection.sendString(inputName.getText() + ": " + msg);
    }
}
