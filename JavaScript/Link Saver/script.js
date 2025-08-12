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
    if(inputElem.value==""){
        chrome.tabs.query({active: true, currentWindow: true}, tabs => {
            let url=tabs[0].url;
            links.push(url);
        })
    }
    localStorage.setItem("links", JSON.stringify(links));
    displayLinks();
    inputElem.value="";
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