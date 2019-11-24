/*************************************************************
* Author: Dillon Wall
* Filename: Cell.h
* Date Created: 1/19/2019
* Modifications:
**************************************************************/

#pragma once


/************************************************************************
* Class: Cell
*
* Purpose: This class represents a cell from a Minesweeper grid/board
*
* Manager functions:
* Cell()
*		Creates default Cell where the state is COVERED, and is not a bomb and not bombs are ajacent
* Cell(bool isBomb, int adjacent, STATES state = COVERED)
*		Creates a Cell based on if its a bomb, how many adjacent, and what state it is (default COVERED)
* Cell(const Cell& other)
* Cell& operator=(const Cell& other)
* ~Cell()
* Cell& operator++()
*		Adds one to the amount of adjacent bombs
*
* Methods:
* char GetState() const
* void SetState(STATES state)
* bool IsBomb() const
*		returns if it is a bomb
* void SetBomb(bool isBomb)
*		sets m_isBomb
* int GetAdjacent() const
* void SetAdjacent(int adjacent)
*
*
*
*************************************************************************/
class Cell
{
public:
	enum STATES : char {COVERED = '?', NUMBER = 'N', BLANK = '-', MARKED = 'M', BOMB = 'X'};

	Cell();
	Cell(bool isBomb, int adjacent, STATES state = COVERED);
	~Cell();
	Cell(const Cell& copy);
	Cell& operator=(const Cell& rhs);
	Cell& operator++();

	char GetState() const;
	void SetState(STATES state);
	bool IsBomb() const;
	void SetBomb(bool isBomb);
	int GetAdjacent() const;
	void SetAdjacent(int adjacent);

private:
	STATES m_state;
	bool m_isBomb;
	int m_adjacent;
};

