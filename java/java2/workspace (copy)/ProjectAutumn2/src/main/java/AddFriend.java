import somePackage.beans.BookList;
import somePackage.db.Database;

import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;


@WebServlet("/AddFriend")
@MultipartConfig(maxFileSize = 16177215)
public class AddFriend extends HttpServlet {
    private static final long serialVersionUTD =1L;

    public AddFriend() {
        super();
    }

    protected void doPost(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws javax.servlet.ServletException, IOException {
        BookList bookList = new BookList();

        String friend_name = request.getParameter("friend_name");
        int friend_id = Integer.parseInt(request.getParameter("friend_id"));
        long id = (Long) request.getSession().getAttribute("id");


        System.out.println(friend_id);
        System.out.println(id);



        ResultSet rs = null;
        Connection conn= Database.getConnection();
        PreparedStatement   statement = null;

        String sql = "INSERT INTO friends (proprietor_id, friend_id) values (?, ?)";

        try {
            statement = conn.prepareStatement(sql);
        } catch (SQLException e) {
            e.printStackTrace();
        }

        try {
            statement.setLong(1, id);
            statement.setInt(2, friend_id);
        } catch (SQLException e) {
            e.printStackTrace();
        }

        try {
            int row = statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        System.out.println("friend was added");
        response.sendRedirect("/pages/userInfoN.jsp?user_name=" + friend_name);
    }


    protected void doGet(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws javax.servlet.ServletException, IOException {
    }
}