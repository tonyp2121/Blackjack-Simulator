#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

void shuffle (bool deck[52], int cardsHeld[6], int aceAmount[6]);
void firstDeal(int cardsHeld[6], bool deck[52], int numPlayers, int aceAmount[6]);

// I want a shuffle function that returns a shuffled deck - check
// I want a way to go one way if the user decides to play or another
// if the user decides to let machines play
// Later on I'd like to introduce a form of card counting AI.
// I'm going to set it every game to shuffle potentially change it later on


int main()
{
  bool deck[52];      // bool since it only has to know if someone grabbed a card or not.
  int numPlayers = 2;
  int gameAmount, newCard, enteredHitLimit; // newCard is a variable used every time someone hits
  int cardsHeld[6] = {0,0,0,0,0,0}; // keeps track of the cards held by each player and the dealer
  int hitLimit[6] = {1,1,1,1,1,16}; // keeps track of the hit limit
  int aceAmount[6] = {0,0,0,0,0,0}; // potentially use char but not sure
  int playerWins[6]= {0,0,0,0,0,0}; // first being the dealer second being player 1 (our player in this case), etc.
  bool randomAmount[6] = {0,0,0,0,0,0}; // this is if I want it to be a random number for their hitLimit
  srand (time(NULL));               // set new "random" seed
  shuffle(deck, cardsHeld, aceAmount); // set everything to its initial state before continuing
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
      firstDeal(cardsHeld,deck,numPlayers,aceAmount); // we deal the initial two cards out to everyone
      for (int j = 0; j < numPlayers; j++){
        if (randomAmount[j]){   // if they wanted to have it as a random amount every time we set that hitlimit as a random amount every time.
          hitLimit[j] = rand() %5 + 14;
        }
        if (cardsHeld [j] < (hitLimit[j])){
          do {
            do{
                newCard = rand() % 52;
            } while(deck[newCard] == 0); // make sure someone isnt already holding that card
            deck[newCard] = 0; // get it out of the deck
            newCard = (newCard)/4 + 2;
            if (newCard >= 11 && newCard != 14){
              newCard = 10;
            }
            else if (newCard == 14){
              newCard = 11;
              aceAmount[j] ++;
            }
            if (((cardsHeld[j] + newCard) > 21) && (aceAmount[j] > 0))
            {
              aceAmount[j]--;
              cardsHeld[j] = cardsHeld[j] - 10;
            }
            cardsHeld[j] += newCard;

          } while(cardsHeld [j] < hitLimit[j]);
        }
        else if (cardsHeld[j] == hitLimit[j] && aceAmount[j] > 0){
          //this is called a soft 17 something the dealer must hit on
          do{
              newCard = rand() % 52;
          } while(deck[newCard] == 0); // make sure someone isnt already holding that card
          deck[newCard] = 0; // get it out of the deck
          newCard = (newCard)/4 + 2;
          if (newCard >= 11 && newCard != 14){
            newCard = 10;
          }
          else if (newCard == 14){
            newCard = 11;
            aceAmount[j] ++;
          }
          if (((cardsHeld[j] + newCard) > 21) && (aceAmount[j] > 0))
          {
            aceAmount[j]--;
            cardsHeld[j] = cardsHeld[j] - 10;
          }
          cardsHeld[j] += newCard;
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
      }*/

      shuffle (deck, cardsHeld, aceAmount);
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

void shuffle (bool deck[52], int cardsHeld[6], int aceAmount[6]){
  for(int i = 0; i < 52; i++){
    deck[i] = true;
  }
  for (int i = 0; i < 6; i++)
  {
    cardsHeld[i] = 0;
    aceAmount[i] = 0;
  }
}
void firstDeal(int cardsHeld[6], bool deck[52], int numPlayers, int aceAmount[6]){
  int newCard;
  for (int i = 0; i < numPlayers; i++)
  {
      do {
        newCard = rand() % 52;
      } while (deck[newCard] == 0);
      deck[newCard] = 0;
      newCard = (newCard)/4 + 2; // gotta figure out a formula for this

      if (newCard >= 11 && newCard != 14)
      {
        newCard = 10;
      }
      else if (newCard == 14)
      {
        newCard = 11;
        aceAmount[i] ++;
      }
      cardsHeld[i] += newCard;
    }
  for (int i = 0; i < numPlayers; i++)
  {
      do {
        newCard = rand() % 52;
      } while (deck[newCard] == 0);
      deck[newCard] = 0;
      newCard = (newCard)/4 + 2; // gotta figure out a formula for this

      if (newCard >= 11 && newCard != 14)
      {
        newCard = 10;
      }
      else if (newCard == 14)
      {
        newCard = 11;
        aceAmount[i] ++;
        if ((cardsHeld[i] + newCard) > 21)
        {
          newCard = 1;
          aceAmount[i] --;
        }
      }
      cardsHeld[i] += newCard;
      }
}
