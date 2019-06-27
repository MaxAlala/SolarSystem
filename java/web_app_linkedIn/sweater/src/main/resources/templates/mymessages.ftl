<#import "parts/common.ftl" as c>

<@c.page>
<h3><b>message management</b></h3>
<#--    <div class="form-row">-->

<#--    </div>-->
<ul class="list-group">
    Message to you:
    <#list tome?ifExists as to>
        <li class="list-group-item">
            <a href="/main/${to.author.id}">from ${to.author.username}: ${to.text}  ,#${to.tag}</a>
        </li>
    </#list>
</ul>

    <ul class="list-group">
        Message from you:
        <#list fromme?ifExists as from>
            <li class="list-group-item">
                <a href="/main/${from.receiver.id}">to ${from.receiver.username}: ${from.text}  ,#${from.tag}</a>
            </li>
        </#list>
    </ul>
</@c.page>