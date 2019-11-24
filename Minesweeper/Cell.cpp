/*************************************************************
* Author: Dillon Wall
* Filename: Cell.cpp
* Date Created: 1/19/2019
* Modifications:
**************************************************************/


#include "Cell.h"



Cell::Cell() : m_state(COVERED), m_isBomb(false), m_adjacent(0)
{
}

Cell::Cell(bool isBomb, int adjacent, STATES state) : m_state(state), m_isBomb(isBomb), m_adjacent(adjacent)
{
}


Cell::~Cell()
{
	//nothing to delete

	m_state = COVERED;
	m_isBomb = false;
	m_adjacent = 0;
}

Cell::Cell(const Cell & copy) : m_state(copy.m_state), m_isBomb(copy.m_isBomb), m_adjacent(copy.m_adjacent)
{
}

Cell & Cell::operator=(const Cell & rhs)
{
	if (this != &rhs)
	{
		//nothing to delete

		m_state = rhs.m_state;
		m_isBomb = rhs.m_isBomb;
		m_adjacent = rhs.m_adjacent;
	}

	return *this;
}

Cell & Cell::operator++()
{
	++m_adjacent;
	return *this;
}

char Cell::GetState() const
{
	return m_state;
}

void Cell::SetState(STATES state)
{
	m_state = state;
}

bool Cell::IsBomb() const
{
	return m_isBomb;
}

void Cell::SetBomb(bool isBomb)
{
	m_isBomb = isBomb;
}

int Cell::GetAdjacent() const
{
	return m_adjacent;
}

void Cell::SetAdjacent(int adjacent)
{
	m_adjacent = adjacent;
}
