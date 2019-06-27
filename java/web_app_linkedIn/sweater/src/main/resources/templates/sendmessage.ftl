<#import "parts/common.ftl" as c>
<#assign
user = Session.SPRING_SECURITY_CONTEXT.authentication.principal
name = user.getUsername()
isAdmin = user.isAdmin()
userid = user.getId()
>
<@c.page >
<h5>${receiver.username}</h5>
${message?ifExists}

<div class="container">

    <div class="card">
    <a class="btn btn-primary" data-toggle="collapse" href="#collapseExample" role="button" aria-expanded="false"
       aria-controls="collapseExample">
        send message
    </a>
    <div class="collapse <#if message??>show</#if>" id="collapseExample">
        <div class="form-group mt-3">
            <form method="post" enctype="multipart/form-data" class="was-validated" action="/user/sendmessage">
                <div class="form-group">

                    <h3>to this man</h3>
                <div class="form-group">

                    <input type="text" class="form-control ${(textError??)?string('is-invalid', '')}"
                           name="text" placeholder="text"
                           class="form-control is-valid" required/>
                    <input type="text" class="form-control"
                           value="${receiver.id}" name="receiver" placeholder="receiver" style="display: none" readonly/>
                    <#if textError??>
                        <div class="invalid-feedback">
                            ${textError}
                        </div>
                    </#if>
                </div>
                <div class="form-group">
                    <input type="text" class="form-control" class="form-control is-valid"
                            name="tag" placeholder="tag"
                           class="form-control is-valid" required/>
                    <#if tagError??>
                        <div class="invalid-feedback">
                            ${tagError}
                        </div>
                    </#if>

                </div>

                    <input type="hidden" name="_csrf" value="${_csrf.token}"/>
                    <div class="form-group">
                        <button type="submit" class="btn btn-success">send</button>
                    </div>
            </form>
        </div>

    </div>
    </div>
</@c.page>

