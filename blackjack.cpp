// credit to wizard of odds for statistical information on blackjack
// you can find more stats on blackjack or other luck based games on
// their site at wizardofodds.com

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <string>

using namespace std;

void shuffle (bool deck[52], int cardsHeld[6], int aceAmount[6], int gameType, int suitType[5], int cardType[5], int dealerSuitType[5], int dealerCardType[5], int numOfCards[2]);
void firstDeal(int cardsHeld[6], bool deck[52], int numPlayers, int aceAmount[6], int gameType, int suitType[5], int cardType[5], int dealerSuitType[5], int dealerCardType[5], int numOfCards[2]);
void hitMe(int cardsHeld[6], bool deck[52], int playerChoice, int aceAmount[6], int gameType, int suitType[5], int cardType[5], int dealerSuitType[5], int dealerCardType[5], int numOfCards[2]);
void drawHand( int suitType[5], int cardType[5], int dealerSuitType[5], int dealerCardType[5], int numOfCards[2], bool dealerTurn);

// I want a shuffle function that returns a shuffled deck - check
// I want a way to go one way if the user decides to play or another
// if the user decides to let machines play
// Later on I'd like to introduce a form of card counting AI.
// I'm going to set it every game to shuffle potentially change it later on

// Really what I need to do is make a hit function.
// or make player specific functions but that would be a lot of work that could already be incorporated in the already done designs.

//      Dealer Has:  2,3,4,5,6,7,8,9,10,A
bool hardHit[18][10]{1,1,1,1,1,1,1,1,1,1, // player 4   // 1 means hit 0 means stay
                    1,1,1,1,1,1,1,1,1,1, // player 5
                    1,1,1,1,1,1,1,1,1,1, // player 6
                    1,1,1,1,1,1,1,1,1,1, // player 7
                    1,1,1,1,1,1,1,1,1,1, // player 8
                    1,1,1,1,1,1,1,1,1,1, // player 9
                    1,1,1,1,1,1,1,1,1,1, // player 10
                    1,1,1,1,1,1,1,1,1,1, // player 11
                    1,1,0,0,0,1,1,1,1,1, // player 12
                    0,0,0,0,0,1,1,1,1,1, // player 13
                    0,0,0,0,0,1,1,1,1,1, // player 14
                    0,0,0,0,0,1,1,1,1,1, // player 15
                    0,0,0,0,0,1,1,1,1,1, // player 16
                    0,0,0,0,0,0,0,0,0,1, // player 17
                    0,0,0,0,0,0,0,0,0,0, // player 18
                    0,0,0,0,0,0,0,0,0,0, // player 19
                    0,0,0,0,0,0,0,0,0,0, // player 20
                    0,0,0,0,0,0,0,0,0,0, // player 21
                  };

bool softHit [9][10]{1,1,1,1,1,1,1,1,1,1, // player 13 and ace
                     1,1,1,1,1,1,1,1,1,1, // player 14 and ace
                     1,1,1,1,1,1,1,1,1,1, // player 15 and ace
                     1,1,1,1,1,1,1,1,1,1, // player 16 and ace
                     1,1,1,1,1,1,1,1,1,1, // player 17 and ace
                     0,0,0,0,0,0,0,1,1,1, // player 18
                     0,0,0,0,0,0,0,0,0,0, // player 19 and ace
                     0,0,0,0,0,0,0,0,0,0, // player 20 and ace
                     0,0,0,0,0,0,0,0,0,0, // player 21 and ace
                   };

int main()
{
  bool deck[52];      // bool since it only has to know if someone grabbed a card or not.
  int numPlayers = 2;
  int gameAmount, newCard, enteredHitLimit; // newCard is a variable used every time someone hits
  int cardsHeld[6] = {0,0,0,0,0,0}; // keeps track of the cards held by each player and the dealer
  int hitLimit[6] = {1,1,1,1,1,16}; // keeps track of the hit limit
  int aceAmount[6] = {0,0,0,0,0,0}; // potentially use char but not sure
  int playerWins[6]= {0,0,0,0,0,0}; // first being the dealer second being player 1 (our player in this case), etc.
  bool randomAmount[6] = {0,0,0,0,0,0}; // this is if I want it to be a ra`ndom number for their hitLimit

  // these are used for when the player is playing the game
  char gameType;
  char playerChoice;
  int numOfCards[2] = {0,0};
  int suitType[5];
  int cardType[5];
  int dealerSuitType[5];
  int dealerCardType[5];

  srand (time(NULL));               // set new "random" seed
  shuffle(deck, cardsHeld, aceAmount, gameType, suitType, cardType, dealerSuitType, dealerCardType, numOfCards); // set everything to its initial state before continuing
  do{
    cout << endl << "If you want to play enter 'p' if you want the computer to play for you enter 'c' lastly enter 'w' if you want to play by the wizard of odds advice." << endl;
    cin >> gameType;
  }while (gameType != 'p' && gameType != 'P' && gameType != 'C' && gameType != 'c' && gameType != 'w' && gameType != 'W');
if (gameType == 'c' || gameType == 'C'){
  do{
  if (numPlayers <2 || numPlayers >6) {cout << endl << "Please try again" << endl << endl;}
  cout << endl << "Number of players (note there will always be at minimum 2 at maximum 6 (player one will assume to be your character))" << endl;
  cin >> numPlayers;    // user enters the player amount they want
} while (numPlayers <2 || numPlayers >6);
  do {
    cout << endl << "Number of times the game is played (note there will always be at minimum 1 at maximum 1,000,000,000)" << endl;
    cin >> gameAmount;  // user enters the number of times the game runs
  } while(gameAmount < 1 || gameAmount > 1000000000);

  for (int i = 0; i < (numPlayers); i++){
    do{
    if (i == numPlayers - 1){enteredHitLimit = 16; break;}  // if the player is the dealer we dont enter the hit limit as it is always 16 for them
    cout << endl << "Set hit limit for character " << i + 1 << "." << endl <<"Put '0' if you want it to be a random number between 14 and 18." << endl << "Put a negative number if you want their hit limit to be random every hand" << endl << endl;
    cin >> enteredHitLimit;  // user enters players hit limit (ie the last number they will hit on)
    if (enteredHitLimit == 0)
    {
      enteredHitLimit = (rand() % 5) + 14;  // if they want a random number we give it to them
      break;
    }
    else if (enteredHitLimit < 0) {randomAmount[i] = true; enteredHitLimit = (rand() % 5) + 14;} // if they want it random everytime we give that to them too.
  }while (enteredHitLimit > 21 || enteredHitLimit < 3);

  enteredHitLimit++;
  hitLimit[i] = enteredHitLimit;
  }

  cout << endl;

  for (int i = 0; i < gameAmount; i++){ // now were at the actual game of blackjack.
      firstDeal(cardsHeld, deck, numPlayers, aceAmount, gameType, suitType, cardType, dealerSuitType, dealerCardType, numOfCards); // we deal the initial two cards out to everyone
      for (int j = 0; j < numPlayers; j++){
        if (randomAmount[j]){   // if they wanted to have it as a random amount every time we set that hitlimit as a random amount every time.
          hitLimit[j] = rand() %5 + 14;
        }
        if (cardsHeld [j] < (hitLimit[j])){
          do {
            hitMe(cardsHeld, deck, j, aceAmount, gameType, suitType, cardType, dealerSuitType, dealerCardType, numOfCards);
          } while(cardsHeld [j] < hitLimit[j]);
        }
        if (cardsHeld[j] == hitLimit[j] && aceAmount[j] > 0 && cardsHeld[j] != 21){
            hitMe(cardsHeld, deck, j, aceAmount, gameType, suitType, cardType, dealerSuitType, dealerCardType, numOfCards);
        }
      }   // after this everyone should have the card they were given
          // then we have to see who won
      for (int j = 0; j < (numPlayers - 1); j++){
        if ((cardsHeld[j] <= 21) && (cardsHeld[j] > cardsHeld[numPlayers - 1]) || (cardsHeld[j] <= 21) && (cardsHeld[numPlayers - 1] > 21) )
        {playerWins[j] ++;}
        else if ((cardsHeld[j] == cardsHeld[numPlayers -1])) {}
        else {playerWins[numPlayers - 1]++;}
      }

      // this code here is only here in case you would like to check to make sure the results are accurate it will tell you the value
      // of cards each player is holding at the end of every hand.

      /*
      for (int j = 0; j < (numPlayers); j++){
        if (j == numPlayers - 1){
          cout << "House has " << cardsHeld[j] << endl << endl;
        }
        else{
          cout << "Player " << j + 1 << " has: " << cardsHeld[j] << endl;
        }
      }
      */

      shuffle (deck, cardsHeld, aceAmount, gameType, suitType, cardType, dealerSuitType, dealerCardType, numOfCards);
  }



  for (int j = 0; j < (numPlayers); j++){
    if (j == numPlayers - 1){
      cout << endl << "House Wins " << playerWins[j] << endl << endl;
    }
    else{
      cout << "Player " << j + 1 << "'s wins: " << playerWins[j] << endl;
    }
  }
  return 0;
  }
  // now were on the player playing the game
  else if (gameType == 'p' || gameType == 'P'){
    numPlayers = 2;
    bool dealerTurn = 0;
    while(playerChoice != 'n' && playerChoice != 'N'){
      firstDeal(cardsHeld, deck, numPlayers, aceAmount, gameType, suitType, cardType, dealerSuitType, dealerCardType, numOfCards);
      drawHand(suitType, cardType, dealerSuitType, dealerCardType, numOfCards, dealerTurn);
      cout << endl << "You currently hold " << cardsHeld[0] << "." << endl;
      do{
      if(cardsHeld[0] == 21) {break;}
      else if(cardsHeld[1] == 21) {break;}
      cout << endl << "Enter 'h' if you'd like to hit, enter 's' if you'd like to stay." << endl;
      cin >> playerChoice;} while (playerChoice != 's' && playerChoice != 'S' && playerChoice != 'h' && playerChoice != 'H');
      if (playerChoice == 'h' || playerChoice == 'H'){
        do{
        hitMe(cardsHeld, deck, 0, aceAmount, gameType, suitType, cardType, dealerSuitType, dealerCardType, numOfCards);
        if(cardsHeld[0] > 21 && aceAmount[0] > 0) {cardsHeld[0] = cardsHeld[0] - 10; aceAmount[0] --;}
        if(cardsHeld[0] >= 21) {break;}
        drawHand(suitType, cardType, dealerSuitType, dealerCardType, numOfCards, dealerTurn);
        cout << endl << "You currently hold " << cardsHeld[0] << "." << endl;
        do{
        cout << endl << "Enter 'h' if you'd like to hit, enter 's' if you'd like to stay." << endl;
        cin >> playerChoice;} while (playerChoice != 's' && playerChoice != 'S' && playerChoice != 'h' && playerChoice != 'H');
      } while((playerChoice == 'h' || playerChoice == 'H') && numOfCards[0] < 5);
      }
      if (cardsHeld[1] < 17 && numOfCards[1] < 5){
        do {
          hitMe(cardsHeld, deck, 1, aceAmount, gameType, suitType, cardType, dealerSuitType, dealerCardType, numOfCards);
          if(cardsHeld[1] > 21 && aceAmount[1] > 0) {cardsHeld[1] = cardsHeld[1] - 10; aceAmount[1] --;}
        } while(cardsHeld [1] < 17);
      }
      if (cardsHeld[1] == 17 && aceAmount[1] > 0 && numOfCards[1] < 5){
          hitMe(cardsHeld, deck, 1, aceAmount, gameType, suitType, cardType, dealerSuitType, dealerCardType, numOfCards);
      }
      dealerTurn = 1;
      drawHand(suitType, cardType, dealerSuitType, dealerCardType, numOfCards, dealerTurn);
      cout << endl << "You held " << cardsHeld[0] << "." << endl;
      cout << endl << "The dealer held " << cardsHeld[1] << "." << endl;
      if (cardsHeld[0] == cardsHeld[1]){cout << endl << "You both have the same values. No one wins." << endl; playerWins[3]++;}
      if (cardsHeld[0] >= cardsHeld[1] && cardsHeld[0] < 22 || cardsHeld[1] > 21 && cardsHeld[0] <= 21){cout << endl << "You win!" << endl;  playerWins[0]++; playerWins[3]++;}
      else{cout << endl << "You lost..." << endl; playerWins[1]++; playerWins[3]++;}
      shuffle (deck, cardsHeld, aceAmount, gameType, suitType, cardType, dealerSuitType, dealerCardType, numOfCards);
      dealerTurn = 0;
      do{
      cout << endl << "Would you like to play again? enter 'y' for yes and 'n' for no." << endl;
      cin >> playerChoice;
    } while (playerChoice != 'y' && playerChoice != 'Y' && playerChoice != 'n' && playerChoice != 'N');
    }
    cout << endl << "You won " << playerWins[0] << " games out of " << playerWins[3] << "." << endl;
    cout << endl << "The dealer won " << playerWins[1] << " games out of " << playerWins[3] << "." << endl;
    cout << endl << endl << "Which means you won " << playerWins[0]/playerWins[3] << "% of the games." << endl << endl;
  }

  else if(gameType == 'w' || gameType == 'W'){
    numPlayers = 2;
    shuffle (deck, cardsHeld, aceAmount, gameType, suitType, cardType, dealerSuitType, dealerCardType, numOfCards);
    bool firstPass = true;
    for(int i = 0; i < 1000000; i++){
      firstDeal(cardsHeld, deck, numPlayers, aceAmount, gameType, suitType, cardType, dealerSuitType, dealerCardType, numOfCards);
      //cout << "Player currently has " << cardsHeld[0] << endl;
      //cout << "Dealer currently has " << cardsHeld[1] << endl;
      // in between stuff
      // I want the player to go first
      if (dealerCardType[1] >= 10){
        if(dealerCardType[1] == 14){dealerCardType[1] = 11;}
        else {dealerCardType[1] = 10;}
      }
      //cout << "Player can see the dealer has a card worth " << dealerCardType[1] << endl;
      firstPass = true;
      while(1){
      if (firstPass && cardsHeld[0] == 21 || firstPass && cardsHeld[1] == 21) {break;}
      if(aceAmount[0] > 0 && cardsHeld[0] > 12 && cardsHeld[0] < 22 && numOfCards[0] < 5){
        if (softHit[cardsHeld[0]-13][dealerCardType[1]-2] == 1){
          //cout << "Player hit at soft " << cardsHeld[0];
          hitMe(cardsHeld, deck, 0, aceAmount, gameType, suitType, cardType, dealerSuitType, dealerCardType, numOfCards);
          if (cardsHeld[0] > 21 && aceAmount[0] > 0) {cardsHeld[0] = cardsHeld[0] - 10; aceAmount[0]--;}
          //cout << " Player now has " << cardsHeld[0] << endl;
        }
        else{break;}
      }
      else if(aceAmount[0] == 0 && numOfCards[0] < 5){
          if(hardHit[cardsHeld[0] - 4][dealerCardType[1]-2] == 1){
            //cout << "Player hit at hard " << cardsHeld[0];
              hitMe(cardsHeld, deck, 0, aceAmount, gameType, suitType, cardType, dealerSuitType, dealerCardType, numOfCards);
              if (cardsHeld[0] > 21 && aceAmount[0] > 0) {cardsHeld[0] = cardsHeld[0] - 10; aceAmount[0]--;}
              //cout << " Player now has " << cardsHeld[0] << endl;
          }
          else{break;}
      }
      else {break;}
      if (cardsHeld[0] > 21 || numOfCards[0] >= 5) {break;}
      firstPass = false;
      }
      // player is done dealer is up
      if (cardsHeld[1] < 17 && numOfCards[1] < 5){
        do {
          hitMe(cardsHeld, deck, 1, aceAmount, gameType, suitType, cardType, dealerSuitType, dealerCardType, numOfCards);
          if(cardsHeld[1] > 21 && aceAmount[1] > 0) {cardsHeld[1] = cardsHeld[1] - 10; aceAmount[1] --;}
        } while(cardsHeld [1] < 17);
      }
      if (cardsHeld[1] == 17 && aceAmount[1] > 0 && numOfCards[1] < 5){
          hitMe(cardsHeld, deck, 1, aceAmount, gameType, suitType, cardType, dealerSuitType, dealerCardType, numOfCards);
      }
      if (cardsHeld[0] > cardsHeld[1] && cardsHeld[0] < 22 || cardsHeld[1] > 21 && cardsHeld[0] <= 21) {playerWins[0]++;}
      else if (cardsHeld[1] == cardsHeld[0] && cardsHeld[1] <= 21) {playerWins[2]++;}
      else {playerWins[1]++;}
      //cout << "Player held " << cardsHeld[0] << endl;
      //cout << "Dealer held " << cardsHeld[1] << endl << endl;
      playerWins[3]++;
      shuffle (deck, cardsHeld, aceAmount, gameType, suitType, cardType, dealerSuitType, dealerCardType, numOfCards);
    }
    cout << "Player Wins " << playerWins[0] << endl;
    cout << "Dealer Wins " << playerWins[1] << endl;
    cout << "No wins     " << playerWins[2] << endl << endl;
    cout << "Total Games " << playerWins[3] << endl << endl;
  }
}

void shuffle (bool deck[52], int cardsHeld[6], int aceAmount[6], int gameType, int suitType[5], int cardType[5], int dealerSuitType[5], int dealerCardType[5], int numOfCards[2]){
  for(int i = 0; i < 52; i++){
    deck[i] = true;
  }
  for (int i = 0; i < 6; i++)
  {
    cardsHeld[i] = 0;
    aceAmount[i] = 0;
  }
  for (int i = 0; i < 5; i++){
  suitType[i] = 0;
  cardType[i] = 0;
  dealerSuitType[i] = 0;
  dealerCardType[i] = 0;
  }
  numOfCards[0]= 0;
  numOfCards[1]= 0;
}

void firstDeal(int cardsHeld[6], bool deck[52], int numPlayers, int aceAmount[6], int gameType, int suitType[5], int cardType[5], int dealerSuitType[5], int dealerCardType[5], int numOfCards[2]){
  int newCard;
  for (int i = 0; i < numPlayers; i++)
  {
      hitMe(cardsHeld, deck, i, aceAmount, gameType, suitType, cardType, dealerSuitType, dealerCardType, numOfCards);
    }
  for (int i = 0; i < numPlayers; i++)
  {
      hitMe(cardsHeld, deck, i, aceAmount, gameType, suitType, cardType, dealerSuitType, dealerCardType, numOfCards);
  }
}

void hitMe(int cardsHeld[6], bool deck[52], int playerChoice, int aceAmount[6], int gameType, int suitType[5], int cardType[5], int dealerSuitType[5], int dealerCardType[5], int numOfCards[2]){
  int newCard;
  do {
    newCard = rand() % 52;
  } while (deck[newCard] == 0);
  deck[newCard] = 0;
  if (gameType == 'p' || gameType == 'P' || ((gameType == 'w' || gameType == 'W') && playerChoice == 1)){
    if (playerChoice == 0)
    {
      suitType[numOfCards[0]] = newCard % 4 + 1;
      cardType[numOfCards[0]] = newCard / 4 + 2;
    }
    else{
      dealerSuitType[numOfCards[1]] = newCard % 4 + 1;
      dealerCardType[numOfCards[1]] = newCard / 4 + 2;
    }
    numOfCards[playerChoice] ++;
  }
  newCard = (newCard)/4 + 2; // gotta figure out a formula for this

  if (newCard >= 11 && newCard != 14)
  {
    newCard = 10;
  }
  else if (newCard == 14)
  {
    newCard = 11;
    aceAmount[playerChoice] ++;
  }
  if (cardsHeld[playerChoice] + newCard > 21 && aceAmount[playerChoice] > 1)
  {
    aceAmount[playerChoice] --;
    newCard = 1;
  }
  // The next line is only for debugging and making sure we're getting the correct values
  // cout << "Player num " << playerChoice + 1 << " recieved the " << newCard << " card. Player " << playerChoice + 1 << " currently has " << cardsHeld[playerChoice] + newCard << endl;
  cardsHeld[playerChoice] += newCard;
}

void drawHand( int suitType[5], int cardType[5], int dealerSuitType[5], int dealerCardType[5], int numOfCards[2], bool dealerTurn)
{
  // top left corner =
  // top right corner =
  // bottom left corner =
  // bottom right corner =
  // heart =
  // diamond =
  // spade =
  // club =
  string localSuitType[2][5];
  string localCardType[2][5];
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < numOfCards[i]; j++)
    {
      if (i == 0){
        if (suitType[j] == 1) {localSuitType[i][j] = "\u2665";}
        else if (suitType[j] == 2) {localSuitType[i][j] = "\u25c6";}
        else if (suitType[j] == 3) {localSuitType[i][j] = "\u2660";}
        else if (suitType[j] == 4) {localSuitType[i][j] = "\u2663";}
        if (cardType[j] < 10){localCardType[i][j] = std::to_string (cardType[j]);} // this might be wrong
        else if (cardType[j] == 10){localCardType[i][j] = "X";}
        else if (cardType[j] == 11){localCardType[i][j] = "J";}
        else if (cardType[j] == 12){localCardType[i][j] = "Q";}
        else if (cardType[j] == 13){localCardType[i][j] = "K";}
        else if (cardType[j] == 14){localCardType[i][j] = "A";}
      }
      else if (i == 1){
        if (dealerSuitType[j] == 1) {localSuitType[i][j] = "\u2665";}
        else if (dealerSuitType[j] == 2) {localSuitType[i][j] = "\u25c6";}
        else if (dealerSuitType[j] == 3) {localSuitType[i][j] = "\u2660";}
        else if (dealerSuitType[j] == 4) {localSuitType[i][j] = "\u2663";}
        if (dealerCardType[j] < 10){localCardType[i][j] = std::to_string (dealerCardType[j]);} // this might be wrong
        else if (dealerCardType[j] == 10){localCardType[i][j] = "X";}
        else if (dealerCardType[j] == 11){localCardType[i][j] = "J";}
        else if (dealerCardType[j] == 12){localCardType[i][j] = "Q";}
        else if (dealerCardType[j] == 13){localCardType[i][j] = "K";}
        else if (dealerCardType[j] == 14){localCardType[i][j] = "A";}
      }
    }
  }
  if(dealerTurn == 0){
  cout << "                                The Dealers Hand" << endl;
  cout << "                               ╭------╮ "; for(int i = 0; i < (numOfCards[1] - 1); i++) {cout << " ╭------╮ ";} cout << endl;
  cout << "                               |######| "; for(int i = 0; i < (numOfCards[1] - 1); i++) {cout << " | " << localCardType[1][i + 1] << localSuitType[1][i + 1] << "   | ";} cout << endl;
  cout << "                               |######| "; for(int i = 0; i < (numOfCards[1] - 1); i++) {cout << " |      | ";} cout << endl;
  cout << "                               |######| "; for(int i = 0; i < (numOfCards[1] - 1); i++) {cout << " |   " << localCardType[1][i + 1] << localSuitType[1][i + 1] << " | ";} cout << endl;
  cout << "                               ╰------╯ "; for(int i = 0; i < (numOfCards[1] - 1); i++) {cout << " ╰------╯ ";} cout << endl;
  cout << endl;
  }
  else{
    cout << "                               The Dealers Hand" << endl;
    cout << "                              "; for(int i = 0; i < (numOfCards[1]); i++) {cout << " ╭------╮ ";} cout << endl;
    cout << "                              "; for(int i = 0; i < (numOfCards[1]); i++) {cout << " | " << localCardType[1][i] << localSuitType[1][i] << "   | ";} cout << endl;
    cout << "                              "; for(int i = 0; i < (numOfCards[1]); i++) {cout << " |      | ";} cout << endl;
    cout << "                              "; for(int i = 0; i < (numOfCards[1]); i++) {cout << " |   " << localCardType[1][i] << localSuitType[1][i] << " | ";}
    cout << endl;
    cout << "                              "; for(int i = 0; i < (numOfCards[1]); i++) {cout << " ╰------╯ ";} cout << endl;

  }
  cout << "                               Your Hand" << endl;
  cout << "                              "; for(int i = 0; i < (numOfCards[0]); i++) {cout << " ╭------╮ ";} cout << endl;
  cout << "                              "; for(int i = 0; i < (numOfCards[0]); i++) {cout << " | " << localCardType[0][i] << localSuitType[0][i] << "   | ";} cout << endl;
  cout << "                              "; for(int i = 0; i < (numOfCards[0]); i++) {cout << " |      | ";} cout << endl;
  cout << "                              "; for(int i = 0; i < (numOfCards[0]); i++) {cout << " |   " << localCardType[0][i] << localSuitType[0][i] << " | ";}
  cout << endl;
  cout << "                              "; for(int i = 0; i < (numOfCards[0]); i++) {cout << " ╰------╯ ";}  cout << endl;
}
