<%@page import="somePackage.enums.SearchType"%>
<%@page import="java.util.ArrayList"%>
<%@page import="somePackage.beans.Book"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>

<%--<%@include file="../pages/jspf/left_menu.jspf" %>--%>

<%--<jsp:useBean id="bookList" class="somePackage.beans.BookList" scope="page"/>--%>

<%--<%@include file="../pages/jspf/letters.jspf" %>--%>
<jsp:useBean id="bookList" class="somePackage.beans.BookList" scope="page"/>

<div class="book_listBUY">

    <h5 style="text-align: left; margin-top:20px;"> That unit </h5>
    <%  int id = Integer.parseInt(request.getParameter("id"));
        Book book = bookList.getUnitsByUnitId(id);
        System.out.println(session.getAttribute("id"));
    %>

    <div class="book_info">
        <div class="book_title">
            <p> <%=book.getName()%></p>
        </div>
        <div class="book_image">
            <a href="#"><img src="<%=request.getContextPath()%>/LocalShowUnitImage?name2=<%=book.getId()%>" height="180" width="190" alt="Обложка"/></a>
        </div>
        <div class="book_details">
            <br><strong>Price:</strong> <%=book.getPrice()%>
            <br><strong>Planet:</strong> <%=book.getPublisher()%>

            <br><strong>count:</strong> <%=book.getCount()%>
            <br><strong>The year of manufacture:</strong> <%=book.getPublishDate()%>
            <br><strong>Proprietor:</strong> <%=book.getAuthor()%>
            <%--<p style="margin:10px;"> <a href="#">buy</a></p>--%>
            <form action="${pageContext.request.contextPath}/SendBuyRequest" method="post">
                <%--<br><input name="Name" type="text" value="<%= book.getName() %>"  placeholder="Name">--%>

                <%--<br><input name="Planet" type="text"  value="<%= book.getPublisher() %>" placeholder="Planet">--%>
                <br><b>Count</b><input name="count" type="text" value="<%= book.getCount() %>"  placeholder="Count">
                <%--<br><input name="Year" type="text" value="<%= book.getPublishDate() %>"  placeholder="Year">--%>
                    <br><b>comment</b><input name="comment" type="text" value="<%= book.getCount() %>"  placeholder="Count">
                    <INPUT id="proprietor_id" TYPE="text" NAME="proprietor_id" value="<%= session.getAttribute("id") %>" style="display: none" readonly>
                    <INPUT id="receiver_id" TYPE="text" NAME="receiver_id" value="<%= book.getAuthor()%>" style="display: none" readonly>
            <INPUT TYPE="text" NAME="unit_id"value="<%= book.getId() %>" style="display: none" readonly>
                <input type="submit" name="BUY">
            </form>
        </div>
    </div>

</div>

