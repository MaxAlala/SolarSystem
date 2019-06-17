
package in.ezeon.capp.domain;


public class Vacancy {
    private Integer id;
    private Integer owner_id;
    private Integer type_id;
    private Integer profession_id;
    private String descr;

    public Vacancy() {
    }

    
    
    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Integer getOwner_id() {
        return owner_id;
    }

    public void setOwner_id(Integer owner_id) {
        this.owner_id = owner_id;
    }

    public Integer getType_id() {
        return type_id;
    }

    public void setType_id(Integer type_id) {
        this.type_id = type_id;
    }

    public Integer getProfession_id() {
        return profession_id;
    }

    public void setProfession_id(Integer profession_id) {
        this.profession_id = profession_id;
    }

    public String getDescr() {
        return descr;
    }

    public void setDescr(String descr) {
        this.descr = descr;
    }
    
    
    
}
