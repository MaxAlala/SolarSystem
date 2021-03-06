package com.example.sweater.domain;

import org.hibernate.validator.constraints.Length;

import javax.persistence.*;
import javax.validation.constraints.NotBlank;
import java.io.Serializable;
import java.util.HashSet;
import java.util.Set;

@Entity
@Table(name = "groups")
public class Group implements Serializable {

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;


    @NotBlank(message = "Please fill the nameofcompany")
    @Length(max = 2048, message = "name too large(more than 2kB)")
    private String name;


    @NotBlank(message = "Please fill the description")
    @Length(max = 2048, message = "description too large(more than 2kB)")
    private String text;
    @Length(max = 255, message = "description too large(more than 255)")
    private String tag;

//    @ManyToOne(fetch = FetchType.EAGER)
    @ManyToOne(targetEntity = User.class, fetch = FetchType.EAGER)
    @JoinColumn(name = "user_id")
    private User author;

    @Column(name="pic")
    private byte[] pic;


    @ManyToMany
    @JoinTable(
            name = "user_group",
            joinColumns = { @JoinColumn(name = "group_id")},
            inverseJoinColumns = { @JoinColumn(name = "user_id")}
    )
    private Set<User> participants = new HashSet<>();

    public Group() {

    }


    public Group(String text, String tag, User author) {
        this.text = text;
        this.tag = tag;
        this.author = author;
    }
    @Length(max = 255, message = "description too large(more than 255)")
    private String filename;

    public String getFilename() {
        return filename;
    }

    public void setFilename(String filename) {
        this.filename = filename;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }

    public String getTag() {
        return tag;
    }

    public void setTag(String tag) {
        this.tag = tag;
    }

    public User getAuthor() {
        return author;
    }

    public void setAuthor(User author) {
        this.author = author;
    }

    public byte[] getPic() {
        return pic;
    }

    public void setPic(byte[] pic) {
        this.pic = pic;
    }

    public Set<User> getParticipants() {
        return participants;
    }

    public void setParticipants(Set<User> participants) {
        this.participants = participants;
    }
}
