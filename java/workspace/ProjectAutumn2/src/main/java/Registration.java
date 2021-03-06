import somePackage.db.Database;
import somePackage.hashmethod.HashMethod;

import javax.servlet.RequestDispatcher;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpSession;
import javax.servlet.http.Part;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;


@WebServlet("/Registration")
@MultipartConfig(maxFileSize = 16177215)
public class Registration extends javax.servlet.http.HttpServlet {
    private static final long serialVersionUTD =1L;

    public Registration() {
        super();
    }

    protected void doPost(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws javax.servlet.ServletException, IOException {
        try {
            String fio = request.getParameter("user");
            String password = request.getParameter("password");
            String hashedPassword = HashMethod.byteArrayToHexString(password.getBytes());
            int yourMoney = Integer.parseInt(request.getParameter("money"));
            String role = "1";
            Part part = request.getPart("image");
            System.out.println(part);
            InputStream inputStream = null;
            if (part != null)
            {

                System.out.println(part.getName());
                System.out.println(part.getSize());
                System.out.println(part.getContentType());

                inputStream = part.getInputStream();

            }


//            "INSERT INTO `leute1`.`users` (`name`, `password`, `role`) VALUES ('Max', '12341234', '1')"
            String sql = "insert into proprietor(fio,password,role, image, credits) value(?,?,?,?,?)";
//            String sql2 =  "INSERT INTO `leute1`.`users` (`name`, `password`, `role`) VALUES ('Max', '12341234', '1')";

            Connection conn = Database.getConnection();
            PreparedStatement ps = conn.prepareStatement(sql);
            ps.setString(1, fio);
            ps.setString(2, hashedPassword);
            ps.setString(3, role);
            ps.setBlob(4, inputStream);
            ps.setInt(5, yourMoney);
            ps.executeUpdate();
//            PrintWriter out = response.getWriter();
//            out.println("You was successfully registered");


            {RequestDispatcher rd = request.getRequestDispatcher("index.jsp");
                rd.include(request, response);}
//            out.println("You was successfully registered");

        } catch (SQLException e) {
            e.printStackTrace();
            System.out.println(124);
        }

    }

    protected void doGet(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws javax.servlet.ServletException, IOException {
    }


}
