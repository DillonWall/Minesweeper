/*************************************************************
* Author: Dillon Wall
* Filename: Minesweeper.h
* Date Created: 1/19/2019
* Modifications:
**************************************************************/

#pragma once

#include "Grid.h"


/************************************************************************
* Class: Minesweeper
*
* Purpose: This class is the main game controller and handles the Input and Printing of the game
*
* Manager functions:
* Minesweeper()
*		Creates default Minesweeper with beginner settings
* Minesweeper(char difficulty)
*		Creates a Minesweeper game with the specified difficulty
* Minesweeper(const Minesweeper& other)
* Minesweeper& operator=(const Minesweeper& other)
* ~Minesweeper()
*
* Methods:
* bool Won() const
*		Checks the grid to see if the game is won
* bool Update(char * input)
*		Takes in a line of input and parses it to do the correct actions
* void Print()
*		Prints the game to the console
*
*
*************************************************************************/
class Minesweeper
{
public:
	enum DIFFICULTY : char { BEGINNER = 'b' , INTERMEDIATE = 'i' , EXPERT = 'e' };

	Minesweeper();
	Minesweeper(char difficulty);
	~Minesweeper();
	Minesweeper(const Minesweeper& copy);
	Minesweeper& operator=(const Minesweeper& rhs);

	bool Won() const;

	bool Update(char * input);
	void Print();

private:
	Grid* m_grid;
};

