<#import "parts/common.ftl" as c>

<@c.page>
<h3><b>Group management</b></h3>
<ul class="list-group">
        <li class="list-group-item">
            <h3><b>Add to groups:</b></h3>
          <#list groups as gr>
              <div class="row align-items-left">
              <h4>${gr.name}</h4>
              <form method="post" enctype="multipart/form-data" class="was-validated" action="/user/addtogroup/">
                <input type="text" class="form-control"
                       value="${user.id}" id="user" name="user" placeholder="user" style="display: none" readonly/>
                <input type="text" class="form-control"
                       value="${gr.id}" id="group" name="group" placeholder="group" style="display: none" readonly/>
                <input type="hidden" name="_csrf" value="${_csrf.token}"/>
                <div class="form-group">
                    <button type="submit" class="btn btn-success">add</button>
                </div>
            </form>
              </div>
            </#list>
        </li>

    <li class="list-group-item">
        <h3><b> Remove from groups:</b></h3>
        <#list groupstodelete as gr>
            <div class="row align-items-left">
                <h4>${gr.name}</h4>
                <form method="post" enctype="multipart/form-data" class="was-validated" action="/user/deletefromgroup">
                    <input type="text" class="form-control"
                           value="${user.id}" id="user" name="user" placeholder="user" style="display: none" readonly/>
                    <input type="text" class="form-control"
                           value="${gr.id}" id="group" name="group" placeholder="group" style="display: none" readonly/>
                    <input type="hidden" name="_csrf" value="${_csrf.token}"/>
                    <div class="form-group">
                        <button type="submit" class="btn btn-success">remove</button>
                    </div>
                </form>
            </div>
        </#list>
    </li>
</ul>
</@c.page>



