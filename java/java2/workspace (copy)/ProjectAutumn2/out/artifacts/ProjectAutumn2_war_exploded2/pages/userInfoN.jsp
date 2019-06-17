<%@ page import="somePackage.beans.Author" %>
<%@ page import="somePackage.beans.Book" %>
<%@ page import="java.util.ArrayList" %>
<%@ page import="somePackage.enums.SearchType" %>
<%@ page import="somePackage.beans.AuthorList" %>
<%@ page pageEncoding="UTF-8" %>

<jsp:useBean id="bookList" class="somePackage.beans.BookList" scope="page"/>



<div class="book_list2">



    <%
//        AuthorList authorList = new AuthorList();
//
//        ArrayList<Book> list = null;
//
//
//
//        Author author1 = authorList.getAuthorByName((request.getParameter("user_name")));
        list = bookList.getUnitsById((int)(author1.getId()));
//        request.getSession().setAttribute("nameImage", author1.getName());
    %>

    <div class="user_image">
        <a href="#"><img src="<%=request.getContextPath()%>/LocalShowPersonImage?name2=<%= author1.getName()%>" <% System.out.println(request.getContextPath() + "/LocalShowPersonImage" + author1.getName());%> height="100" width="100" alt="user"/></a>
    </div>
    <h5 style="text-align: left; margin-top:20px;">His units: <%=list.size() %> </h5>
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
            <br><strong>price per unit:</strong> <%=book.getPrice()%>
            <br><strong>Planet</strong> <%=book.getPublisher()%>

            <br><strong>Count:</strong> <%=book.getCount()%>
            <br><strong>The year of manufacture:</strong> <%=book.getPublishDate()%>
            <br><strong>Proprietor:</strong> <%=book.getAuthor()%>
            <p style="margin:10px;"> <a href="buy.jsp?id=<%=book.getId()%>">buy</a></p>
        </div>
    </div>


    <%}%>



</div>

</div>



</body>
</html>