#include <iostream>
#include <vector>
using namespace std;

class WordleBoard {
    
    string board[6][5];
    string solution;
    public:
      WordleBoard(string solution);
      //~WordleBoard();
      void setGuess(string guess);
      void printBoard();
      int count;
        //vector<char> checkGuess(vector<char> guess);
        //std::string getGuess();
        //string checkGuess(char guess
      bool win(string guess);

};