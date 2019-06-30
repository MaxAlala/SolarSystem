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
        <%--<form action="${pageContext.request.contextPath}/SendMessage" method="post" enctype="multipart/form-data">--%>
        <%--<br><input id="UserName" name="UserName" type="text"   placeholder="UserName">--%>
        <%--<br><input id="Text" name="Text"  type="text"  placeholder="Text">--%>
        <%--&lt;%&ndash;<br><input id="Planet" name="Planet" type="text"  placeholder="Planet">&ndash;%&gt;--%>
        <%--&lt;%&ndash;<br><input id="Count" name="Count" type="text"  placeholder="Count">&ndash;%&gt;--%>
        <%--&lt;%&ndash;<br><input id="Year" name="Year" type="text"  placeholder="Year">&ndash;%&gt;--%>
        <%--&lt;%&ndash;<br><input id="image" type="file" name="image" size="200" placeholder="image">&ndash;%&gt;--%>
        <%--&lt;%&ndash;<br><input id="Type" type="text" name="Type" placeholder="Type"/>&ndash;%&gt;--%>
        <%--<br><INPUT id="id" TYPE="text" NAME="id"value="<%= session.getAttribute("id") %>" style="display: none" readonly>--%>
        <%--<br><input  type="submit" name="send">--%>
        <%--</form>--%>


        <sql:setDataSource
                var="myDS"
                driver="com.mysql.jdbc.Driver"
                url="jdbc:mysql://localhost:3306/library?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&serverTimezone=UTC"
                user="root" password="1234qwer"
        />
        <% long id = (long)session.getAttribute("id");  %>

        <sql:query var="listMessages"   dataSource="${myDS}">
            SELECT * FROM friends where proprietor_id = <%= id %>;
        </sql:query>

        <div align="center">
            <table border="1" cellpadding="5">
                <caption><h2>List of your friends</h2></caption>
                <tr>
                    <th>ID</th>
                    <th>your_id</th>
                    <th>your_friend_id</th>
                </tr>


                <c:forEach var="message" items="${listMessages.rows}">

                    <tr>
                        <td><c:out value="${message.id}" /></td>
                        <td><c:out value="${message.proprietor_id}" /></td>
                        <td>   <a href = "<c:url value = "../pages/userInfo.jsp">
                        <c:param name="user_id" value="${message.friend_id}"/>


</c:url>
">  <c:out value="${message.friend_id}" /></a>
</td>

                    </tr>
                </c:forEach>
            </table>
        </div>

    </div>
</div>
</body>
</html>