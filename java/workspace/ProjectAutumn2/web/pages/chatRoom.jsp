<jsp:useBean id="bookList" class="somePackage.beans.BookList" scope="page"/>
<div class="book_infoCH">
    <div class="book_title">
        <%--<p> <%=book.getName()%></p>--%>
    </div>

    <div class="book_details">
        <form action="${pageContext.request.contextPath}/SendMessage" method="post" enctype="multipart/form-data">
            <br><input id="UserName" name="UserName" type="text"   placeholder="UserName">
            <br><input id="Text" name="Text"  type="text"  placeholder="Text">
            <br><INPUT id="id" TYPE="text" NAME="id" value="<%= session.getAttribute("id") %>" style="display: none" readonly>
            <br><input  type="submit" name="send">
        </form>
    </div>
</div>
</body>
</html>
