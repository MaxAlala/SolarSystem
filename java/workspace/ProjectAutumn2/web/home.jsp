<%--
  Created by IntelliJ IDEA.
  User: BETELGEIZE
  Date: 9/6/2018
  Time: 6:31 AM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Hello!</title>
</head>
<body>
<%
    RequestDispatcher dispatcher = request.getRequestDispatcher("/login.jsp");
    dispatcher.forward(request, response);
%>
 HELLOY! ${username}
<a href = "cabinet.jsp">Your cabinet</a>

<form action = "Logout">
    <input type ="submit" value="Logout">
</form>

</body>
</html>
