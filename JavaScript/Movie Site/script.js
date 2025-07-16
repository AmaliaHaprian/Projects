const APILINK='https://api.themoviedb.org/3/discover/movie?sort_by=popularity.desc&api_key=d3efd84e2e0390e34b677b253c035bd6&page=1';
const IMG_PATH='https://image.tmdb.org/t/p/w1280';
const SEARCHAPI='https://api.themoviedb.org/3/search/movie?&api_key=d3efd84e2e0390e34b677b253c035bd6&query="';

const main=document.getElementById('section');
const form=document.getElementById('form');
const search=document.getElementById('query');

returnMovies(APILINK);

function returnMovies(url){
    fetch(url).then(res => res.json())
    .then(function(data){
        console.log(data.results);
        data.results.forEach(movie => {
            const div_card=document.createElement('div');
            div_card.setAttribute('class', 'card');
            const div_row=document.createElement('div');
            div_row.setAttribute('class', 'row');
            const div_col=document.createElement('div');
            div_col.setAttribute('class', 'col');
            const image=document.createElement('img');
            image.setAttribute('class', 'poster');
            image.setAttribute('id', 'image');
            const title=document.createElement('h3');
            title.setAttribute('id', 'title');
            const center=document.createElement('center');

            title.innerText=`${movie.title}`;
            image.src=IMG_PATH+movie.poster_path;

            center.appendChild(image);
            div_card.appendChild(center);
            div_card.appendChild(title);
            div_col.appendChild(div_card);
            div_row.appendChild(div_col);

            main.appendChild(div_row);
        });
    });
}

form.addEventListener("submit", (elem) => {
    elem.preventDefault();
    main.innerHTML='';

    const searchTerm=search.value;

    if(searchTerm){
        returnMovies(SEARCHAPI+searchTerm);
        search.value="";} 
    });