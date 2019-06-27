<#macro skill skills>

<#--<h3><b>${userChannel.username}'s</b></h3>-->
<div><h3>Skills</h3></div>
<ul class="list-group">
    <#list skills as sl>
        <li class="list-group-item">
            <h3>${sl.getName()}</h3>
        </li>
    </#list>
</ul>
</#macro>