package main.java;

import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.FileItemFactory;
import org.apache.commons.fileupload.FileUploadException;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;
import org.apache.commons.fileupload.servlet.ServletRequestContext;
import somePackage.beans.Author;
import somePackage.beans.Book;
import somePackage.beans.BookList;
import somePackage.db.Database;

import javax.servlet.RequestDispatcher;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpSession;
import javax.servlet.http.Part;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.sql.*;
import java.util.Iterator;
import java.util.List;


@WebServlet("/SendMessage")
@MultipartConfig(maxFileSize = 16177215)
public class SendMessage extends HttpServlet {
    private static final long serialVersionUTD =1L;

    public SendMessage() {
        super();
    }

    protected void doPost(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws javax.servlet.ServletException, IOException {
        BookList bookList = new BookList();


        String name = request.getParameter("UserName");
        String text = request.getParameter("Text");
//        String Planet = request.getParameter("Planet");
//        int count =Integer.parseInt(request.getParameter("Count"));
//        int year = Integer.parseInt(request.getParameter("Year"));
//        String type = request.getParameter("Type");
        int id = Integer.parseInt(request.getParameter("id"));
//        Part filePart = request.getPart("image");
//        System.out.println(filePart);

        System.out.println(name);
        System.out.println(text);
        System.out.println(id);

//        InputStream inputStream = null;
//        long fileSize = 0;
//        String fileContent = null;
//        if (filePart != null)
//        {
//
//            System.out.println(filePart.getName());
//            System.out.println(filePart.getSize());
//            System.out.println(filePart.getContentType());
//
//            inputStream = filePart.getInputStream();
//            fileSize = filePart.getSize();
//            fileContent = filePart.getContentType();
//        }

        try
        {
            ResultSet rs = null;
            Connection conn= Database.getConnection();
            PreparedStatement   statement = conn.prepareStatement("select * from proprietor where fio = ?");
            statement.setString(1, name);
//            ResultSet rs = st.executeQuery(query);

            rs = statement.executeQuery();

            int proprietor_id = 8;
            while (rs.next()) {

                proprietor_id = rs.getInt("id");
                String nameProp = rs.getString("fio");

                System.out.println("proprietor_id : " + proprietor_id);
                System.out.println("nameProp : " + nameProp);

            }

//            statement = conn.prepareStatement("select * from type where name = ?");
//            statement.setString(1, type);
//            rs = statement.executeQuery();
//
//            int type_id = 8;
//            while (rs.next()) {
//
//                type_id = rs.getInt("id");
//                String nameT = rs.getString("name");
//
//                System.out.println("type_id : " + type_id);
//                System.out.println("nameT : " + nameT);
//
//            }

//            Connection conn= Database.getConnection();

            String sql = "INSERT INTO message (sender_id, receiver_id, Text) values (?, ?, ?)";
            statement = conn.prepareStatement(sql);

            statement.setInt(1, id);
            statement.setInt(2, proprietor_id);
            statement.setString(3, text);

//
//            if (inputStream != null)
//            {
//                statement.setBlob(6, inputStream);
//            }
//            statement.setInt(7, id  );
//            statement.setInt(8, type_id);

            int row = statement.executeUpdate();
            response.sendRedirect("/pages/chatRoomU.jsp");
        }catch(Exception e){e.printStackTrace();}
    }



    protected void doGet(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws javax.servlet.ServletException, IOException {
    }
}
