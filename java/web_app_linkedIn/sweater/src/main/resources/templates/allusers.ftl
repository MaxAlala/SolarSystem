<#import "parts/common.ftl" as c>

<@c.page>
<h3><b>All users</b></h3>
<div><h3></h3></div>

    <div class="form-row">
        <div class="form-group col-md-6">
            <form method="get" action="/user/searchbyskill" class="form-inline">
                <input type="text" name="filter" class="form-control" value="${filter?ifExists}"
                       placeholder="Search by skill">
                <button type="submit" class="btn btn-primary ml-2">Search</button>
            </form>
            <form method="get" action="/user/searchbyusername" class="form-inline">
                <input type="text" name="filter" class="form-control" value="${filter?ifExists}"
                       placeholder="Search by username">
                <button type="submit" class="btn btn-primary ml-2">Search</button>
            </form>
        </div>
    </div>
<ul class="list-group">
    <#list users?ifExists as user>
        <li class="list-group-item">
            <a href="/main/${user.id}">${user.getUsername()}</a>
            <a href="/user/addtogroup/${user.id}">groups_manager</a>
<#--          <#list groups as gr>-->
<#--              <div class="row align-items-left">-->
<#--              <h4>${gr.name}</h4>-->
<#--              <form method="post" enctype="multipart/form-data" class="was-validated" action="addtogroup">-->
<#--                <input type="text" class="form-control"-->
<#--                       value="${user.id}" id="user" name="user" placeholder="user" style="display: none" readonly/>-->
<#--                <input type="text" class="form-control"-->
<#--                       value="${gr.id}" id="group" name="group" placeholder="group" style="display: none" readonly/>-->
<#--                <input type="hidden" name="_csrf" value="${_csrf.token}"/>-->

<#--                &lt;#&ndash;                     <#if groups??>&ndash;&gt;-->
<#--                <div class="form-group">-->
<#--                    <button type="submit" class="btn btn-success">add</button>-->
<#--                </div>-->
<#--                &lt;#&ndash;                     </#if>&ndash;&gt;-->
<#--            </form>-->
<#--            <form method="post" enctype="multipart/form-data" class="was-validated" action="deletefromgroup">-->
<#--                <input type="text" class="form-control"-->
<#--                       value="${user.id}" id="user" name="user" placeholder="user" style="display: none" readonly/>-->
<#--                <input type="hidden" name="_csrf" value="${_csrf.token}"/>-->
<#--                <input type="text" class="form-control"-->
<#--                       value="${gr.id}" id="group" name="group" placeholder="group" style="display: none" readonly/>-->

<#--                &lt;#&ndash;                    <#if groups??>&ndash;&gt;-->
<#--                <div class="form-group">-->
<#--                    <button type="submit" class="btn btn-error">delete</button>-->
<#--                </div>-->
<#--                &lt;#&ndash;                    </#if>&ndash;&gt;-->
<#--            </form>-->
<#--              </div>-->
<#--            </#list>-->


        </li>
    </#list>
</ul>
</@c.page>