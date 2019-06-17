package in.ezeon.capp.test;

import in.ezeon.capp.config.SpringRootConfig;
import javax.sql.DataSource;
import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.jdbc.core.JdbcTemplate;

/**
 *
 * @author Vikram
 */
public class TestDataSource {  
    public static void main(String[] args) {
        ApplicationContext ctx = new AnnotationConfigApplicationContext(SpringRootConfig.class);
        DataSource ds = ctx.getBean(DataSource.class);
        JdbcTemplate jt = new JdbcTemplate(ds);
        String sql="INSERT INTO worker(`descr`,`name`, `phone`, `email`, `address`, `loginName`, `password`, `role`, `loginStatus`) VALUES(?,?,?,?,?,?,?,?,?)";
        Object[] param = new Object[]{"good worker","Vikram", "9303580884", "vikram@ezeon.net", "Bhopal", "v", "v123", 1,2};
        jt.update(sql, param);
        System.out.println("------SQL executed-----");
    }    
}
