package in.ezeon.capp.service;

import in.ezeon.capp.domain.Contact;
import in.ezeon.capp.domain.Vacancy;
import java.util.List;


public interface VacancyService {

    public void save(Vacancy c);

    public void update(Vacancy c);

    public void delete(Integer id);
   

    public void delete(Integer[] ids);
    
    public Vacancy findById(Integer id);


    public List<Vacancy> findUserVacancy(Integer id);

 
    public List<Vacancy> findUserContact(Integer id, String txt);
}
