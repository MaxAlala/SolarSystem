package in.ezeon.capp.dao;

import in.ezeon.capp.domain.worker;
import java.util.List;

/**
 *
 * @author Vikram
 */
public interface UserDAO {

    public void save(worker u);

    public void update(worker u);

    public void delete(worker u);

    public void delete(Integer userId);

    public worker findById(Integer userId);

    public List<worker> findAll();

    public List<worker> findByProperty(String propName, Object propValue);
}
