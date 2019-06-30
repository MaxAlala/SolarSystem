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


@WebServlet("/SendBuyRequest")
@MultipartConfig(maxFileSize = 16177215)
public class SendBuyRequest extends HttpServlet {
    private static final long serialVersionUTD =1L;

    public SendBuyRequest() {
        super();
    }

    protected void doPost(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws javax.servlet.ServletException, IOException {
        BookList bookList = new BookList();


        String comment = request.getParameter("comment");
        int proprietor_id = Integer.parseInt(request.getParameter("proprietor_id"));
        String receiver_name = request.getParameter("receiver_id");
        int unit_id = Integer.parseInt(request.getParameter("unit_id"));
        int count = Integer.parseInt(request.getParameter("count"));
//      int price =Integer.parseInt(request.getParameter("price"));
//        int proprietor_id = 0;

        System.out.println(proprietor_id);
        System.out.println(receiver_name);
        System.out.println(unit_id);
        System.out.println(comment);
        System.out.println(count);


//
//        PreparedStatement   statement = null;
//        try
//        {
            ResultSet rs = null;
            Connection conn= Database.getConnection();
        PreparedStatement   statement = null;
        try {
            statement = conn.prepareStatement("select * from proprietor where fio = ?");
        } catch (SQLException e) {
            e.printStackTrace();
        }
        try {
            statement.setString(1, receiver_name);
        } catch (SQLException e) {
            e.printStackTrace();
        }

int receiver_id = 0;
        try {
            rs = statement.executeQuery();


            while (rs.next()) {

//                String nameProp = null;
//                try {
                receiver_id = rs.getInt("id");
//                    nameProp = rs.getString("fio");
//                } catch (SQLException e) {
//                    e.printStackTrace();
//                }

                System.out.println("receiver_id : " + receiver_id);
//                System.out.println("nameProp : " + nameProp);

            }
        } catch (Exception e) {
            e.printStackTrace();
        }

//            String comment = request.getParameter("comment");
//            int proprietor_id = Integer.parseInt(request.getParameter("proprietor_id"));
//            int receiver_id = Integer.parseInt(request.getParameter("receiver_id"));
//            int unit_id = Integer.parseInt(request.getParameter("unit_id"));
//            int count = Integer.parseInt(request.getParameter("count"));
        boolean statusAgree = false;

        String sql = "INSERT INTO businessmessage (proprietor_id, receiver_id, unit_id, comment, unit_count, status) values (?, ?, ?, ?, ?, ?)";
        try {
            statement = conn.prepareStatement(sql);
        } catch (SQLException e) {
            e.printStackTrace();
        }



          try {


            statement.setInt(1, proprietor_id);
            statement.setInt(2, receiver_id);
        statement.setInt(3, unit_id);
        statement.setString(4, comment);
        statement.setInt(5, count);
        statement.setBoolean(6, statusAgree);


        } catch (SQLException e) {
            e.printStackTrace();
        }
//
//            if (inputStream != null)
//            {
//                statement.setBlob(6, inputStream);
//            }
//            statement.setInt(7, id  );
//            statement.setInt(8, type_id);

        try {
            int row = statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        response.sendRedirect("/pages/personalArea.jsp");

    }


    protected void doGet(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws javax.servlet.ServletException, IOException {
    }
}
