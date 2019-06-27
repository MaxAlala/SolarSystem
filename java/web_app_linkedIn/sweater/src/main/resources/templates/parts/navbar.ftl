<#-- navbar  -->
<#include "security.ftl">
<#import "login.ftl" as l>

<nav id="navbar" class="navbar navbar-fixed-top navbar-expand-lg navbar-dark bg-dark">
    <a class="navbar-brand" href="/">vse</a>
    <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarSupportedContent"
            aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
        <span class="navbar-toggler-icon"></span>
    </button>

    <div class="collapse navbar-collapse" id="navbarSupportedContent">
        <ul class="navbar-nav mr-auto">
            <li class="nav-item">
                <a class="nav-link" href="/">home</a>
            </li>
            <li class="nav-item">
                <a class="nav-link" href="/main">vacancies</a>
            </li>
            <li class="nav-item">
                <a class="nav-link" href="/user/mymessages">my messages</a>
            </li>
            <#if isAdmin>
            <li class="nav-item">
                <a class="nav-link" href="/user">all users av</a>
            </li>            <li class="nav-item">
                <a class="nav-link" href="/user/getalluser">all users</a>
            </li>
            </#if>
              <#if user??>
            <li class="nav-item">
                <a class="nav-link" href="/user/profile">profile</a>
            </li>
               <li class="nav-item">
                   <a class="nav-link" href="/chat">chat</a>
               </li>
              </#if>
        </ul>

        <div class="navbar-text mr-3">${name}</div>
        <@l.logout user??/>
    </div>
</nav>
