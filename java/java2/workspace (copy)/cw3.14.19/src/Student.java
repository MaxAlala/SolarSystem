import javax.persistence.*;

/**
 * Created by ma on 13.04.2016.
 */
@Entity
@Table(name="students")
public class Student {
    private long id;
    private String name;
    private Integer year;

    @Override
    public String toString() {
        return "Student{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", year=" + year +
                ", group=" + group +
                '}';
    }

    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE, generator = "students_id_seq")
    @SequenceGenerator(name="students_id_seq", sequenceName="students_id_seq", allocationSize = 1)
    @Column(name = "id")
    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    @Basic
    @Column(name = "name")
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Basic
    @Column(name = "year")
    public Integer getYear() {
        return year;
    }

    public void setYear(Integer year) {
        this.year = year;
    }

    private Group group;

    @ManyToOne
    @JoinColumn(name = "group_id", referencedColumnName = "id")
    public Group getGroup() {
        return group;
    }
    public void setGroup(Group group) {
        this.group = group;
    }



    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Student student = (Student) o;

        if (id != student.id) return false;
        if (!group.equals(student.group)) return false;
        if (name != null ? !name.equals(student.name) : student.name != null) return false;
        if (year != null ? !year.equals(student.year) : student.year != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = (int) (id ^ (id >>> 32));
        result = 31 * result + (name != null ? name.hashCode() : 0);
        result = 31 * result + (year != null ? year.hashCode() : 0);
        result = 31 * result + (int) (group.getId() ^ (group.getId() >>> 32));
        return result;
    }
}
