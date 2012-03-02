#ifndef DllHeader
#define DllHeader

#define DLLexport __declspec(dllexport)


#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
typedef unsigned short int ui; 
const char EMPTY = ' ';			
const char x = 'X';
const char o = 'O';
const char TIE = 'T';
const char NONE = 'N';


  int askNumber(string question, ui high, ui low);
  bool isLegal(int move, const vector<char>* const board);


extern "C"
{

DLLexport  char winner(const vector<char>* const board);
DLLexport  int humanMove(const vector<char>* const board);
DLLexport  int computerMove(vector<char> board, char comp);


}

#endif
 
