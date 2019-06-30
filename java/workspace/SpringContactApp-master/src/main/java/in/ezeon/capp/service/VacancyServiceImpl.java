package in.ezeon.capp.service;

import in.ezeon.capp.dao.BaseDAO;
import in.ezeon.capp.dao.ContactDAO;
import in.ezeon.capp.domain.Contact;
import in.ezeon.capp.domain.Vacancy;
import in.ezeon.capp.rm.VacancyRowMapper;
import in.ezeon.capp.util.StringUtil;
import java.util.List;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

/**
 *
 * @author Vikram
 */
@Service
public class VacancyServiceImpl extends BaseDAO implements VacancyService{
    
    @Autowired
    private VacancyDAO vacancyDAO;
    
    @Override    
    public void save(Vacancy c) {
        vacancyDAO.save(c);
    }

    @Override
    public void update(Contact c) {
        vacancyDAO.update(c);
    }

    @Override
    public void delete(Integer id) {
        vacancyDAO.delete(id);
    }

    @Override
    public void delete(Integer[] cotactIds) {
        String ids = StringUtil.toCommaSeparatedString(cotactIds);
        String sql = "DELETE FROM contact WHERE contactId IN("+ids+")";
        getJdbcTemplate().update(sql);
    }

    @Override
    public List<Vacancy> findUserContact(Integer id) {
        return vacancyDAO.findByProperty("id", id);
    }

    @Override
    public List<Vacancy> findUserContact(Integer id, String txt) {
        String sql = "SELECT contactId, userId, name, phone, email, address, remark FROM contact WHERE userId=? AND (name LIKE '%"+txt+"%' OR address LIKE '%"+txt+"%' OR phone LIKE '%"+txt+"%' OR email LIKE '%"+txt+"%' OR remark LIKE '%"+txt+"%')";
        return getJdbcTemplate().query(sql, new VacancyRowMapper(),id); 
    }

    @Override
    public Vacancy findById(Integer id) {
        return vacancyDAO.findById(id);
    }
    
}
