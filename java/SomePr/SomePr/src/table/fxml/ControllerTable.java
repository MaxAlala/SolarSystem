package table.fxml;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Modality;
import javafx.stage.Stage;

import java.io.IOException;

import table.impls.Person;
import static starter.Starter.addressBookImpl;

public class ControllerTable {


    @FXML
    private Button btnAdd;

    @FXML
    private Button btnEdit;

    @FXML
    private Button btnDelete;

    @FXML
    private TextField txtSearch;

    @FXML
    private Button btnSearch;

    @FXML
    public TableView<Person> tableAddressBook;

    @FXML
    private TableColumn<Person, String> columnFio;

    @FXML
    private TableColumn<Person, String> columnPhone;

    @FXML
    private Label labelCount;

    @FXML
    private Button btnOk;

    @FXML
    private Button btnCancel;

    @FXML
    private TextField txtName;

    @FXML
    private TextField txtPhone;
     Parent fxmlEdit;
    private FXMLLoader fxmlLoader = new FXMLLoader();
    private EditDialogController editDialogController;
    private Stage editDialogStage;

    @FXML
    private void toMenu(ActionEvent event) throws IOException {

        Parent page1 = FXMLLoader.load(getClass().getResource("../../mainMenu/sampleMenu.fxml"));
        Scene tableScene = new Scene(page1);
        Stage window = (Stage)((Node)event.getSource()).getScene().getWindow();
        window.setScene(tableScene);
        window.show();
    }


//    private EditDialogController editController;
//
//    public Controller() {
//        this.editController = new EditDialogController(this);
//    }
    @FXML
    private void initialize() {

//        tableAddressBook.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE); // how many people can you select

        columnFio.setCellValueFactory(new PropertyValueFactory<Person, String>("name"));
        columnPhone.setCellValueFactory(new PropertyValueFactory<Person, String>("number")); // method go to getter

        addressBookImpl.fillTestData();
        tableAddressBook.setItems(addressBookImpl.getPersonList());
        updateCountLabel();
    }
//    tableAddressBook.setOnMouseClicked(new EventHandler<MouseEvent>() {
//        public void handle(MouseEvent event) {
//            if (event.getClickedCount () == 2) {
//                editDialogController.setPerson((Person) tableAddressBook.getSelectionModel().getSelectedItem());
//                showDialog();
//            }
//        }
//    }


    private void updateCountLabel() {
        labelCount.setText("number of String " + addressBookImpl.getPersonList().size());


    }


    public void showDialog(ActionEvent actionEvent) {
        Object source = actionEvent.getSource();

        if (!(source instanceof Button)) {
            return;
        }
        Button clickedButton = (Button) source;
        Person selectedPerson = (Person) tableAddressBook.getSelectionModel().getSelectedItem();

        switch (clickedButton.getId()) {
            case "btnAdd":
                startNewWindow(actionEvent);
                System.out.println("add " + selectedPerson);
                break;

            case "btnEdit":
                startNewWindow(actionEvent);
//                main.putPerson(selectedPerson);

                System.out.println("edit " + selectedPerson);

                break;

            case "btnDelete":
                if(!selectedPerson.equals("")){
                    addressBookImpl.delete(selectedPerson);
                }
                System.out.println("delete " + selectedPerson);
                break;
        }

    }

    private void initLoader() {
        try {
            fxmlLoader.setLocation(getClass().getResource("edit.table.fxml"));
            fxmlEdit = fxmlLoader.load();
            editDialogController = fxmlLoader.getController();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    private void startNewWindow(ActionEvent actionEvent){

        try {
             editDialogStage = new Stage();
            fxmlEdit = FXMLLoader.load(getClass().getResource("edit.fxml"));
            editDialogStage.setTitle("Редактирование записи");
            editDialogStage.setMinHeight(150);
            editDialogStage.setMinWidth(300);
            editDialogStage.setResizable(false);
            editDialogStage.setScene(new Scene(fxmlEdit));
            editDialogStage.initModality(Modality.WINDOW_MODAL); // init modality of the window
            editDialogStage.initOwner(((Node) actionEvent.getSource()).getScene().getWindow()); // init main window
            editDialogStage.show();


        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void addPerson(){

    }
}


