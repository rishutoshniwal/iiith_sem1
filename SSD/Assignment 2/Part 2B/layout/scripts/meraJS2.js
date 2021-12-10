

function myFunction() {
	var bt=document.getElementById("change");
  var x = document.createElement("INPUT");
  x.style.cssText='width:200px;height:200px;';
  var y=document.getElementById("top").innerHTML;
  x.setAttribute("type", "text");
  x.setAttribute("value", y);
   var e = document.querySelector("body");
        
        //e.firstElementChild can be used.
        var child = e.lastElementChild; 
        while (child) {
			
            e.removeChild(child);
            child = e.lastElementChild;
			
        }
		
		 var l = document.createElement("BUTTON");
		 l.style.cssText='width:100px;height:50px;';
		 l.innerHTML="edit it";
		  document.body.appendChild(l);
  document.body.appendChild(x);
 
	
}



//var y=document.getElementById("top").innerHTML;