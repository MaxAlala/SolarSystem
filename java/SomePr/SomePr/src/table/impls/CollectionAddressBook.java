package table.impls;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

public class CollectionAddressBook implements AddressBook {
    public ObservableList<Person> personList = FXCollections.observableArrayList(); // allow you put, change the info into the table(table.fxml)!


    @Override
    public void add(Person person) { personList.add(person); }

    @Override
    public void update(Person person) {


    }

    @Override
    public void delete(Person person) { personList.remove(person);
    }

    public void print(){
        int number = 0;
        System.out.println();
        for(Person person : personList) {
            number++;
            System.out.println(number+" ) fio = "+ person.getName() + "; phone = "+ person.getNumber());

        }

    }

    public void fillTestData() {
        personList.add(new Person("07.12.12 & Flappy", "3"));
        personList.add(new Person("31.12.12 & Flappy", "4"));
        personList.add(new Person("09.12.12 & Flappy", "6"));
        personList.add(new Person("18.12.12 & Flappy", "8"));
        personList.add(new Person("18.12.12 & arithmetic", "132"));
    }

    public ObservableList<Person> getPersonList() {
        return personList;
    }
}
