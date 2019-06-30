<%@page import="somePackage.db.Database"%>
<%@page import="java.sql.Connection"%>
<%@page import="java.sql.ResultSet"%>
<%@page import="java.sql.Statement"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>Upload File</title>
</head>

<body>
<form method="post" action="UploadFileController" enctype="multipart/form-data">
    <center>
        <table border="1" width="25%" cellpadding="5">
            <thead>
            <th colspan="3">Upload File</th>
            </thead>
            <tbody>
            <tr>
                <td>Title :</td>
                <td><input type="text" name="title" size="30"></td>
            </tr>
            <tr>
                <td>Choose File :</td>
                <td><input type="file" name="file_uploaded"/></td>
            </tr>
            <tr>
                <td colspan="3">
                    <center><input type="submit" value="Upload"></center>
                </td>
            </tr>
            </tbody>
        </table>
    </center>
</form>

<br><br>

<table border="1" width="25%" cellpadding="5">
    <thead>
    <th colspan="3">Uploaded Files</th>
    </thead>
    <tbody>
    <tr>
        <td>
            <center><b>Id</b></center>
        <td>
            <center><b>Title</b></center>
        </td>
        <td>
            <center><b>File</b></center>
        </td>
    </tr>

    <%
                        try
                        {

                                Connection myconnection= Database.getConnection();

                                String sqlString = "SELECT * FROM files";
                                Statement myStatement = myconnection.createStatement();
                                ResultSet rs=myStatement.executeQuery(sqlString);
                                
                                if(!rs.isBeforeFirst())
                                {
                                    %>
                                        <tr>
                                        <td colspan="3"><center><%out.print("No Files!"); %></center></td>
                                        </tr>
                                    <%
                                }    
                                
                                while(rs.next())
                                {   
                            %>
                                    <tr>
                                        <td><center><%out.print(rs.getString("id")); %></center></td>
                                        <td><center><%out.print(rs.getString("title")); %></center></td>
                                        <td><center><a href="view_file.jsp?id=<%out.print(rs.getString("id"));%>">View</a></center></td>
                                    </tr>
                            <%
                                }
                            %>
                            
                </tbody> 
        </table>
                            
                            <%
                                rs.close();
                                myStatement.close();
                                myconnection.close();
                        }catch(Exception e){e.printStackTrace();}    
                        
                    %>
        
        <div style="position: relative">
            <div style="position: fixed ; bottom: 0 ; width:100% ; text-align:center ">
                <p><a href="https://www.youtube.com/user/TechWorld3g?sub_confirmation=1">CLICK HERE TO SUBSCRIBE</a></p>
            </div>
        </div>  
  
    </body>
</html>