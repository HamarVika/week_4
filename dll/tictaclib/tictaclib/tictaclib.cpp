// tictaclib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "tictaclib.h"

 
extern "C" {
	
 
 //////////////////////////////////////////////////////////////////
DLLexport int askNumber(string question, ui high, ui low) {				//отримання від користувача ходу
    ui number;
    do {
        cout << question << "("<< low << "- "<< high << "): ";
        cin >> number;
    } while (number > high || number < low);
    //return number+1;
	return number;							//повертає хід кравця
}

 //////////////////////////////////////////////////////////////////
DLLexport char winner(const vector<char>* const board)			//для визначення переможця
{
    const int WINNING_ROWS[8][3] = { {0, 1, 2},			//всі можливі виграшні трійки
                                        {3, 4, 5},
                                        {6, 7, 8},
                                        {0, 3, 6},
                                        {1, 4, 7},
                                        {2, 5, 8},
                                        {0, 4, 8},
                                        {2, 4, 6}
                                       };
 
    const int TOTAL_ROWS = 8;
// якщо хоч якийсь виграшний рядок має три однакових значення(і не пустий) 
// то переможець визначений
for(ui row = 0; row < TOTAL_ROWS; ++row)
{
    if ( ((*board)[WINNING_ROWS[row][0]] != EMPTY) &&
         ((*board)[WINNING_ROWS[row][0]] == (*board)[WINNING_ROWS[row][1]]) &&
         ((*board)[WINNING_ROWS[row][1]] == (*board)[WINNING_ROWS[row][2]]) )
    {
         return (*board)[WINNING_ROWS[row][0]];			//повертає значення (Х/0)
    }
}
 
 
// оскільки ніхто не переміг - перевірка на нічию(якщо немає вільних комірок) 
if (count(board->begin(), board->end(), EMPTY) == 0)
    return TIE;
 
// якщо ніхто не переміг і не нічия - гра продовжується
return NONE;
}
 //////////////////////////////////////////////////////////////////
DLLexport inline bool isLegal(int move, const vector<char>* const board)		//чи комірка вільна
{
    return ((*board)[move] == EMPTY);
}
//////////////////////////////////////////////////////////////////
 DLLexport int humanMove(const vector<char>* const board)			//хід гравця
{
    int move = askNumber("Where will you move?", (board->size()),1);		//в move - результат ходу
    //while (!isLegal(move-2, board))
	while (!isLegal(move-1, board))			//якщо комірка зайнята
    {
        cout << "\nOops! That square is already occupied\n";
        move = askNumber("Where will you move?", (board->size()),1);
    }
    cout << "Fine...\n";
   // return move-2;
	return move-1;				//повертає результат ходу
}
 //////////////////////////////////////////////////////////////////
DLLexport int computerMove(vector<char> board, char computer)				//хід компютера
{
    cout << "I shall take square number ";
 
    // компютер, якщо може перемогти в наступному ході, робить хід
    for(int move = 0; move < board.size(); ++move)
    {
        if (isLegal(move, &board))			//якщо комірка не зайнята
        {
            board[move] = computer;
            if (winner(&board) == computer)			//якщо компютер переміг
            {
                cout << move+1 << endl;
                return move;					//повертає результат ходу
            }
            // якщо ж ні - відміняє цей хід
            board[move] = EMPTY;
        }
    }
    // Якщо гравець може перемогти в наступному ході - блокує цей хід
    char human;
    if (computer == x)		//обмін
    {
        human = o;
    }
    else { human = x; }
 
 
    for(int move = 0; move < board.size(); ++move)
    {
        if (isLegal(move, &board))			//якщо комірка не зайнята
        {
            board[move] = human;
            if (winner(&board) == human)			//якщо перемагає гравець
            {
                cout << move+1 << endl;
                return move;						//то компютер ходить сюди
            }
            // якщо ж ні - віміняє цей хід
            board[move] = EMPTY;
        }
    }
    // перелік найкращих ходів(центральна, кутові, аж потім бокові)
    const ui BEST_MOVES[] = {5, 1, 3, 7, 9, 2, 4, 6, 8};
    // якщо ніхто не може перемогти в наступному ході - використати цей перелік
    for(ui i = 0; i < board.size(); ++i)
    {
        int move = BEST_MOVES[i];
        if (isLegal(move-1, &board))			//якщо хід можливий
        {
            cout << move << endl;
            return move-1;
        }
     }
    return 0;
}
 


}


