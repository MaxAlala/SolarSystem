package main.java;

import somePackage.beans.Author;
import somePackage.db.Database;

import javax.jms.ServerSession;
import javax.jms.Session;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.sql.*;

@WebServlet("/AgreeWithBuyRequest")
@MultipartConfig(maxFileSize = 16177215)
public class AgreeWithBuyRequest extends HttpServlet {
    private static final long serialVersionUTD =1L;

    public AgreeWithBuyRequest() {
        super();
    }

    protected void doPost(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws javax.servlet.ServletException, IOException {

             int receiver_id = Integer.parseInt(request.getParameter("receiver_id"));
        int proprietor_id = Integer.parseInt(request.getParameter("proprietor_id"));
        int unit_count = Integer.parseInt(request.getParameter("unit_count"));
        int unit_id = Integer.parseInt(request.getParameter("unit_id"));
        int message_id = Integer.parseInt(request.getParameter("message_id"));

        System.out.println(receiver_id +" "+proprietor_id+" "+unit_count+" "+unit_id+" "+message_id);


        try
        {
            ResultSet rs = null;
            Connection conn= Database.getConnection();
            PreparedStatement   statement = conn.prepareStatement("select * from unit where id = ?"); ////////take price and count of unit
            statement.setInt(1, unit_id);


            rs = statement.executeQuery();

            int count = 0;
            int price = 0;
            Blob image = null;
            long genre_id = 0;
            long author_id = 0;
            long planet_id = 0;
            int publish_year = 0;
            String name = null;


            while (rs.next()) {

                count = rs.getInt("count");
                 price = rs.getInt("price");
                    image = rs.getBlob("image");
                    genre_id = rs.getLong("genre_id");
                    author_id = rs.getLong("author_id");
                    planet_id = rs.getLong("planet_id");
                    publish_year = rs.getInt("publish_year");
                name = rs.getString("name");

                System.out.println("price : " + price);
                System.out.println("count : " + count);
                System.out.println("genre_id : " + genre_id);
                System.out.println("author_id : " + author_id);
                System.out.println("planet_id : " + planet_id);
                System.out.println("publish_year : " + publish_year);
                System.out.println("name : " + name);
                System.out.println("image : " + image);

            }

            int totalMoney = price * unit_count; ////////absolut price


            statement = conn.prepareStatement("select * from proprietor where id = ?"); ////////take money of new owner
            statement.setInt(1, proprietor_id);
            rs = statement.executeQuery();

            int credits = 0;
            while (rs.next()) {

                credits = rs.getInt("credits");
            }
            System.out.println(credits + "credits of a merch ");
            credits-=totalMoney;
            System.out.println(credits + "after//  credits of a merch  ");

            String sql2 = "UPDATE proprietor SET credits = ? WHERE id = ?";  ////////update money
            statement = conn.prepareStatement(sql2);


            statement.setInt(1, credits);
            statement.setInt(2, proprietor_id);
            System.out.println(statement.executeUpdate() + " money update");




            if(unit_count == count) {

                String sql3 = "UPDATE unit SET author_id = ? WHERE id = ?"; ////////update unit s owner

                statement = conn.prepareStatement(sql3);

                statement.setInt(1, proprietor_id);
                statement.setInt(2, unit_id);
                System.out.println(statement.executeUpdate() + " unit owner");

            }else{
                count -= unit_count;
                String query = " insert into unit (name, count, price, genre_id, author_id, planet_id, publish_year, image)"
                        + " values (?, ?, ?, ?, ?, ?, ?, ?)";
                statement = conn.prepareStatement(query);

                statement.setString(1, name);
                statement.setInt(2, unit_count);
                statement.setInt(3, price);
                statement.setLong(4, genre_id);
                statement.setLong(5, proprietor_id);
                statement.setLong(6, planet_id);
                statement.setInt(7, publish_year);
                statement.setBlob(8, image);
//                rs = statement.executeUpdate();
                System.out.println(statement.executeUpdate() + "suuccessful created new clone unit");

                String query2 = "UPDATE unit SET count = ? WHERE id = ?"; ////////update counnt of old unit

                statement = conn.prepareStatement(query2);

                statement.setInt(1, count);
                statement.setInt(2, unit_id);
                System.out.println(statement.executeUpdate() + "suuccessful changed count");
            }

            statement = conn.prepareStatement("select * from proprietor where id = ?");  ////////update credits of old owner
            statement.setInt(1, receiver_id);

            System.out.println(statement.executeQuery() + " money of an old guy");

//
//            Author author = new Author();
            while (rs.next()) {

                credits = rs.getInt("credits");
//                 author.setName(rs.getString("fio"));
//                author.setCredits(credits);
            }


            System.out.println(credits + "before//  credits of a old owner  ");



            credits += totalMoney;
            System.out.println(credits + "after//  credits of a old owner  ");

            String sql5 = "UPDATE proprietor SET credits = ? WHERE id = ?";
            statement = conn.prepareStatement(sql5);

            statement.setInt(1, credits);
            statement.setInt(2, receiver_id);
            HttpSession session = request.getSession();
            session.setAttribute("credits", credits);


            System.out.println(statement.executeUpdate());


            String sql6 = "UPDATE businessmessage SET status = ? WHERE id = ?"; ////////update  message s status
            statement = conn.prepareStatement(sql6);

            statement.setBoolean(1, true);
            statement.setInt(2, message_id);
            statement.executeUpdate();
            System.out.println("DEALT!");
            response.sendRedirect("/pages/personalAreaRequests.jsp");



        }catch(Exception e){e.printStackTrace();}
    }



    protected void doGet(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws javax.servlet.ServletException, IOException {
    }
}
