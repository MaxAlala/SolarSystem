package table.impls;

public class Person {

    public  String number;
     public String name;

    public Person(String name, String number) {
        this.number = number;
        this.name = name;
    }

    public String getNumber() {
        return number;
    }

    public void setNumber(String number) {
        this.number = number;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return "Person{" +
                "number='" + number + '\'' +
                ", name='" + name + '\'' +
                '}';
    }
}
