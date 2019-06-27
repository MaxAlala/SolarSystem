<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <link href='https://fonts.googleapis.com/css?family=Roboto:100,300,400,500,700,900|Material+Icons' rel="stylesheet">

    <title>Sarafan</title>
    <!-- версия для разработки, включает отображение полезных предупреждений в консоли -->
    <#--<script src="https://cdn.jsdelivr.net/npm/vue/dist/vue.js"></script>-->
    <#--<script src="https://cdn.jsdelivr.net/npm/vue-resource@1.5.1"></script>-->

  <#assign
  frontendData = frontendData

  >
    <#--<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.1/css/bootstrap.min.css" integrity="sha384-WskhaSGFgHYWDcbwN70/dfYBj47jz9qbsMId/iRN3ewGhXQFZCSftd1LZCfmhktB" crossorigin="anonymous" />-->
</head>
<body>
<#--<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.1/js/bootstrap.min.js" integrity="sha384-smHYKdLADwkXOn1EmN1qk/HfnUcbVRZyYmZ4qpPea6sjB/pTJ0euyQp0Mk8ck+5T" crossorigin="anonymous"></script>-->


<h3>Sarafan</h3>

<div id="app" >

</div>
<script type="text/javascript">
var profile = "${frontendData.profile.username}"
</script>
<script src="http://localhost:8000/main.js">

</script>
</body>
</html>


