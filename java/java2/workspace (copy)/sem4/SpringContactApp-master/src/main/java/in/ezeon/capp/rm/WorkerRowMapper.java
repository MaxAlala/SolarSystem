package in.ezeon.capp.rm;

import in.ezeon.capp.domain.User;
import in.ezeon.capp.domain.Worker;
import java.sql.ResultSet;
import java.sql.SQLException;
import org.springframework.jdbc.core.RowMapper;
/**
 *
 * @author Vikram
 */
public class WorkerRowMapper implements RowMapper<Worker>{
    @Override
    public Worker mapRow(ResultSet rs, int i) throws SQLException {
        Worker u=new Worker();
        u.setId(rs.getInt("id"));
        u.setName(rs.getString("name"));
        u.setPhone(rs.getString("phone"));
        u.setEmail(rs.getString("email"));
        u.setAddress(rs.getString("address"));
        u.setLoginName(rs.getString("loginName"));
        u.setRole(rs.getInt("role"));
        u.setLoginStatus(rs.getInt("loginStatus"));
        u.setDescr(rs.getString("descr"));
        return u;
    }    
}
