<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>



<%
      response.setHeader("Cache-Control", "no-cache, no-store, must-revalidate");
      if(session.getAttribute("author") == null) {
            response.sendRedirect("http://localhost:8080/index.jsp");
      }
%>

<%@include file="../pages/jspf/left_menu.jspf" %>
           
<%@include file="../pages/jspf/letters.jspf" %>

<div style="float:left; margin-top: 20px;">
<h3>Выберите раздел или используйте поиск книги</h3>
      </div>