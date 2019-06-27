<#import "parts/common.ftl" as c>
<#assign
user = Session.SPRING_SECURITY_CONTEXT.authentication.principal
name = user.getUsername()
isAdmin = user.isAdmin()
userid = user.getId()



>
<@c.page >
<h5>${username}</h5>
${message?ifExists}

<div class="container">


    <div class="card">
<form method="post">
    <div class="form-group row">
        <label class="col-sm-2 col-form-label">Password:</label>
        <div class="col-sm-6">
            <input type="password" name="password" class="form-control" placeholder="Password" />
        </div>
    </div>
    <div class="form-group row">
        <label class="col-sm-2 col-form-label">about me:</label>
        <div class="col-sm-6">
            <input type="text" name="aboutme" class="form-control" placeholder="aboutme" />
        </div>
    </div>
    <div class="form-group row">
        <label class="col-sm-2 col-form-label">Email:</label>
        <div class="col-sm-6">
            <input type="email" name="email" class="form-control" placeholder="some@some.com" value="${email!''}" />
        </div>
    </div>
    <input type="hidden" name="_csrf" value="${_csrf.token}" />
    <button class="btn btn-primary" type="submit">Save</button>
</form>
    </div>

    <div class="card">
    <a class="btn btn-primary" data-toggle="collapse" href="#collapseExample" role="button" aria-expanded="false"
       aria-controls="collapseExample">
        create new group
    </a>
    <div class="collapse <#if message??>show</#if>" id="collapseExample">
        <div class="form-group mt-3">
            <form method="post" enctype="multipart/form-data" class="was-validated" action="/user/creategroup">
                <div class="form-group">

                    <input type="text" class="form-control ${(textError??)?string('is-invalid', '')}"
                            name="name" placeholder="name"
                           class="form-control is-valid" required/>
                    <#if textError??>
                        <div class="invalid-feedback">
                            ${textError}
                        </div>
                    </#if>
                    <#--<div class="invalid-feedback">-->
                    <#--cannot be empty-->
                    <#--</div>-->
                </div>
                <div class="form-group">

                    <input type="text" class="form-control ${(textError??)?string('is-invalid', '')}"
                           name="text" placeholder="text"
                           class="form-control is-valid" required/>
                    <#if textError??>
                        <div class="invalid-feedback">
                            ${textError}
                        </div>
                    </#if>
                    <#--<div class="invalid-feedback">-->
                    <#--cannot be empty-->
                    <#--</div>-->
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
                <div class="form-group">
                    <div class="custom-file">
                        <input type="file" class="custom-file-input" id="file" required name="file"/>
                        <label class="custom-file-label" for="validatedCustomFile">file</label>
                    </div>
                </div>
                <input type="hidden" name="_csrf" value="${_csrf.token}"/>
                <div class="form-group">
                    <button type="submit" class="btn btn-success">Add</button>
                </div>
            </form>
        </div>

    </div>

    </div>
  <#if isAdmin>
    <div class="card">
    <a class="btn btn-primary" data-toggle="collapse" href="#collapseExample2" role="button" aria-expanded="false"
       aria-controls="collapseExample2">
        create new skill
    </a>
    <div class="collapse <#if message??>show</#if>" id="collapseExample2">
        <div class="form-group mt-3">
            <form method="post" enctype="multipart/form-data" class="was-validated" action="createskill">
                <div class="form-group">

                    <input type="text" class="form-control ${(textError??)?string('is-invalid', '')}"
                           name="name" placeholder="name"
                           class="form-control is-valid" required/>
                    <#if textError??>
                        <div class="invalid-feedback">
                            ${textError}
                        </div>
                    </#if>
                    <#--<div class="invalid-feedback">-->
                    <#--cannot be empty-->
                    <#--</div>-->
                </div>
                <div class="form-group">

                    <input type="text" class="form-control ${(textError??)?string('is-invalid', '')}"
                           name="text" placeholder="text"
                           class="form-control is-valid" required/>
                    <#if textError??>
                        <div class="invalid-feedback">
                            ${textError}
                        </div>
                    </#if>
                    <#--<div class="invalid-feedback">-->
                    <#--cannot be empty-->
                    <#--</div>-->
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
                    <button type="submit" class="btn btn-success">Add</button>
                </div>
            </form>
        </div>




    </div>
    </div>
</#if>
    <div class="card">
<#--<div class="form-row">-->
    <h3>your groups</h3>
    <#list yourgroups as gr>
        <div class="row align-items-left">
            <h4>${gr.name}</h4>

            <form method="post" enctype="multipart/form-data" class="was-validated" action="deletefromgroup">
<#--                <input type="text" class="form-control"-->
<#--                       value="${user.id}" id="user" name="user" placeholder="user" style="display: none" readonly/>-->
                <input type="hidden" name="_csrf" value="${_csrf.token}"/>
                <input type="text" class="form-control"
                       value="${gr.id}" id="group" name="group" placeholder="group" style="display: none" readonly/>

                <#--                    <#if groups??>-->
                <div class="form-group">
                    <button type="submit" class="btn btn-error">delete</button>
                </div>
                <#--                    </#if>-->
            </form>
        </div>
    </#list>
<#--    </div>-->
    </div>

    <div class="card">
<#--    <div class="form-row">-->
        <h3>your skills</h3>

        <#list yourskills as gr>
            <div class="row align-items-left">
                <h4>${gr.name}</h4>

                <form method="post" enctype="multipart/form-data" class="was-validated" action="deleteskill">
<#--                    <input type="text" class="form-control"-->
<#--                           value="${user.id}" id="user" name="user" placeholder="user" style="display: none" readonly/>-->
                    <input type="text" class="form-control"
                           value="${gr.id}" id="skill" name="skill" placeholder="skill" style="display: none" readonly/>
                    <input type="hidden" name="_csrf" value="${_csrf.token}"/>

                    <#--                    <#if groups??>-->
                    <div class="form-group">
                        <button type="submit" class="btn btn-error">delete</button>
                    </div>
                    <#--                    </#if>-->
                </form>
            </div>
        </#list>
<#--    </div>-->
    </div>

<div class="card">
    <h4>All skills</h4>

    <#list skills as gr>
        <div class="row align-items-left">
            <h4>${gr.name}</h4>
            <form method="post" enctype="multipart/form-data" class="was-validated" action="/user/addskill">
                <input type="text" class="form-control"
                       value="${gr.id}" id="skill" name="skill" placeholder="skill" style="display: none" readonly/>
                <input type="hidden" name="_csrf" value="${_csrf.token}"/>

                <div class="form-group">
                    <button type="submit" class="btn btn-success">add</button>
                </div>
                <#--                     </#if>-->
            </form>
            <form method="post" enctype="multipart/form-data" class="was-validated" action="/user/deleteskill">
                <input type="hidden" name="_csrf" value="${_csrf.token}"/>
                <input type="text" class="form-control"
                       value="${gr.id}" id="skill" name="skill" placeholder="skill" style="display: none" readonly/>

                <#--                    <#if groups??>-->
                <div class="form-group">
                    <button type="submit" class="btn btn-error">delete</button>
                </div>
                <#--                    </#if>-->
            </form>
        </div>
    </#list>
</div>
</div>
</@c.page>

