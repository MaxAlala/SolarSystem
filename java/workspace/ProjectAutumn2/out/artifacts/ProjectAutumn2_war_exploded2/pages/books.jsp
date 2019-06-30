<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@page import="somePackage.enums.SearchType"%>
<%@page import="java.util.ArrayList"%>
<%@page import="somePackage.beans.Book"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>

<%@include file="../pages/jspf/left_menu.jspf" %>

<%--<jsp:useBean id="bookList" class="somePackage.beans.BookList" scope="page"/>--%>

<%@include file="../pages/jspf/letters.jspf" %>

<div class="book_list">



    <%
        ArrayList<Book> list = null;

        if (request.getParameter("genre_id") != null) {
            long genreId = Long.valueOf(request.getParameter("genre_id"));
            list = bookList.getBooksByGenre(genreId);
        } else if (request.getParameter("letter") != null) {
            String letter = request.getParameter("letter");
            session.setAttribute("letter", letter);
            list = bookList.getBooksByLetter(letter);
        } else if (request.getParameter("search_string") != null) {
            String searchStr = request.getParameter("search_string");
            SearchType type = SearchType.TITLE;
            if (request.getParameter("search_option").equals("author")) {
                type = SearchType.AUTHOR;
            }

            if (searchStr != null && !searchStr.trim().equals("")) {
                list = bookList.getBooksBySearch(searchStr, type);
            }
        }
       %>
    <h5 style="text-align: left; margin-top:20px;">Найдено книг: <%=list.size() %> </h5>
              <%  session.setAttribute("currentBookList", list);
                for (Book book : list) {

    %>

    <div class="book_info">
        <div class="book_title">
            <p> <%=book.getName()%></p>
        </div>
        <div class="book_image">
            <a href="#"><img src="<%=request.getContextPath()%>/ShowImage?index=<%=list.indexOf(book)%>" height="180" width="190" alt="Обложка"/></a>
        </div>
        <div class="book_details">
            <br><strong>Price:</strong> <%=book.getPrice()%>
            <br><strong>Planet:</strong> <%=book.getPublisher()%>

            <br><strong>count:</strong> <%=book.getCount()%>
            <br><strong>The year of manufacture:</strong> <%=book.getPublishDate()%>
            <br><strong>Proprietor:</strong><a href = "<c:url value = "../pages/userInfoN.jsp">
                        <c:param name="user_name" value="<%=book.getAuthor()%>"/></c:url>
                        ">  <c:out value="<%=book.getAuthor()%>" /></a>
            <p style="margin:10px;"> <a href="buy.jsp?id=<%=book.getId()%>">buy</a></p>
        </div>
    </div>


    <%}%>



</div>
