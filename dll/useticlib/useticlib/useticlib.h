#ifndef Header
#define Header

#include <iostream>
using namespace std;
typedef unsigned short int ui;


typedef  char (*winner)(const vector<char>* const board);
typedef int (*computerMove)(vector<char> board, char computer);
typedef	int (*humanMove)(const vector<char>* const board);

#endif