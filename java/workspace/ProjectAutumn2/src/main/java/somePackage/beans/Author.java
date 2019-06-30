package somePackage.beans;

import java.util.ArrayList;
import java.util.Arrays;

public class Author {

    private String name;
    private long id;
    private byte[] image;
    private int credits;
    private int role;
    private ArrayList<Book> resources = new ArrayList<>();


    public Author() {
    }

//    public void refreshResourses(){
//
//    }

    public Author(String name, long id) {
        this.name = name;
        this.id = id;
    }

    public byte[] getImage() {
        return image;
    }

    public void setImage(byte[] image) {
        this.image = image;
    }

    public int getCredits() {
        return credits;
    }

    public void setCredits(int credits) {
        this.credits = credits;
    }

    public int getRole() {
        return role;
    }

    public void setRole(int role) {
        this.role = role;
    }

    public ArrayList<Book> getResources() {
        return resources;
    }

    public void setResources(ArrayList<Book> resources) {
        this.resources = resources;
    }

    public long getId() {
        return id;
    }
    
    public void setId(long id) {
        this.id = id;
    }
    
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return "Author{" +
                "name='" + name + '\'' +
                ", id=" + id +
                ", image=" + Arrays.toString(image) +
                ", credits=" + credits +
                ", role=" + role +
                ", resources=" + resources +
                '}';
    }
}
