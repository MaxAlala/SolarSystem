package in.ezeon.capp.rm;

import in.ezeon.capp.domain.Contact;
import in.ezeon.capp.domain.Vacancy;
import java.sql.ResultSet;
import java.sql.SQLException;
import org.springframework.jdbc.core.RowMapper;

/**
 *
 * @author Vikram
 */
public class VacancyRowMapper implements RowMapper<Vacancy>{
    @Override
    public Vacancy mapRow(ResultSet rs, int i) throws SQLException {
        Vacancy c=new Vacancy();
        c.setId(rs.getInt("id"));
        c.setOwner_id(rs.getInt("onwer_id"));
        c.setType_id(rs.getInt("type_id"));
        c.setProfession_id(rs.getInt("profession_id"));
        c.setDescr(rs.getString("descr"));                     
        return c;
    }
    
}
