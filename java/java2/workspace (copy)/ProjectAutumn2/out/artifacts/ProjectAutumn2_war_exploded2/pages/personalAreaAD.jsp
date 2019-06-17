<%--
  Created by IntelliJ IDEA.
  User: BETELGEIZE
  Date: 9/15/2018
  Time: 8:47 AM
  To change this template use File | Settings | File Templates.
--%>

<jsp:useBean id="bookList" class="somePackage.beans.BookList" scope="page"/>


<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
<div class="book_infoCH">
    <div class="book_title">
        <%--<p> <%=book.getName()%></p>--%>
    </div>
    <div class="book_image">
        <%--<a href="#"><img src="<%=request.getContextPath()%>/ShowImage?index=<%=list.indexOf(book)%>" height="180" width="190" alt="Обложка"/></a>--%>
    </div>
    <div class="book_details">
        <form action="${pageContext.request.contextPath}/BookAdd" method="post" enctype="multipart/form-data">
            <br><input id="Name" name="Name" type="text"   placeholder="Name">
            <br><input id="Price" name="Price"  type="text"  placeholder="Price">
            <br><input id="Planet" name="Planet" type="text"  placeholder="Planet">
            <br><input id="Count" name="Count" type="text"  placeholder="Count">
            <br><input id="Year" name="Year" type="text"  placeholder="Year">
            <br><input id="image" type="file" name="image" size="200" placeholder="image">
            <br><input id="Type" type="text" name="Type" placeholder="Type"/>
            <br><INPUT id="id" TYPE="text" NAME="id"value="<%= session.getAttribute("id") %>" style="display: none" readonly>
            <br><input  type="submit" name="change">
        </form>
    </div>
</div>
</body>
</html>
