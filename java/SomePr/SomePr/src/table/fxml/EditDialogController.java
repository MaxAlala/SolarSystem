package table.fxml;

import table.impls.Person;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import static starter.Starter.addressBookImpl;

public class EditDialogController {

    @FXML
private Button btnOk;

    @FXML
    private Button btnCancel;

    @FXML
    private TextField txtName;


    @FXML
    private TextField txtPhone;

    @FXML
    private TableColumn<Person, String> columnFio;

    @FXML
    private TableColumn<Person, String> columnPhone;


    public String getTxtPhone() {
        return txtPhone.getText();
    }

    public void setTxtPhone(String txtPhone) {
        this.txtPhone.setText("txtPhone");
    }

    public String getTxtName() {
        return txtName.getText();
    }

    public void setTxtName(String txtName) {
        this.txtName.setText(txtName);
    }


    private Person person;

    public void actionClose(ActionEvent actionEvent) {
        Node source = (Node) actionEvent.getSource();
        Stage stage = (Stage) source.getScene().getWindow();
        stage.close();
    }

    public void setPerson(ActionEvent actionEvent) {

        String phone = txtPhone.getText();
        String name = txtName.getText();
        addressBookImpl.add(new Person(name, phone));

        }
        public void editPerson() {

        }

    }
