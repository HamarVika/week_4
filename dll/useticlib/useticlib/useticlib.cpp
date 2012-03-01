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

 askNumber asknum;
 winner win;
 isLegal isleg;
 computerMove compmove;
 humanMove hummove;
///////////////////////////////////////////////////////////////////////////////////////////////////
// Open Dll and initialize pointers ///////////////////////////////////////////////////////////////
HMODULE InitP()
{
hLib = LoadLibrary(TEXT("tictaclib.dll"));
if(!hLib)
return NULL;
asknum = (askNumber)GetProcAddress(hLib, "askNumber");
win = (winner)GetProcAddress(hLib, "winner");
isleg = (isLegal)GetProcAddress(hLib, "isLegal");
compmove =(computerMove)GetProcAddress(hLib, "computerMove");
hummove = (humanMove)GetProcAddress(hLib, "humanMove");
return hLib;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void displayBoard(const vector<char>* const board)			//���� �������
{
    cout << "\n\t" << (*board)[0] << " | "<< (*board)[1] << " | "<< (*board)[2];
    cout << "\n\t" << "---------";
    cout << "\n\t" << (*board)[3] << " | "<< (*board)[4] << " | "<< (*board)[5];
    cout << "\n\t" << "---------";
    cout << "\n\t" << (*board)[6] << " | "<< (*board)[7] << " | "<< (*board)[8];
    cout << "\n\n";
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void announceWinner(char winner, char human, char computer)			//���������� ���������
{
    if (winner == computer)					//���� ���������� - ��������
        cout << "computer" << " wins!\n";
            
    else if (winner == human)				//���� ��������� ������
        cout << "human" << " wins!\n";
      
    else											//���� ����
    {
        cout << "It's a tie.\n";
        cout << "You were most lucky, human, and somehow managed to tie me.\n";
        cout << "Celebrate... \n";
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
char playAgain(string question)				//������ ����� ��?
{
    char ans = 'n';
    cout << question;
    cin >> ans;
    return ans;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void instructions()					//���� ����������
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
char askYesNo(string question)				//������ ������ ������?
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
    vector<char> board(NUM_SQUARES, EMPTY);			//��������� ������� ����(�����)
 
    instructions();								//���� ����������
    char computer = x;							
    char human = o;								
    char ans = askYesNo("Do you want to go first?");
    if (ans == 'y')						//���� ������ ������ ������
    {
        human = x;						// �� ���� ������ �
        computer = o;						//� �������� - 0
    }
    char turn = x;				
    displayBoard(&board);					//���� ���� �� ������� ����
 
    while (win(&board) == NONE)			//���� ���� �� ������ � �� ����
    {
        if (turn == human)					//���� ����� ���� ������
        {
            move = hummove(&board);			//������� ������
            board[move] = human;
        }
 
        else
        {
            move = compmove(board, computer);			//������ - ��������
            board[move] = computer;
        }
        displayBoard(&board);					//���� ���� � ������������ ����
 
        if (turn == human)					//���� ����� ����
        {
            turn = computer;
        }
        else { turn = human; }
    }
    announceWinner(win(&board), human, computer);			//���� ���������
    ans = playAgain("Do you want to play again? (y/n): ");			//������ ����� �� ���?
    if (ans == 'y')								//���� ��� 
    {
        cout << endl;
        playGame();							//��� ��������
    }
    else										//���� �
    {
        cout << "Thanks for playing!";				//��� ���������
        return 0;
    }
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void playGame()
{
    main();
}

