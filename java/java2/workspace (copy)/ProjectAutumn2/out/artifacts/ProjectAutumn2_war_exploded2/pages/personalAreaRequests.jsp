<%@ taglib prefix="sql" uri="http://java.sun.com/jsp/jstl/sql" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<sql:setDataSource
        var="myDS"
        driver="com.mysql.jdbc.Driver"
        url="jdbc:mysql://localhost:3306/library?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&serverTimezone=UTC"
        user="root" password="1234qwer"
/>
<% long id = (long)session.getAttribute("id");
    System.out.println(id);%>

<sql:query var="listMessages"   dataSource="${myDS}">
    SELECT * FROM businessmessage where receiver_id= <%= id  %>;
</sql:query>

<div align="center">
    <table border="1" cellpadding="5">
        <caption><h2>List of your messages</h2></caption>
        <tr>
            <th>ID</th>
            <th>comment</th>
            <th>unit_count</th>
            <th>unit_id</th>
            <th>receiver_id</th>
            <th>proprietor_id</th>

            <th>status</th>
        </tr>
        <c:forEach var="message" items="${listMessages.rows}">
            <tr>
                <td><c:out value="${message.id}" /></td>
                <td><c:out value="${message.comment}" /></td>
                <td><c:out value="${message.unit_count}" /></td>
                <td><c:out value="${message.unit_id}" /></td>
                <td><c:out value="${message.receiver_id}" /></td>
                <td><c:out value="${message.proprietor_id}" /></td>
                <td><c:out value="${message.status}" /></td>
                <td><form  method="post" action="${request.contextPath}/AgreeWithBuyRequest?message_id=${message.id}&receiver_id=${message.receiver_id}&proprietor_id=${message.proprietor_id}&unit_count=${message.unit_count}&unit_id=${message.unit_id}">
                    <input type="submit" value="accept">
                </form></td>
            </tr>

            <%--<a href="<%=request.getContextPath()%>/AgreeWithBuyRequest?message_id=${message.id}&receiver_id=${message.receiver_id}&proprietor_id=${message.proprietor_id}&unit_count=${message.unit_count}&unit_id=${message.unit_id}">Accept</a>--%>
        </c:forEach>
    </table>
</div>
</body>
</html>
