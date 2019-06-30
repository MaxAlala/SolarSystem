import somePackage.beans.Author;
import somePackage.hashmethod.HashMethod;

import javax.servlet.RequestDispatcher;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.*;


@WebServlet("/Login")

public class Login extends HttpServlet {
    private static final long serialVersionUTD =1L;

    public Login() {
        super();
    }

    protected void doPost(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws javax.servlet.ServletException, IOException {
        try {
            String name = request.getParameter("user");
            String password = request.getParameter("password");
            String hashedPassword = HashMethod.byteArrayToHexString(password.getBytes());
            String role = "1";
            String dbName = null;
            String dbPassword = null;
            Byte [] image = null;
            int credits = 0;
            int id = 0;
//
//            boolean remember_me_is_checked = (request.getParameter("rememberMe")!=null);


//            Cookie c = new Cookie("login", encodeString(uuid));
//            c.setMaxAge(365 * 24 * 60 * 60); // one year
//            servletResponse.addCookie(c);
//
////            if(remember_me_is_checked)
////            {
//                Cookie c = new Cookie("userid", name);
//                c.setMaxAge(24*60*60);
//                response.addCookie(c);  // response is an instance of type HttpServletReponse
//            }


//            "INSERT INTO `leute1`.`users` (`name`, `password`, `role`) VALUES ('Max', '12341234', '1')"
            String sql = "select * from proprietor where fio=? and password=?";
//            String sql2 =  "INSERT INTO `leute1`.`users` (`name`, `password`, `role`) VALUES ('Max', '12341234', '1')";
            Class.forName("com.mysql.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/library?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&serverTimezone=UTC", "root","1234qwer");
            PreparedStatement ps = conn.prepareStatement(sql);
            ps.setString(1, name);
            ps.setString(2, hashedPassword);
            ResultSet rs = ps.executeQuery();
            Author author = new Author();
            while(rs.next()){
                author.setId(rs.getInt(1));
                author.setName(rs.getString(2));
                dbPassword = rs.getString(4);
                author.setCredits(rs.getInt(6));
                author.setImage(rs.getBytes(5));
                author.setRole(rs.getInt(7));
                System.out.println(author.getName() + "  " + dbPassword +" " + author.getRole() + author.getCredits());
            }

            PrintWriter out = response.getWriter();
            if(rs != null) {
                out.println("You was successfully logged");
                HttpSession session = request.getSession();
                session.setAttribute("author", author);
                session.setAttribute("fio", author.getName());
                response.sendRedirect("pages/main.jsp");
                session.setAttribute("id", author.getId());
                session.setAttribute("credits", author.getCredits());

            } else
            {RequestDispatcher rd = request.getRequestDispatcher("index.jsp");
            rd.include(request, response);}
//            out.println("You was successfully registered");

        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
            System.out.println(124);
        }

    }

    protected void doGet(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws javax.servlet.ServletException, IOException {
    }


}
