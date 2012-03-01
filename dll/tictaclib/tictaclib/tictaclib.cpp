// tictaclib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "tictaclib.h"

 
extern "C" {
	
 
 //////////////////////////////////////////////////////////////////
DLLexport int askNumber(string question, ui high, ui low) {				//��������� �� ����������� ����
    ui number;
    do {
        cout << question << "("<< low << "- "<< high << "): ";
        cin >> number;
    } while (number > high || number < low);
    //return number+1;
	return number;							//������� ��� ������
}

 //////////////////////////////////////////////////////////////////
DLLexport char winner(const vector<char>* const board)			//��� ���������� ���������
{
    const int WINNING_ROWS[8][3] = { {0, 1, 2},			//�� ������ ������� �����
                                        {3, 4, 5},
                                        {6, 7, 8},
                                        {0, 3, 6},
                                        {1, 4, 7},
                                        {2, 5, 8},
                                        {0, 4, 8},
                                        {2, 4, 6}
                                       };
 
    const int TOTAL_ROWS = 8;
// ���� ��� ������ ��������� ����� �� ��� ��������� ��������(� �� ������) 
// �� ���������� ����������
for(ui row = 0; row < TOTAL_ROWS; ++row)
{
    if ( ((*board)[WINNING_ROWS[row][0]] != EMPTY) &&
         ((*board)[WINNING_ROWS[row][0]] == (*board)[WINNING_ROWS[row][1]]) &&
         ((*board)[WINNING_ROWS[row][1]] == (*board)[WINNING_ROWS[row][2]]) )
    {
         return (*board)[WINNING_ROWS[row][0]];			//������� �������� (�/0)
    }
}
 
 
// ������� ���� �� ������ - �������� �� ����(���� ���� ������ ������) 
if (count(board->begin(), board->end(), EMPTY) == 0)
    return TIE;
 
// ���� ���� �� ������ � �� ���� - ��� ������������
return NONE;
}
 //////////////////////////////////////////////////////////////////
DLLexport inline bool isLegal(int move, const vector<char>* const board)		//�� ������ �����
{
    return ((*board)[move] == EMPTY);
}
//////////////////////////////////////////////////////////////////
 DLLexport int humanMove(const vector<char>* const board)			//��� ������
{
    int move = askNumber("Where will you move?", (board->size()),1);		//� move - ��������� ����
    //while (!isLegal(move-2, board))
	while (!isLegal(move-1, board))			//���� ������ �������
    {
        cout << "\nOops! That square is already occupied\n";
        move = askNumber("Where will you move?", (board->size()),1);
    }
    cout << "Fine...\n";
   // return move-2;
	return move-1;				//������� ��������� ����
}
 //////////////////////////////////////////////////////////////////
DLLexport int computerMove(vector<char> board, char computer)				//��� ���������
{
    cout << "I shall take square number ";
 
    // ��������, ���� ���� ��������� � ���������� ���, ������ ���
    for(int move = 0; move < board.size(); ++move)
    {
        if (isLegal(move, &board))			//���� ������ �� �������
        {
            board[move] = computer;
            if (winner(&board) == computer)			//���� �������� ������
            {
                cout << move+1 << endl;
                return move;					//������� ��������� ����
            }
            // ���� � � - ������ ��� ���
            board[move] = EMPTY;
        }
    }
    // ���� ������� ���� ��������� � ���������� ��� - ����� ��� ���
    char human;
    if (computer == x)		//����
    {
        human = o;
    }
    else { human = x; }
 
 
    for(int move = 0; move < board.size(); ++move)
    {
        if (isLegal(move, &board))			//���� ������ �� �������
        {
            board[move] = human;
            if (winner(&board) == human)			//���� �������� �������
            {
                cout << move+1 << endl;
                return move;						//�� �������� ������ ����
            }
            // ���� � � - ����� ��� ���
            board[move] = EMPTY;
        }
    }
    // ������ ��������� ����(����������, �����, �� ���� �����)
    const ui BEST_MOVES[] = {5, 1, 3, 7, 9, 2, 4, 6, 8};
    // ���� ���� �� ���� ��������� � ���������� ��� - ����������� ��� ������
    for(ui i = 0; i < board.size(); ++i)
    {
        int move = BEST_MOVES[i];
        if (isLegal(move-1, &board))			//���� ��� ��������
        {
            cout << move << endl;
            return move-1;
        }
     }
    return 0;
}
 


}


