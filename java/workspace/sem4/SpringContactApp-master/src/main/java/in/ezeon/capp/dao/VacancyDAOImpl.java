package in.ezeon.capp.dao;

import in.ezeon.capp.domain.Contact;
import in.ezeon.capp.domain.Vacancy;
import in.ezeon.capp.rm.VacancyRowMapper;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import org.springframework.jdbc.core.namedparam.MapSqlParameterSource;
import org.springframework.jdbc.core.namedparam.SqlParameterSource;
import org.springframework.jdbc.support.GeneratedKeyHolder;
import org.springframework.jdbc.support.KeyHolder;
import org.springframework.stereotype.Repository;

/**
 *
 * @author Vikram
 */
@Repository
public class VacancyDAOImpl extends BaseDAO implements VacancyDAO {

//       private Integer id;
//    private Integer owner_id;
//    private Integer type_id;
//    private Integer profession_id;
//    private String descr;
    @Override
    public void save(Vacancy c) {
        String sql = "INSERT INTO vacancy(id, owner_id, type_id, profession_id, descr) VALUES(:id, :owner_id, :type_id, :profession_id, :descr)";
        Map m = new HashMap();
        m.put("id", c.getId());
        m.put("owner_id", c.getOwner_id());
        m.put("type_id", c.getType_id());
        m.put("profession_id", c.getProfession_id());
        m.put("descr", c.getDescr());
   
        SqlParameterSource ps = new MapSqlParameterSource(m);
        KeyHolder kh = new GeneratedKeyHolder();
        getNamedParameterJdbcTemplate().update(sql, ps, kh);
        c.setId(kh.getKey().intValue());
    }

    @Override
    public void update(Vacancy c) {
        String sql = "UPDATE vacancy SET id=:id, owner_id=:owner_id, type_id=:type_id, profession_id=:profession_id, descr=:descr WHERE id=:id";
        Map m = new HashMap();
       m.put("id", c.getId());
        m.put("owner_id", c.getOwner_id());
        m.put("type_id", c.getType_id());
        m.put("profession_id", c.getProfession_id());
        m.put("descr", c.getDescr());
        getNamedParameterJdbcTemplate().update(sql, m);
    }

    @Override
    public void delete(Vacancy c) {
        this.delete(c.getId());
    }

    @Override
    public void delete(Integer id) {
        String sql = "DELETE FROM vacancy WHERE id=?";
        getJdbcTemplate().update(sql, id);
    }

    @Override
    public Vacancy findById(Integer id) {
        String sql = "SELECT id, owner_id, type_id, profession_id, descr FROM vacancy WHERE id=?";
        return getJdbcTemplate().queryForObject(sql, new VacancyRowMapper(), id);
    }

    @Override
    public List<Vacancy> findAll() {
        String sql = "SELECT id, owner_id, type_id, profession_id, descr FROM vacancy";
        return getJdbcTemplate().query(sql, new VacancyRowMapper());
    }

    @Override
    public List<Vacancy> findByProperty(String propName, Object propValue) {
        String sql = "SELECT id, owner_id, type_id, profession_id, descr FROM vacancy WHERE "+propName+"=?";
        return getJdbcTemplate().query(sql, new VacancyRowMapper(), propValue);
    }

}
