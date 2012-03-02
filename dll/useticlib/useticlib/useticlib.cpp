// useticlib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<string>
#include <Windows.h>
#include<vector>
#include<algorithm>

#include "useticlib.h"

const char EMPTY = ' ';			
const char x = 'X';
const char o = 'O';
const char TIE = 'T';
const char NONE = 'N';
void playGame();

HMODULE hLib;

// Dll function pointers //////////////////////////////////////////////////////////////////////////


 winner win;
 computerMove compmove;
 humanMove hummove;
 
///////////////////////////////////////////////////////////////////////////////////////////////////
// Open Dll and initialize pointers ///////////////////////////////////////////////////////////////
HMODULE InitP()
{
hLib = LoadLibrary(TEXT("tictaclib.dll"));
if(!hLib)
return NULL;

win = (winner)GetProcAddress(hLib, "winner");
compmove =(computerMove)GetProcAddress(hLib, "computerMove");
hummove = (humanMove)GetProcAddress(hLib, "humanMove");
return hLib;

}
////////////////////////////////////////////////////////////////////////////////////////////////////
void displayBoard(const vector<char>* const board)			//вивід таблиці
{
    cout << "\n\t" << (*board)[0] << " | "<< (*board)[1] << " | "<< (*board)[2];
    cout << "\n\t" << "---------";
    cout << "\n\t" << (*board)[3] << " | "<< (*board)[4] << " | "<< (*board)[5];
    cout << "\n\t" << "---------";
    cout << "\n\t" << (*board)[6] << " | "<< (*board)[7] << " | "<< (*board)[8];
    cout << "\n\n";
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void announceWinner(char winner, char human, char computer)			//оголошення переможця
{
    if (winner == computer)					//якщо переможець - компютер
        cout << "computer" << " wins!\n";
            
    else if (winner == human)				//якщо перемогла людина
        cout << "human" << " wins!\n";
      
    else											//якщо нічия
    {
        cout << "It's a tie.\n";
        cout << "You were most lucky, human, and somehow managed to tie me.\n";
        cout << "Celebrate... \n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
char playAgain(string question)				//будете грати ще?
{
    char ans = 'n';
    cout << question;
    cin >> ans;
    return ans;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void instructions()					//вивід інструкцій
{
    cout << "Welcome to the ultimate man-machine showdown: Tic-Tac-Toe.\n";
   
    cout << "Make your move known by entering a number, 1 - 9, as illustrated:\n\n";
 
    cout << "1 | 2 | 3\n";
    cout << "---------\n";
    cout << "4 | 5 | 6\n";
    cout << "---------\n";
    cout << "7 | 8 | 9\n\n";
}
 ////////////////////////////////////////////////////////////////////////////////////////////////////
char askYesNo(string question)				//будете ходити першим?
{
    char response;
    do
    {
        cout << question << "(y/n): ";
        cin >> response;
    } while (response != 'y' && response != 'n');
    return response;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	InitP();
	 int move;
    const int NUM_SQUARES = 9;
    vector<char> board(NUM_SQUARES, EMPTY);			//створення пустого поля(дошки)
 
    instructions();								//вивід інструкцій
    char computer = x;							
    char human = o;								
    char ans = askYesNo("Do you want to go first?");
    if (ans == 'y')						//якщо людина ходить першою
    {
        human = x;						// то вона отримує Х
        computer = o;						//а компютер - 0
    }
    char turn = x;				
    displayBoard(&board);					//вивід поки ще пустого поля
 
    while (win(&board) == NONE)			//поки ніхто не виграв і не нічия
    {
        if (turn == human)					//якщо черга ходу гравця
        {
            move = hummove(&board);			//гравець ходить
            board[move] = human;
        }
 
        else
        {
            move = compmove(board, computer);			//інакше - компютер
            board[move] = computer;
        }
        displayBoard(&board);					//вивід поля з результатами ходів
 
        if (turn == human)					//зміна черги ходу
        {
            turn = computer;
        }
        else { turn = human; }
    }
    announceWinner(win(&board), human, computer);			//вивід переможця
    ans = playAgain("Do you want to play again? (y/n): ");			//Хочете грати ще раз?
    if (ans == 'y')								//якщо так 
    {
        cout << endl;
        playGame();							//гра спочатку
    }
    else										//якщо ні
    {
        cout << "Thanks for playing!";				//гра завершена
        return 0;
    }
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void playGame()
{
    main();
}

