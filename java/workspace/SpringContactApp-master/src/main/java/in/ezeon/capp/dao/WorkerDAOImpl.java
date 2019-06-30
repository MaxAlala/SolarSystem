package in.ezeon.capp.dao;


import in.ezeon.capp.domain.Worker;
import in.ezeon.capp.rm.UserRowMapper;
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
        Integer userId = kh.getKey().intValue();
        u.setId(userId);
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
                + " WHERE userId=:userId";
        Map m = new HashMap();
        m.put("name", u.getName());
        m.put("phone", u.getPhone());
        m.put("email", u.getEmail());
        m.put("address", u.getAddress());       
        m.put("role", u.getRole());
        m.put("loginStatus", u.getLoginStatus());
        m.put("userId", u.getUserId());
        getNamedParameterJdbcTemplate().update(sql, m);
    }

    @Override
    public void delete(worker u) {
        this.delete(u.getUserId());
    }

    @Override
    public void delete(Integer userId) {
        String sql="DELETE FROM worker WHERE userId=?";
        getJdbcTemplate().update(sql, userId);
    }

    @Override
    public worker findById(Integer userId) {
        String sql = "SELECT userId, name, phone, email, address, loginName, role, loginStatus"
                + " FROM worker WHERE userId=?";
        worker u = getJdbcTemplate().queryForObject(sql, new UserRowMapper(),userId);
        return u;
    }

    @Override
    public List<Worker> findAll() {
           String sql = "SELECT userId, name, phone, email, address, loginName, role, loginStatus"
                + " FROM worker";
           /*
           List<worker> users = getJdbcTemplate().query(sql, new UserRowMapper());
           return users;
           */
           return getJdbcTemplate().query(sql, new UserRowMapper());
    }

    @Override
    public List<Worker> findByProperty(String propName, Object propValue) {
         String sql = "SELECT userId, name, phone, email, address, loginName, role, loginStatus"
                + " FROM worker WHERE "+propName+"=?";
         return getJdbcTemplate().query(sql, new UserRowMapper(), propValue);
    }

}
