<#import "parts/common.ftl" as c>

<@c.page>
<h3><b>${userChannel.username}'s</b></h3>
<div><h3>${type}</h3></div>
<ul class="list-group">
    <#list users as user>
        <li class="list-group-item">
            <a href="/main/${user.id}">${user.getUsername()}</a>
        </li>
    </#list>
</ul>
</@c.page>
