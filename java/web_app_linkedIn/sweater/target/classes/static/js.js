

// When the user scrolls the page, execute myFunction
window.onscroll = function() {myFunction()};

// Get the navbar
var navbar = document.getElementById("navbar");

// Get the offset position of the navbar
var sticky = navbar.offsetTop;

// Add the sticky class to the navbar when you reach its scroll position. Remove "sticky" when you leave the scroll position
function myFunction() {
    if (window.pageYOffset >= sticky) {
        navbar.classList.add("sticky")
    } else {
        navbar.classList.remove("sticky");
    }
}
// Get the modal
var modal = document.getElementById('myModal');

// Get the image and insert it inside the modal - use its "alt" text as a caption
// var img = document.getElementById('myImg');
var modalImg = document.getElementById("img01");
var captionText = document.getElementById("caption");


function Modal(el){
    // display: block;
    // overflow: auto;
    modal.style.display = "block";
    modal.style.overflow = "auto";
    modalImg.src = el.src;
    captionText.innerHTML = el.alt;
}

// Get the <span> element that closes the modal
var span = document.getElementsByClassName("close")[0];



// When the user clicks on <span> (x), close the modal
span.onclick = function() {
        modal.style.display = "none";
    };

function sendLikes(elem, url, liked, imageLikedId, imageUnlikedId, likes){
    var request = new XMLHttpRequest();
    request.open('GET', url);
    request.send();
    var il = document.getElementById(imageLikedId);
    var iul = document.getElementById(imageUnlikedId);
    var likesCount = document.getElementById(likes);
 // alert("!!!"+ il + " " + iul);
    var curImg;
if(il != null){
    curImg = il;
} else {
    curImg = iul;
}
 // alert(likes);
    var score;
    if(curImg.classList.toString()=== 'far fa-heart') {
          curImg.className = 'fas fa-heart';
           score = parseInt(likes.innerHTML);
            score++;
          likes.innerHTML = score;

          // alert(curImg + "1");
    }else

        if(curImg.classList.toString()=== 'fas fa-heart')
          {
              curImg.className = 'far fa-heart';
              // alert(curImg + "2");
              score = parseInt(likes.innerHTML);
              score--;
              likes.innerHTML = score;
          }


}






