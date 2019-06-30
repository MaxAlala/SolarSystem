package in.ezeon.capp.dao;

import in.ezeon.capp.domain.Vacancy;
import java.util.List;

/**
 *
 * @author Vikram
 */
public interface VacancyDAO {

    public void save(Vacancy c);

    public void update(Vacancy c);

    public void delete(Vacancy c);

    public void delete(Integer id);

    public Vacancy findById(Integer id);

    public List<Vacancy> findAll();

    public List<Vacancy> findByProperty(String propName, Object propValue);
}
