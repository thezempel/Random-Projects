#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "WordleBoard.h"
using namespace std;

WordleBoard::WordleBoard(string correct) {
    count = 0;
    cout << "New game started " << endl;
    solution = correct;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            board[i][j] = '_';
        }
    }
}

void WordleBoard::printBoard(){
    for (int i = 0; i < 6; i++) {
      cout << i+1 << " ";
        for (int j = 0; j < 5; j++) {
            cout << board[i][j] << " ";
        }
      cout << endl;
    }
  //cout << solution;
}

void WordleBoard::setGuess(string guess) {
  vector<char>word(guess.begin(), guess.end());
  vector<char> solVec(solution.begin(), solution.end());
  vector<string>checked;
  string x, y = "";

  for (int i = 0; i < 5; i++) {
    y += word[i];
    if (word[i] == solVec[i]) {
      //change color to Green
      x = "\033[1;32m" + y + "\033[0m";
      checked.push_back(x);
      solVec[i] = '.';
    }
    else if (std::find(solution.begin(), solution.end(), word[i]) != solution.end()) {
      //change color to Yellow
      x = "\033[1;33m" + y + "\033[0m";
      checked.push_back(x);
    }
    else {
      checked.push_back(y);
    }
    board[count][i] = checked[i];
    x = "";
    y = "";
    
      
  }
  count++;
}

bool WordleBoard::win(string guess) {
  return (guess == solution);
}





/*
void WordleBoard::setGuess(string guess) {
  vector<char> word(guess.begin(), guess.end());
  string newWord[5];
  for (int i = 0; i < 5; i++) {
    newWord[i] = checkGuess(word[i]);//not passiong anything
  }
  // = checkGuess(word);
  for (int i = 0; i < 5; i++) {
    board[count][i] = newWord[i];
  }
  count++;

}

string WordleBoard::checkGuess(char check) {
  //char c = guess[];
  string guess;
  string check1 = "";
  check1 += check;
  //cout << c;
  if (std::find(solution.begin(), solution.end(), check) != solution.end()) {
     guess = "\033[1;32" + check1 + "\033[0m\n"; 
    cout << guess;
  }
  return guess;
}



//need fix if nest
vector<char> WordleBoard::checkGuess(vector<char> word) {
  vector<char> solVec(solution.begin(), solution.end());
  char x;
  for (int i = 0; i < 5; i++) {
    //cout << guess[i];
    cout << solVec[i] << "*";
    //if (solution.find(word[i])) {
    if (std::find(solution.begin(), solution.end(), word[i]) != solution.end()) {
      //change color to Yellow
      cout << "@";
      x = '!';
      
      if (word[i] == solVec[i]) {
      //change color to Green
        cout << "^";
        x = '^';
        }
    }
    else
      x = word[i];
    word[i] = x;

  }
  cout << endl;
  return word;
}
*/