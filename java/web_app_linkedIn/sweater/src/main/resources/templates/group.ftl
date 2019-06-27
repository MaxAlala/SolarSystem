<#import "parts/common.ftl" as c>

<@c.page>
<div id="myModal" class="modal">
    <span class="close">&times;</span>
    <img class="modal-content" id="img01"/>
    <div id="caption"></div>
</div>
<div class="container">
    <div class="card">
<h3><b>${group.name}</b></h3>
<div><h4>Tag: #${group.tag}</h4></div>
<div><h4>Lider: ${group.author.username}</h4></div>
<#--<div><h3>${group.text}</h3></div>-->
<#--<div><h3>${group.author}</h3></div>-->
        <img src="/img/${group.filename}" alt="myImg${group.id}" class="card-img-top" id="myImg${group.id}"
             onclick="Modal(this)"/>
<ul class="list-group">
    <#list group.participants as user>
        <li class="list-group-item">
            <a href="/main/${user.id}">${user.getUsername()}</a>
        </li>
    </#list>
</ul>
    </div>
</@c.page>

