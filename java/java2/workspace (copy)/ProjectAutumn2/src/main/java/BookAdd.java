import somePackage.beans.BookList;
import somePackage.db.Database;

import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.Part;
import java.io.IOException;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;


@WebServlet("/BookAdd")
@MultipartConfig(maxFileSize = 16177215)
public class BookAdd extends HttpServlet {
    private static final long serialVersionUTD =1L;

    public BookAdd() {
        super();
    }

    protected void doPost(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws javax.servlet.ServletException, IOException {
        BookList bookList = new BookList();

//        String name = null;
//        String price = null;
//        String Planet = null;
//        int count =0;
//        int year = 0;
//        String type = null;
//        int id = 0;
//        System.out.println(id);
//        System.out.println(type);
//        System.out.println(name);

//        List items = upload.parseRequest(request);
//        Iterator<FileItem> iter = items.iterator();
//        while (iter.hasNext()) {
//            FileItem item = iter.next();
//
//            if (item.isFormField()) {
//                processFormField(item);
//            } else {
//                processUploadedFile(item);
//            }
//        }

        String name = request.getParameter("Name");
        int price = Integer.parseInt(request.getParameter("Price"));
        String Planet = request.getParameter("Planet");
        int count =Integer.parseInt(request.getParameter("Count"));
        int year = Integer.parseInt(request.getParameter("Year"));
        String type = request.getParameter("Type");
        int id = Integer.parseInt(request.getParameter("id"));
        Part filePart = request.getPart("image");
        System.out.println(filePart);

                System.out.println(name);
        System.out.println(price);
        System.out.println(Planet);
        System.out.println(count);
        System.out.println(year);
        System.out.println(type);
        System.out.println(id);



//        FileItemFactory factory = new DiskFileItemFactory();
//
//
//        ServletFileUpload upload = new ServletFileUpload( factory );
//
//        List<FileItem> items = null;
//        try {
//             items = new ServletFileUpload(new DiskFileItemFactory()).parseRequest(new ServletRequestContext(request));
//        } catch (FileUploadException e) {
//            e.printStackTrace();
//        }
//
//        for( FileItem uploadItem : items )
//        {
//            if( uploadItem.isFormField() )
//            {
//                switch (uploadItem.getFieldName()){
//                    case "Name":  name = uploadItem.getString();
//                    break;
//                    case "Price": price = uploadItem.getString();
//                    break;
//                    case "Planet":  Planet = uploadItem.getString();
//                        break;
//                    case "Count": count = Integer.parseInt(uploadItem.getString());
//                        break;
//                    case "Year":  year = Integer.parseInt(uploadItem.getString());
//                        break;
//                    case "Type": type = uploadItem.getString();
//                        break;
//                    case "id": id = Integer.parseInt(uploadItem.getString());
//                        break;
//
//                }
//                System.out.println(uploadItem.getFieldName());
//                System.out.println(uploadItem.getString());
//            } else{
//                System.out.println(uploadItem.getFieldName());
//            }
//        }

//        long id = Long.parseLong(request.getParameter("id"));
//        byte[] image = request.getParameter("image");
//        Part filePart = request.getPart("image");
//        byte[] image =  filePart;
//        Book book = new Book();
//        book.setPrice(price);
//        book.setPublisher(Planet);
//        book.setCount(count);
//        book.setPublishDate(year);
//        book.setId(id);
//        book.setName(name);


//        bookList.updateBooks(book);
//        String title=(request.getParameter("title"));
//        Part filePart = request.getPart("image");
//        System.out.println(filePart.getName());
        InputStream inputStream = null;
        long fileSize = 0;
        String fileContent = null;
        if (filePart != null)
        {

            System.out.println(filePart.getName());
            System.out.println(filePart.getSize());
            System.out.println(filePart.getContentType());

            inputStream = filePart.getInputStream();
            fileSize = filePart.getSize();
            fileContent = filePart.getContentType();
        }


        try
        {
            ResultSet rs = null;
            Connection conn= Database.getConnection();
            PreparedStatement   statement = conn.prepareStatement("select * from planet where name = ?");
            statement.setString(1, Planet);
//            ResultSet rs = st.executeQuery(query);

            rs = statement.executeQuery();

            int planet_id = 8;
            while (rs.next()) {

                planet_id = rs.getInt("id");
                String nameP = rs.getString("name");

                System.out.println("planet_id : " + planet_id);
                System.out.println("nameP : " + nameP);

            }

            statement = conn.prepareStatement("select * from type where name = ?");
            statement.setString(1, type);
            rs = statement.executeQuery();

            int type_id = 8;
            while (rs.next()) {

                type_id = rs.getInt("id");
                String nameT = rs.getString("name");

                System.out.println("type_id : " + type_id);
                System.out.println("nameT : " + nameT);

            }

//            Connection conn= Database.getConnection();

            String sql = "INSERT INTO unit (name,price,planet_id,count,publish_year, image, author_id, genre_id) values (?, ?, ?, ?, ?, ?, ?, ?)";
            statement = conn.prepareStatement(sql);

            statement.setString(1, name);
            statement.setInt(2, price);
            statement.setInt(3, planet_id);
            statement.setInt(4, count);
            statement.setInt(5, year);

            if (inputStream != null)
            {
                statement.setBlob(6, inputStream);
            }
            statement.setInt(7, id  );
            statement.setInt(8, type_id);

            int row = statement.executeUpdate();

            response.sendRedirect("/pages/personalArea.jsp");
        }catch(Exception e){e.printStackTrace();}
    }



    protected void doGet(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws javax.servlet.ServletException, IOException {
    }
}
