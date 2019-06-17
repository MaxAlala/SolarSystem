<%--
  Created by IntelliJ IDEA.
  User: BETELGEIZE
  Date: 9/6/2018
  Time: 6:36 AM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Cabinet</title>
</head>
<body>
<%
    response.setHeader("Cache-Control", "no-cache, no-store, must-revalidate");
    if(session.getAttribute("fio") == null) {
        response.sendRedirect("login.jsp");
    }
%>
 Your cabinet!
<iframe width="560" height="315" src="https://www.youtube.com/embed/sTvY9Llqtms" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe>
</body>
</html>
