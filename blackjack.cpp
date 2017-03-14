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
  bool deck[52];
  int numPlayers = 2;
  int gameAmount = 1;
  int cardsHeld[6] = {0,0,0,0,0,0};
  int hitLimit[6] = {1,1,1,1,1,16};
  int newCard;
  int aceAmount[6] = {0,0,0,0,0,0}; // potentially use char but not sure
  int test;
  int playerWins[6]= {0,0,0,0,0,0}; // first being the dealer second being player 1 (our player in this case), etc.
  bool randomAmount[6] = {0,0,0,0,0,0}; // this is if I want it to be a random number for their hitLimit
  srand (time(NULL));
  shuffle(deck, cardsHeld, aceAmount);
  do{
  if (numPlayers <2 || numPlayers >6) {cout << endl << "Please try again" << endl << endl;}
  cout << endl << "Number of players (note there will always be at minimum 2 at maximum 6 (player one will assume to be your character))" << endl;
  cin >> numPlayers;
} while (numPlayers <2 || numPlayers >6);
  do {
    cout << endl << "Number of times the game is played (note there will always be at minimum 1 at maximum 1,000,000,000)" << endl;
    cin >> gameAmount;
  } while(gameAmount < 1 || gameAmount > 1000000000);

  for (int i = 0; i < (numPlayers); i++){
    do{
    if (i == numPlayers - 1){test = 16; break;}
    cout << endl << "Set hit limit for character " << i + 1 << "." << endl <<"Put '0' if you want it to be a random number between 14 and 18." << endl << "Put a negative number if you want their hit limit to be random every hand" << endl << endl;
    cin >> test;
    if (test == 0)
    {
      test = (rand() % 5) + 14;
      break;
    }
    else if (test < 0) {randomAmount[i] = true; test = (rand() % 5) + 14;}
  }while (test > 21 || test < 1);
  // if (i == numPlayers - 1) {test = 16;}
  test++;
  hitLimit[i] = test;
  }

  cout << endl;

  for (int i = 0; i < gameAmount; i++){
      firstDeal(cardsHeld,deck,numPlayers,aceAmount);
      for (int j = 0; j < numPlayers; j++){
        if (randomAmount[j]){
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
            /*
            if (j == numPlayers - 1 && cardsHeld[j] == 17 && aceAmount[j] > 0){
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
            }*/
            if (cardsHeld[j] == hitLimit[j] && aceAmount[j] > 0){
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
          } while(cardsHeld [j] < hitLimit[j]);
        }
      }   // after this everyone should have the card they were given
          // then we have to see who won
      for (int j = 0; j < (numPlayers - 1); j++){
        if ((cardsHeld[j] <= 21) && (cardsHeld[j] > cardsHeld[numPlayers - 1]) || (cardsHeld[j] <= 21) && (cardsHeld[numPlayers - 1] > 21) )
        {playerWins[j] ++;}
        else if ((cardsHeld[j] == cardsHeld[numPlayers -1])) {}
        else {playerWins[numPlayers - 1]++;}
      }
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
