package main.java;

import somePackage.beans.Author;
import somePackage.beans.Book;
import somePackage.beans.BookList;

import javax.servlet.RequestDispatcher;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.*;


@WebServlet("/BookChanger")

public class BookChanger extends HttpServlet {
    private static final long serialVersionUTD =1L;

    public BookChanger() {
        super();
    }

    protected void doPost(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws javax.servlet.ServletException, IOException {
        BookList bookList = new BookList();

            String name = request.getParameter("Name");
            String price = request.getParameter("Price");
            String Planet = request.getParameter("Planet");
        int count = Integer.parseInt(request.getParameter("Count"));
        int year = Integer.parseInt(request.getParameter("Year"));
        long id = Long.parseLong(request.getParameter("id"));

        Book book = new Book();
        book.setPrice(price);
        book.setPublisher(Planet);
        book.setCount(count);
        book.setPublishDate(year);
        book.setId(id);
        book.setName(name);

//            String dbName = null;
//            String dbPassword = null;
//            Byte [] image = null;
//            int credits = 0;
//            int id = 0;

        bookList.updateBooks(book);
        response.sendRedirect("/pages/personalArea.jsp");

    }

    protected void doGet(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) throws javax.servlet.ServletException, IOException {
    }
}
