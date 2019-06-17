<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="sql" uri="http://java.sun.com/jsp/jstl/sql" %>
<%@ page language="java" contentType="text/html; charset=UTF-8"
         pageEncoding="UTF-8"%>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">

<jsp:useBean id="bookList" class="somePackage.beans.BookList" scope="page"/>

<div class="book_infoCH">
    <div class="book_title">
        <%--<p> <%=book.getName()%></p>--%>
    </div>
    <div class="book_image">
        <%--<a href="#"><img src="<%=request.getContextPath()%>/ShowImage?index=<%=list.indexOf(book)%>" height="180" width="190" alt="Обложка"/></a>--%>
    </div>
    <div class="book_details">


        <sql:setDataSource
                var="myDS"
                driver="com.mysql.jdbc.Driver"
                url="jdbc:mysql://localhost:3306/library?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&serverTimezone=UTC"
                user="root" password="1234qwer"
        />
        <% long id = (long)session.getAttribute("id");  %>

        <sql:query var="listMessages"   dataSource="${myDS}">
            SELECT * FROM message where receiver_id= <%= id %>;
        </sql:query>

        <div align="center">
            <table border="1" cellpadding="5">
                <caption><h2>List of your messages</h2></caption>
                <tr>
                    <th>ID</th>
                    <th>text</th>
                    <th>sender_id</th>
                    <th>receiver_id</th>
                </tr>
                <c:forEach var="message" items="${listMessages.rows}">
                    <tr>
                        <td><c:out value="${message.id}" /></td>
                        <td><c:out value="${message.text}" /></td>
                        <td><c:out value="${message.sender_id}" /></td>
                        <td><c:out value="${message.receiver_id}" /></td>
                    </tr>
                </c:forEach>
            </table>
        </div>

    </div>
</div>
</body>
</html>
