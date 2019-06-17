<%@ page import="somePackage.beans.Book" %>
<%@ page import="java.util.ArrayList" %>
<%@ page pageEncoding="UTF-8" %>

<jsp:useBean id="bookList" class="somePackage.beans.BookList" scope="page"/>


<div class="book_list2">



    <%
        ArrayList<Book> list = null;

        list = bookList.getUnitsByName(author.getName());
    %>
    <h5 style="text-align: left; margin-top:20px;">Найдено книг: <%=list.size() %> </h5>
    <%  session.setAttribute("currentBookList", list);
        for (Book book : list) {
    %>

    <div class="book_infoCH2">
        <div class="book_title">
            <p> <%=book.getName()%></p>
        </div>
        <div class="book_image">
            <a href="#"><img src="<%=request.getContextPath()%>/ShowImage?index=<%=list.indexOf(book)%>" height="180" width="190" alt="Обложка"/></a>
        </div>
        <div class="book_details">
            <form action="${pageContext.request.contextPath}/BookChanger" method="post">
                <br><input name="Name" type="text" value="<%= book.getName() %>"  placeholder="Name">
            <br><input name="Price"  type="text" value="<%= book.getPrice() %>" placeholder="Price">
            <br><input name="Planet" type="text"  value="<%= book.getPublisher() %>" placeholder="Planet">
            <br><input name="Count" type="text" value="<%= book.getCount() %>"  placeholder="Count">
            <br><input name="Year" type="text" value="<%= book.getPublishDate() %>"  placeholder="Year">

                <br><INPUT TYPE="text" NAME="id"value="<%= book.getId() %>" style="display: none" readonly>
                <br><input type="submit" name="change">
            </form>


        </div>
    </div>


    <%}%>



</div>

</div>



</body>
</html>
