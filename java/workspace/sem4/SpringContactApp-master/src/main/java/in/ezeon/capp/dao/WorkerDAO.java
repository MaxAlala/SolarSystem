package in.ezeon.capp.dao;

import in.ezeon.capp.domain.Worker;
import java.util.List;

/**
 *
 * @author Vikram
 */
public interface WorkerDAO {

    public void save(Worker u);

    public void update(Worker u);

    public void delete(Worker u);

    public void delete(Integer workerId);

    public Worker findById(Integer workerId);

    public List<Worker> findAll();

    public List<Worker> findByProperty(String propName, Object propValue);
}
