let links=[];
let inputElem=document.getElementById("inputElem");
let saveButton=document.getElementById("saveButton");
let linkList=document.getElementById("linkList");

//localStorage.setItem("links", JSON.stringify(links));
let storedLinks=JSON.parse(localStorage.getItem("links"));
if(storedLinks){
    links=storedLinks;
    displayLinks();
}

saveButton.addEventListener("click", function(){
    links.push(inputElem.value);
    inputElem.value="";
    localStorage.setItem("links", JSON.stringify(links));
    displayLinks();
})

function displayLinks(){
    let text="";
    for(let i=0;i<links.length;i++){
        text+=`<li>
                <a target='_blank' href='${links[i]}'>
                    ${links[i]}
                </a>
               </li>`;
    }
    linkList.innerHTML=text;
}