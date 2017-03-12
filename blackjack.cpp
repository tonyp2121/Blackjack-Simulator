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
  int amountOfTimesPlayed = 1;
  int cardsHeld[6] = {0,0,0,0,0,0};
  int hitLimit[6] = {16,1,1,1,1,1};
  int newCard;
  int aceAmount[6] = {0,0,0,0,0,0}; // potentially use char but not sure
  int test;
  shuffle(deck, cardsHeld, aceAmount);
  do{
  if (numPlayers <2 || numPlayers >6) {cout << endl << "Please try again and this time dont fuck up simple shit please" << endl << endl;}
  cout << "Number of players (note there will always be at minimum 2 at maximum 6 (player one will assume to be your character))" << endl;
  cin >> numPlayers;
} while (numPlayers <2 || numPlayers >6);
  do {
    cout << "Number of times the game is played (note there will always be at minimum 1 at maximum 1,000,000)" << endl;
    cin >> amountOfTimesPlayed;
  } while(amountOfTimesPlayed < 1 || amountOfTimesPlayed > 1000000);

  for (int i = 0; i < (numPlayers - 1); i++){
    do{
    cout << "Set hit limit for character " << i + 1 << ". Put '0' if you want it to be a random number between 14 and 18." << endl;
    cin >> test;
    if (test == 0)
    {
      test = (rand() % 5) + 14;
      break;
    }
  }while (test > 21 || test < 1);
  hitLimit[i+1] = test;
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
