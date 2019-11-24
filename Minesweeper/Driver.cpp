/*************************************************************
*
* Lab / Assignment: Lab1 - Minesweeper
*
* Overview:
*		This program allows the user to play the game Minesweeper.
*		The game consists of a grid of cells that represent a minefield
*		and the player trys to uncover all cells that are not a mine.
*		Uncovering all cells that are not mines wins, while uncovering
*		a cell that is a mine loses.
*
* Input:
*		In the initial menu, entering 'b' 'i' or 'e' starts a beginner,
*		intermediate, or expert game respectively, and 'x' exits the program.
*
*		During gameplay, to uncover a cell you enter its coordinate
*		as 'X Y' where X is how far right the cell is and Y is how
*		far down the cell is. To mark a cell, it is very similar
*		but you start with a lowercase 'm', the command to mark is 'm X Y'
*		If you want to exit the game before finishing, enter 'exit'
*
* Output:
*		Upon initial start, the program will display a message asking
*		the user to input the desired difficulty, or if they would
*		like to quit.
*
*		During gameplay, There is a grid of symbols represent cells
*		and numbered axis to help the user pick a coordinate.
*		The symbols for cells are: '?' = covered, 'M' = marked,
*		'-' = uncovered/blank, '#' where # is a number 1 to 8 = number cell,
*		'X' = mine/bomb. For readability, number cells are colored blue,
*		bombs are colored red, and marked cells are colored green.
*
*		After the user ends a game, it will output either a 'game over' message
*		or 'you win' message to report if they won, and go back to the 
*		initial start message asking for a difficulty.
*
**************************************************************/

/*************************************************************
* Author: Dillon Wall
* Filename: Driver.cpp
* Date Created: 1/19/2019
* Modifications:
**************************************************************/

#include "Minesweeper.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#define BUFFER_SIZE 255
#define GetMessage GetMessage //windows defines this to GetMessageW so redefine it back to original

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	bool exit = false;
	Random::Init();

	try
	{
		while (!exit)
		{
			char difficulty = '0';

			while (difficulty != Minesweeper::BEGINNER && difficulty != Minesweeper::INTERMEDIATE && difficulty != Minesweeper::EXPERT && difficulty != 'x')
			{
				cout << "Please enter a difficulty (b=Beginner, i=Intermediate, e=Expert, x=Exit):" << endl;
				cin >> difficulty;
			}

			if (difficulty != 'x')
			{
				Minesweeper game(difficulty);


				char inputBuffer[BUFFER_SIZE];

				while (cin.getline(inputBuffer, BUFFER_SIZE) && game.Update(inputBuffer))
				{
					game.Print();
				}

				//show game after its over
				game.Print();

				//print final result
				cout << endl;
				if(game.Won())
					cout << "  --==< Y O U   W I N ! >==--" << endl;
				else
					cout << "  --==< G A M E   O V E R >==--" << endl;
				cout << endl;
			}
			else
			{
				exit = true;
			}
		}
	}
	catch (Exception e)
	{
		cout << e.GetMessage() << endl;
	}
}
