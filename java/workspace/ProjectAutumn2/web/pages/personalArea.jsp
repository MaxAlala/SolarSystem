<%@ page import="somePackage.beans.Author" %>
<%@ page import="somePackage.beans.Book" %>
<%@ page import="java.util.ArrayList" %>
<%@ page import="somePackage.enums.SearchType" %>
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

            </div>
        </div>


        <%}%>



    </div>

</div>



</body>
</html>
