package somePackage.beans;

import somePackage.db.Database;
import somePackage.enums.SearchType;

import java.sql.*;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

public class BookList {

    private ArrayList<Book> bookList = new ArrayList<Book>();

    public void clearBookList(){
        bookList.clear();
    }
    private ArrayList<Book> getBooks(String sql) {

        Statement stmt = null;
        ResultSet rs = null;
        Connection conn = null;

        try {
            conn = Database.getConnection();
            stmt = conn.createStatement();

            rs = stmt.executeQuery(sql);
            while (rs.next()) {
                Book book = new Book();
                book.setId(rs.getLong("id"));
                book.setName(rs.getString("name"));
                book.setGenre(rs.getString("type"));
                book.setPrice(rs.getString("price"));
                book.setAuthor(rs.getString("proprietor"));
                book.setCount(rs.getInt("count"));
                book.setPublishDate(rs.getInt("publish_year"));
                book.setPublisher(rs.getString("planet"));
                book.setImage(rs.getBytes("image"));
                bookList.add(book);
            }

        } catch (SQLException ex) {
            Logger.getLogger(BookList.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            try {
                if (stmt != null) {
                    stmt.close();
                }
                if (rs != null) {
                    rs.close();
                }
                if (conn != null) {
                    conn.close();
                }
            } catch (SQLException ex) {
                Logger.getLogger(BookList.class.getName()).log(Level.SEVERE, null, ex);
            }
        }

        return bookList;
    }

    private Book getBooks2(String sql) {

        Statement stmt = null;
        ResultSet rs = null;
        Connection conn = null;
        Book book = null;
        try {
            conn = Database.getConnection();
            stmt = conn.createStatement();

            rs = stmt.executeQuery(sql);

            while (rs.next()) {
                 book = new Book();
                book.setId(rs.getLong("id"));
                book.setName(rs.getString("name"));
                book.setGenre(rs.getString("type"));
                book.setPrice(rs.getString("price"));
                book.setAuthor(rs.getString("proprietor"));
                book.setCount(rs.getInt("count"));
                book.setPublishDate(rs.getInt("publish_year"));
                book.setPublisher(rs.getString("planet"));
                book.setImage(rs.getBytes("image"));

            }

        } catch (SQLException ex) {
            Logger.getLogger(BookList.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            try {
                if (stmt != null) {
                    stmt.close();
                }
                if (rs != null) {
                    rs.close();
                }
                if (conn != null) {
                    conn.close();
                }
            } catch (SQLException ex) {
                Logger.getLogger(BookList.class.getName()).log(Level.SEVERE, null, ex);
            }
        }

        return book;
    }

    public ArrayList<Book> getAllBooks() {
        return getBooks("select b.id,b.name,b.price,b.count,b.publish_year, p.name as planet, "
                + "a.fio as proprietor, g.name as type, b.image from unit b inner join proprietor a on b.author_id=a.id "
                + "inner join type g on b.genre_id=g.id inner join planet p on b.planet_id=p.id order by b.name");
    }
//        return getBooks("select b.id,b.name,b.isbn,b.page_count,b.publish_year, p.name as publisher, "
//                                + "a.fio as author, g.name as genre, b.image from book b inner join author a on b.author_id=a.id "
//                                + "inner join genre g on b.genre_id=g.id inner join publisher p on b.publisher_id=p.id order by b.name");

    public ArrayList<Book> getBooksByGenre(long id) {
        if (id == 0) {
            return getAllBooks();
        } else {
            return getBooks("select b.id,b.name,b.price,b.count,b.publish_year, p.name as planet, a.fio as proprietor, g.name as type, b.image from unit b "
                    + "inner join proprietor a on b.author_id=a.id "
                    + "inner join type g on b.genre_id=g.id "
                    + "inner join planet p on b.planet_id=p.id "
                    + "where genre_id=" + id + " order by b.name ");
//            return getBooks("select b.id,b.name,b.isbn,b.page_count,b.publish_year, p.name as publisher, a.fio as author, g.name as genre, b.image from book b "
//                    + "inner join author a on b.author_id=a.id "
//                    + "inner join genre g on b.genre_id=g.id "
//                    + "inner join publisher p on b.publisher_id=p.id "
//                    + "where genre_id=" + id + " order by b.name "
//                    + "limit 0,5");
        }
    }

    public ArrayList<Book> getBooksByLetter(String letter) {;
        return getBooks("select b.id,b.name,b.price,b.count,b.publish_year, p.name as planet, a.fio as proprietor, g.name as type, b.image from unit b "
                + "inner join proprietor a on b.author_id=a.id "
                + "inner join type g on b.genre_id=g.id "
                + "inner join planet p on b.planet_id=p.id "
                + "where substr(b.name,1,1)='" + letter + "' order by b.name "
                );
//        return getBooks("select b.id,b.name,b.isbn,b.page_count,b.publish_year, p.name as publisher, a.fio as author, g.name as genre, b.image from book b "
//                + "inner join author a on b.author_id=a.id "
//                + "inner join genre g on b.genre_id=g.id "
//                + "inner join publisher p on b.publisher_id=p.id "
//                + "where substr(b.name,1,1)='" + letter + "' order by b.name "
//                + "limit 0,5");

    }

    public ArrayList<Book> getBooksBySearch(String searchStr, SearchType type) {
        StringBuilder sql = new StringBuilder("select b.id,b.name,b.price,b.count,b.publish_year, p.name as planet, a.fio as proprietor, g.name as type, b.image from unit b "
                + "inner join proprietor a on b.author_id=a.id "
                + "inner join type g on b.genre_id=g.id "
                + "inner join planet p on b.planet_id=p.id ");
//        StringBuilder sql = new StringBuilder("select b.id,b.name,b.isbn,b.page_count,b.publish_year, p.name as publisher, a.fio as author, g.name as genre, b.image from book b "
//                + "inner join author a on b.author_id=a.id "
//                + "inner join genre g on b.genre_id=g.id "
//                + "inner join publisher p on b.publisher_id=p.id ");

        if (type == SearchType.AUTHOR) {
            sql.append("where lower(a.fio) like '%" + searchStr.toLowerCase() + "%' order by b.name ");

        } else if (type == SearchType.TITLE) {
            sql.append("where lower(b.name) like '%" + searchStr.toLowerCase() + "%' order by b.name ");
        }
        sql.append("limit 0,5");


        return getBooks(sql.toString());


    }



    public ArrayList<Book> getUnitsByName(String name){
//        ArrayList<Book> resources = new ArrayList<>();
//        resources.clear();
//
//
//        int s = bookList.size();
//        for (Book book: bookList) {
//            if(book.getAuthor().equals(name))
//                resources.add(book);
//
//        }
//        return resources;
            StringBuilder sql = new StringBuilder("select b.id,b.name,b.price,b.count,b.publish_year, p.name as planet, a.fio as proprietor, g.name as type, b.image from unit b "
                    + "inner join proprietor a on b.author_id=a.id "
                    + "inner join type g on b.genre_id=g.id "
                    + "inner join planet p on b.planet_id=p.id ");
//        StringBuilder sql = new StringBuilder("select b.id,b.name,b.isbn,b.page_count,b.publish_year, p.name as publisher, a.fio as author, g.name as genre, b.image from book b "
//                + "inner join author a on b.author_id=a.id "
//                + "inner join genre g on b.genre_id=g.id "
//                + "inner join publisher p on b.publisher_id=p.id ");


            sql.append("where lower(a.fio) like '%" + name + "%' order by b.name ");
            return getBooks(sql.toString());
            }

    public ArrayList<Book> getUnitsById(int id){
//        ArrayList<Book> resources = new ArrayList<>();
//        resources.clear();
//
//
//        int s = bookList.size();
//        for (Book book: bookList) {
//            if(book.getAuthor().equals(name))
//                resources.add(book);
//
//        }
//        return resources;
        StringBuilder sql = new StringBuilder("select b.id,b.name,b.price,b.count,b.publish_year, p.name as planet, a.fio as proprietor, g.name as type, b.image from unit b "
                + "inner join proprietor a on b.author_id=a.id "
                + "inner join type g on b.genre_id=g.id "
                + "inner join planet p on b.planet_id=p.id ");
//        StringBuilder sql = new StringBuilder("select b.id,b.name,b.isbn,b.page_count,b.publish_year, p.name as publisher, a.fio as author, g.name as genre, b.image from book b "
//                + "inner join author a on b.author_id=a.id "
//                + "inner join genre g on b.genre_id=g.id "
//                + "inner join publisher p on b.publisher_id=p.id ");


        sql.append("where lower(a.id) like '%" + id + "%' order by b.name ");
        return getBooks(sql.toString());
    }



    public String updateBooks(Book book) {
//        imitateLoading();

        PreparedStatement prepStmt = null;
        ResultSet rs = null;
        Connection conn = null;
        String planet_name = book.getPublisher();
        try {
            conn = Database.getConnection();
//            prepStmt = conn.prepareStatement("update unit as b inner join planet as g on b.planet_id = g.id  set b.name=?,   g.name=?, b.publish_year=? where b.id=?");
//            prepStmt = conn.prepareStatement("INSERT INTO `planet`(name,system,wealth) VALUES (?,?,?)");
//            prepStmt.setString(1, book.getPublisher());
//            prepStmt.setString(2, "Solar");
//            prepStmt.setString(3, "Wealth");
//            prepStmt.executeUpdate();

            prepStmt = conn.prepareStatement("select * from planet where name = ?");
            prepStmt.setString(1, book.getPublisher());
//            ResultSet rs = st.executeQuery(query);

            rs = prepStmt.executeQuery();
            int planet_id = 8;
            while (rs.next()) {

                 planet_id = rs.getInt("id");
                String name = rs.getString("name");

                System.out.println("planet_id : " + planet_id);
                System.out.println("name : " + name);

            }

            System.out.println("count: " + book.getCount());
            prepStmt = conn.prepareStatement("update unit set name=?, planet_id=?, count=?, price=?, publish_year=? where id=?");
            prepStmt.setString(1, book.getName());
            prepStmt.setLong(2, planet_id);
            prepStmt.setInt(3, book.getCount());
            prepStmt.setInt(4, Integer.parseInt(book.getPrice()));
            prepStmt.setInt(5, book.getPublishDate());
            prepStmt.setLong(6,book.getId());
//            for (Book book : bookList) {
//                prepStmt.setString(1, book.getName());
//                prepStmt.setString(2, book.getPublisher());
////                prepStmt.setString(3, book.getAuthor());
//                prepStmt.setInt(3, book.getCount());
//                prepStmt.setInt(4, book.getPublishDate());
////                prepStmt.setString(6, book.getPublisher());
////                prepStmt.setString(5, book.getDescr());
//                prepStmt.setLong(5, book.getId());
//                prepStmt.addBatch();
//            }



            prepStmt.executeUpdate();


        } catch (SQLException ex) {
            System.out.println("error");
            Logger.getLogger(BookList.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            System.out.println("error");
            try {
                if (prepStmt != null) {
                    prepStmt.close();
                }
                if (rs != null) {
                    rs.close();
                }
                if (conn != null) {
                    conn.close();
                }
            } catch (SQLException ex) {
                Logger.getLogger(BookList.class.getName()).log(Level.SEVERE, null, ex);
            }
        }

//        try
//        {
//            // create a java mysql database connection
//            String myDriver = "org.gjt.mm.mysql.Driver";
//            String myUrl = "jdbc:mysql://localhost/test";
//            Class.forName(myDriver);
//            Connection conn2 = Database.getConnection();
//
//            // create the java mysql update preparedstatement
//            String query = "update book set name=?, isbn=?, page_count=?, publish_year=? where id=?";
//            PreparedStatement preparedStmt = conn2.prepareStatement(query);
//            preparedStmt.setInt   (1, 6000);
//            preparedStmt.setString(2, "Fred");
//
//            // execute the java preparedstatement
//            preparedStmt.executeUpdate();
//
//            conn.close();
//        }
//        catch (Exception e)
//        {
//            System.err.println("Got an exception! ");
//            System.err.println(e.getMessage());
//        }
//    }
        System.out.println("update was successful");
//        switchEditMode();
        return "books";
    }

    public Book getUnitsByUnitId(int id){

        StringBuilder sql = new StringBuilder("select b.id,b.name,b.price,b.count,b.publish_year, p.name as planet, a.fio as proprietor, g.name as type, b.image from unit b "
                + "inner join proprietor a on b.author_id=a.id "
                + "inner join type g on b.genre_id=g.id "
                + "inner join planet p on b.planet_id=p.id ");

        sql.append("where lower(b.id) like '%" + id + "%' order by b.name ");
        getBooks2(sql.toString());
        return  getBooks2(sql.toString());
    }



}

