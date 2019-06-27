<#macro groups group>

<#--<h3><b>${userChannel.username}'s</b></h3>-->
<div><h3>Groups</h3></div>
<ul class="list-group">
    <#list group as gr>
        <li class="list-group-item">
            <a href="/main/group/${gr.id}">${gr.getName()}</a>
        </li>
    </#list>
</ul>
</#macro>