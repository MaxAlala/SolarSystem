<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>

<html>

    <head>

        <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
        <title>SolarSystem - entrance</title>
        <link href="css/style_index.css" rel="stylesheet" type="text/css">

    </head>

    <body>
    <%--<img src="images/star_wars.jpg" id="bg" alt="">--%>
        <%session.invalidate(); %>
        <div class="gigaMain">



        <div class="main">

            <div class="content">
                <p class="title"><span class="xxxd"><img src="images/galaxy.jpg" width="76" height="77" hspace="10" vspace="10" align="middle"></span></p>
                <p class="title">Space shop - SolarSystem</p>
                <p class="title">Be honest, be fair, be rational - is motto of this market. All our job dedicated for our clients.  </p>
                <p class="title">Rule: you shop adjust our motto.</p>
                <p class="title">How to connect with us: <a href="mailto:support@testlibrary.com">SolarSystem@mars.com</a></p>
                <p>&nbsp;</p>

            </div>

            <div class="login_div">
                <p class="title">Please, input you data:</p>
                <%--<form class="login_form" name="username" action="pages/main.jsp" method="POST">--%>
                    <%--Имя: <input type="text" name="username" value="" size="20" />--%>
                    <%--<input type="submit" value="Войти" />--%>
                <%--</form>--%>

                <script type="text/javascript">

                    function myFunction() {
                        var x, text;

                        // Get the value of the input field with id="numb"
                        x = document.getElementById("in").value;

                        // If x is Not a Number or less than one or greater than 10
                        if ( x.length === 0 || x.length > 20) {
                            text = "Input not valid";
                        } else {
                            text = "";
                        }
                        document.getElementById("demo").innerHTML = text;
                    }


                    // function validateForm()
                    // {
                    //     var x=document.forms["myForm"]["user"].value;
                    //     if (x==null || x=="")
                    //     {
                    //         alert("Input not valid");
                    //         return false;
                    //     }
                    // }

                </script>

                <script type="text/javascript">

                    function validatePassword() {

                        var p = document.getElementById("passw").value, text;

                        if (p.length < 8) {
                            text = "Your password must be at least 8 characters";
                        }
                        if (p.search(/[a-z]/i) < 0) {
                            text = "Your password must contain at least one letter.";
                        }
                        if (p.search(/[0-9]/) < 0) {
                            text = "Your password must contain at least one digit."; 
                        }
                        
                        document.getElementById("demo").innerHTML = text;
                    }

                </script>

                <div align="center">
                    <form name="myForm" action="Login" method="post" >
                        User name : <input id="in"  onclick="myFunction()" type="text" name="user" required="required"><br>
                        Password : <input class="in" id="passw" onclick="validatePassword()" type="password" name="password" required="required">
                        <input type="submit" value="sign in">
                        <p id="demo"></p>
                        <input type="checkbox" id="rememberMe" name="rememberMe">
                        <label for="rememberMe">rememberMe</label>
                    </form>



                    <form action = "registration.jsp">
                        <input type ="submit" value="sign up">
                    </form>

                    <%--<a href="registration.jsp">registration</a>--%>
                    <%--<a href="/pages/main.jsp">main</a>--%>
                </div>




            </div>

<div class="footer">
    Founder: alien222, 2076 year
</div>
</div>
</div>
</body>

</html>