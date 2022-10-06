#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "WordleBoard.h"
using namespace std;

bool isValid(string word, vector<string> wordList);


int main() {
  string word, solution;
  ifstream wordFile;
  vector<string>wordList;

  wordFile.open("sgb-words.txt");
  bool is_open(wordFile);
  if (!is_open) //verifies that file exists
    cout << "no word file found";
  else {
    //put words into vector
    while (wordFile.peek() != EOF) {
      getline(wordFile, word);
      wordList.push_back(word);
    }
    sort(wordList.begin(), wordList.end());
    
    //pick random word
    srand(time(NULL));
    solution = wordList[rand() % wordList.size()];
    //cout << solution << "**"<< endl; //prints solution for testing purposes
    
    
    /* game starts here */
    WordleBoard game1(solution); //create new game
    //start the guessing!
    while (game1.count != 6 && !game1.win(word)) {
      cout << "Enter word: ";
      cin >> word;
      //make sure word has correct length
      while (word.length() != 5) {
        cout << "word isn't the right amount of letters" << endl
            << "Enter word: ";
        cin >> word;
      }
      while (!isValid(word, wordList)) {
        cout << "not a valid word" << endl
             << "Enter word: ";
        cin >> word;
      }
      //check word - FIXME
      game1.setGuess(word);
      game1.printBoard();
    }
    if (game1.win(word)) {
      cout << "YOU WON!!";
    }
    else
      cout << "game over" << endl << "The word was: " << solution;
    
  }


  
  return 0;
  
}

bool isValid(string word, vector<string> wordList) {
  return binary_search(wordList.begin(), wordList.end(), word);
}