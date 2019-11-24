/*************************************************************
* Author: Dillon Wall
* Filename: Grid.h
* Date Created: 1/19/2019
* Modifications:
**************************************************************/

#pragma once

#include "Cell.h"
#include "Array2D.h"
#include "Exception.h"
#include "Random.h"
#include <iostream>
#include <Windows.h>

using std::cout;
using std::endl;


/************************************************************************
* Class: Grid
*
* Purpose: This class represents a brid/board from Minesweeper
*
* Manager functions:
* Grid()
*		Creates default Grid with no cells, bombs, or uncovered
* Grid(int width, int height, int numBombs)
*		Creates a Grid with a specified width and height of cells and number of bombs
* Grid(const Grid& other)
* Grid& operator=(const Grid& other)
* ~Grid()
*
* Methods:
* void Mark(int x, int y)
*		turns covered cells into marked cells and visa-versa
* bool Uncover(int x, int y)
*		Helper function for FloodUncover, which uncovers the cell and any subsequent cells
* void UncoverAll()
*		Uncovers all cells in the grid
* void Print()
*		cout to the console the grid/board and also the coordinates
* bool Won() const
*		returns true if only bombs are left and all other tiles are uncovered, otherwise false
* void SetWon()
*		sets number of uncovered to the correct amount to win. Mainly for testing purposes only
*
* void FloodUncover(int x, int y)
*		Starts at the specified coordinate and recusively uncover any cells around it
*		that should subsequently be uncovered
*
*************************************************************************/
class Grid
{
public:
	Grid();
	Grid(int width, int height, int numBombs);
	~Grid();
	Grid(const Grid& copy);
	Grid& operator=(const Grid& rhs);

	void Mark(int x, int y);
	bool Uncover(int x, int y);
	void UncoverAll();
	void Print();

	bool Won() const;
	void SetWon();

	static HANDLE hConsole;

private:
	void FloodUncover(int x, int y);

	Array2D<Cell>* m_cells;
	int m_numBombs, m_numUncovered;
};

