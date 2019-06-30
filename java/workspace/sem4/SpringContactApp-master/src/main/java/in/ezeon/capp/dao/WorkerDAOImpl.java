package in.ezeon.capp.dao;

import in.ezeon.capp.domain.Worker;

import in.ezeon.capp.rm.WorkerRowMapper;
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
public class WorkerDAOImpl extends BaseDAO implements WorkerDAO {

    @Override
    public void save(Worker u) {
        String sql = "INSERT INTO worker(name, phone, email, address, loginName, password, role, loginStatus, descr)"
                + " VALUES(:name, :phone, :email, :address, :loginName, :password, :role, :loginStatus, :descr)";
        Map m = new HashMap();
        m.put("name", u.getName());
        m.put("phone", u.getPhone());
        m.put("email", u.getEmail());
        m.put("address", u.getAddress());
        m.put("loginName", u.getLoginName());
        m.put("password", u.getPassword());
        m.put("role", u.getRole());
        m.put("loginStatus", u.getLoginStatus());
        m.put("descr", u.getDescr());
        KeyHolder kh = new GeneratedKeyHolder();
        SqlParameterSource ps = new MapSqlParameterSource(m);
        super.getNamedParameterJdbcTemplate().update(sql, ps, kh);
        Integer id = kh.getKey().intValue();
        u.setId(id);
    }

    @Override
    public void update(Worker u) {
        String sql = "UPDATE worker "
                + " SET name=:name,"
                + " phone=:phone, "
                + " email=:email,"
                + " address=:address,"
                + " role=:role,"
                + " loginStatus=:loginStatus "
                + "descr = :descr"
                + " WHERE id=:id";
        Map m = new HashMap();
        m.put("name", u.getName());
        m.put("phone", u.getPhone());
        m.put("email", u.getEmail());
        m.put("address", u.getAddress());       
        m.put("role", u.getRole());
        m.put("loginStatus", u.getLoginStatus());
        m.put("id", u.getId());
        m.put("descr", u.getDescr());
        getNamedParameterJdbcTemplate().update(sql, m);
    }

    @Override
    public void delete(Worker u) {
        this.delete(u.getId());
    }

    @Override
    public void delete(Integer id) {
        String sql="DELETE FROM Worker WHERE id=?";
        getJdbcTemplate().update(sql, id);
    }

    @Override
    public Worker findById(Integer id) {
        String sql = "SELECT id, name, phone, email, address, loginName, role, loginStatus, descr"
                + " FROM worker WHERE userId=?";
        Worker u = getJdbcTemplate().queryForObject(sql, new WorkerRowMapper(),id);
        return u;
    }

    @Override
    public List<Worker> findAll() {
           String sql = "SELECT id, name, phone, email, address, loginName, role, loginStatus, descr"
                + " FROM worker";
           /*
           List<User> users = getJdbcTemplate().query(sql, new UserRowMapper());
           return users;
           */
           return getJdbcTemplate().query(sql, new WorkerRowMapper());
    }

    @Override
    public List<Worker> findByProperty(String propName, Object propValue) {
         String sql = "SELECT id, name, phone, email, address, loginName, role, loginStatus, descr"
                + " FROM worker WHERE "+propName+"=?";
         return getJdbcTemplate().query(sql, new WorkerRowMapper(), propValue);
    }

}
