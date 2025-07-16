let playerScore=0;
let computerScore=0;

let rockButton=document.querySelector("#rock");
let paperButton=document.querySelector("#paper");
let scissorsButton=document.querySelector("#scissors");
let message=document.querySelector("#message");
let scoreDisplay=document.querySelector("#score");


function getComputerChoice(){
    const choices=["rock","paper","scissors"];
    const randomIndex=Math.floor(Math.random()*choices.length);
    return choices[randomIndex];
}

function play(playerChoice){
    const computerChoice=getComputerChoice();
    if(playerChoice==computerChoice){
        message.textContent="It'a a tie! You both chose "+ playerChoice+".";
    }
    else if(playerChoice=="rock" && computerChoice=="scissors" ||
            playerChoice=="paper" && computerChoice=="rock" ||
            playerChoice=="scissors" && computerChoice=="paper"){
        message.textContent="You win! "+ playerChoice +" beats " + computerChoice + ".";
        updateScore("player");}
    else{
        message.textContent="You lose! " + computerChoice + " beats " + playerChoice + ".";
        updateScore("computer");
    }
    gameOver();
}

function updateScore(winner){
    if(winner=="player")
        playerScore++;
    else if(winner=="computer")
        computerScore++;
    scoreDisplay.textContent="Player: " + playerScore + ", Computer: " + computerScore;
}

function gameOver(){
    if(playerScore==5){
        message.textContent="Congratulations! You reached 5 points and won the game!";
        resetGame();
    
    } else if(computerScore==5){
        message.textContent="Game over! The computer reached 5 points first.";
        resetGame();
    }
}

function resetGame(){
    playerScore=0;
    computerScore=0;
    scoreDisplay.textContent="Player: 0, Computer: 0";
}