<#import "parts/common.ftl" as c>
<#import "subs.ftl" as s>
<#import "groups.ftl" as gr>
<#import "parts/pager.ftl" as p>
<#import "skills.ftl" as sk>


<#-- search->main(Filter), add new post 3 field, with validation  -->
<#assign
user = Session.SPRING_SECURITY_CONTEXT.authentication.principal
name = user.getUsername()
isAdmin = user.isAdmin()
userid = user.getId()
>

<@c.page >

<div id="myModal" class="modal">
    <span class="close">&times;</span>
    <img class="modal-content" id="img01"/>
    <div id="caption"></div>
</div>
 <#if userChannel??>
 <h3>Cabinet of <b>${userChannel.getUsername()}</b></h3>
     <a class="nav-link" href="/user/sendmessage/${userChannel.id}">send message</a>
     <h4>something about me: ${userChannel.aboutme}</h4>

 <#else>
 <h3>All vacancies</h3>

 </#if>
    <#if subscriptionsCount??>
        <@s.subs isSubscriber isCurrentUser userChannel subscriptionsCount subscribersCount/>
        <@gr.groups group/>
        <@sk.skill skill/>
    </#if>
<#--<#macro isCurrentUser isSubscriber userChannel subscriptionsCount subscribersCount>-->

<div class="form-row">
    <div class="form-group col-md-6">
        <form method="get" action="/main" class="form-inline">
            <input type="text" name="filter" class="form-control" value="${filter?ifExists}"
                   placeholder="Search by tag">
            <button type="submit" class="btn btn-primary ml-2">Search</button>
        </form>
    </div>
</div>

<a class="btn btn-primary" data-toggle="collapse" href="#collapseExample" role="button" aria-expanded="false"
   aria-controls="collapseExample">
    Add new vacancy
</a>
<div class="collapse <#if message??>show</#if>" id="collapseExample">
    <div class="form-group mt-3">
        <form method="post" enctype="multipart/form-data" class="was-validated">
            <div class="form-group">

                <input type="text" class="form-control ${(textError??)?string('is-invalid', '')}"
                       value="<#if message??>${message.text}</#if>" name="text" placeholder="text"
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
                       value="<#if message??>${message.tag}</#if>" name="tag" placeholder="tag"
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

    <@p.pager url page/>
<div class="container">
<#--<@p.pager url page>-->
    <#list page.content as message>
    <#--<a id="like" href="/messages/${message.id}/like">-->
        <#assign
        liked = message.meLiked?string('yes','no')
        imageLikedId ="liked${message.id}"
        imageUnlikedId ="unliked${message.id}"
        likes = "likes${message.id}"
        >
        <div class="card">

        <img src="/img/${message.filename}" alt="myImg${message.id}" class="card-img-top" id="myImg${message.id}"
             onclick="Modal(this)"/>
            <div class="m-2">
                <div class="text${message.id}"><span>${message.text}</span></div>
                <div class="row">
                    <div class="tag${message.id}"><i class="col-sm" >#${message.tag}</i></div>
                <a class="col-sm" href="/main/${message.author.id}">${message.authorName}</a>
                <div class="col-sm" id="likedD${message.id}"
                     onclick="sendLikes(this,'/messages/${message.id}/like', '${liked}','${imageLikedId}','${imageUnlikedId}',${likes})">
                <#--${likes}-->
                <#--${imageLikedId}-->
                <#--${imageUnlikedId}-->
 <#if message.meLiked>
     <i class="fas fa-heart" id="liked${message.id}"></i>
 <#else>
     <i class="far fa-heart" id="unliked${message.id}"></i>
 </#if>
                    <div style="user-select: none;" id="likes${message.id}">${message.likes}</div>
                </div>
                </div>
            </div>

      <#if message.getAuthor().getId()?string == userid?string>
            <div class="btn-group" role="group" aria-label="Basic example">
                <a  type="button" class="btn btn-outline-primary btn-sm" data-toggle="collapse" href="#changeMessage${message.getId()}"
                    aria-controls="collapseExample">
                    change snippet
                </a>

                <form method="post" enctype="multipart/form-data" action="/maindelete">

                    <input type="text" value="${message.id}" name="id" style="display: none" readonly/>

                    <input type="text" class="form-control ${(textError??)?string('is-invalid', '')}"
                           value="<#if message??>${message.text}</#if>" name="text"
                           placeholder="text" style="display: none" readonly/>
                    <input type="text" class="form-control"
                           value="<#if message??>${message.tag}</#if>" name="tag" placeholder="tag" style="display: none" readonly/>
                    <input type="hidden" name="_csrf" value="${_csrf.token}"/>

                    <button type="submit" class="btn btn-danger">delete</button>
                </form>
            </div>
            <div class="card-footer text-muted">

            <#--urlLike = "/messages/${message.id}/like";-->



            <div class="collapse" id="changeMessage${message.getId()}">
                <div class="form-group mt-3">
                    <form method="post" enctype="multipart/form-data" action="/mainchange" class="was-validated">
                        <div class="custom-file">
                            <input type="file" class="custom-file-input" id="file" required name="file"/>
                            <label class="custom-file-label" for="validatedCustomFile">file</label>

                        </div>

                        <div class="form-group">
                            <input type="hidden" value="${message.id}" name="id" style="display: none" readonly/>

                <#if message.filename??>
                            <input type="hidden" value="${message.filename}" name="filename"/>
                </#if>
                            <input type="text" class="form-control ${(textError??)?string('is-invalid', '')}"
                                   value="<#if message??>${message.text}</#if>" name="text"
                                   placeholder="text" class="form-control is-valid" required/>


                <#if textError??>
                <div class="invalid-feedback">
                    ${textError}
                </div>
                </#if>

                        </div>
                        <div class="form-group">
                            <input type="text" class="form-control"
                                   value="<#if message??>${message.tag}</#if>" name="tag" placeholder="tag"
                                   class="form-control is-valid" required/>
                <#if tagError??>
                    <div class="invalid-feedback">
                        ${tagError}
                    </div>
                </#if>
                        </div>
                        <input type="hidden" name="_csrf" value="${_csrf.token}"/>
                        <div class="form-group">
                            <button type="submit" class="btn btn-success">change</button>
                        </div>
                    </form>

                </div>

            </div>

            </div>
      </#if>
        </div>
    <#else>
    No message
    </#list>
</div>
    <@p.pager url page/>

</@c.page>
