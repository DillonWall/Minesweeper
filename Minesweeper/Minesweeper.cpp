/*************************************************************
* Author: Dillon Wall
* Filename: Minesweeper.cpp
* Date Created: 1/19/2019
* Modifications:
**************************************************************/


#include "Minesweeper.h"



Minesweeper::Minesweeper() : m_grid(nullptr)
{
	m_grid = new Grid(10, 10, 10);
}

Minesweeper::Minesweeper(char difficulty) : m_grid(nullptr)
{
	if (difficulty == BEGINNER)
	{
		m_grid = new Grid(10, 10, 10);
	}
	else if (difficulty == INTERMEDIATE)
	{
		m_grid = new Grid(16, 16, 40);
	}
	else if (difficulty == EXPERT)
	{
		m_grid = new Grid(16, 30, 100);
	}
	else
	{
		throw Exception("Incorrect difficulty sent to Minesweeper ctor");
	}
}


Minesweeper::~Minesweeper()
{
	delete m_grid;

	m_grid = nullptr;
}

Minesweeper::Minesweeper(const Minesweeper & copy) : m_grid(nullptr)
{
	m_grid = new Grid(*copy.m_grid);
}

Minesweeper & Minesweeper::operator=(const Minesweeper & rhs)
{
	if (this != &rhs)
	{
		delete m_grid;

		m_grid = new Grid(*rhs.m_grid);
	}

	return *this;
}

bool Minesweeper::Won() const
{
	return m_grid->Won();
}

// Note: if the user does not input a number, I do not explicitly check for that... 
// If you were to do so you could write a function like the one seen here to check: http://www.cplusplus.com/forum/beginner/170595/
bool Minesweeper::Update(char * input) 
{
	char * p;
	p = strtok(input, " "); // get a pointer to point to the input delimiting by spaces
	if (!p) return true; // if bad input exit the function but keep game going

	if (strcmp(p,"exit") == 0)
	{
		m_grid->UncoverAll();
		return false; //false stops the game
	}
	//else if (strcmp(p, "win") == 0)
	//{
	//	m_grid->UncoverAll();
	//	m_grid->SetWon();
	//}
	else if (strcmp(p, "m") == 0)
	{
		int x = 0;
		int y = 0;

		try
		{
			//get x
			p = strtok(NULL, " ");
			if (p)
				sscanf(p, "%d", &x);
			else
				return true; // if bad input exit the function but keep game going

			//get y
			p = strtok(NULL, " ");
			if (p)
				sscanf(p, "%d", &y);
			else
				return true; // if bad input exit the function but keep game going

			m_grid->Mark(x, y);
		}
		catch (...)
		{
			return true; // if bad input exit the function but keep game going
		}
	}
	else
	{
		//assume its a coordinate
		int x = 0;
		int y = 0;

		try
		{
			//get x (p is already x)
			if (p)
				sscanf(p, "%d", &x);
			else
				return true; // if bad input exit the function but keep game going

			//get y
			p = strtok(NULL, " ");
			if (p)
				sscanf(p, "%d", &y);
			else
				return true; // if bad input exit the function but keep game going

			return m_grid->Uncover(x, y);
		}
		catch (...)
		{
			return true; // if bad input exit the function but keep game going
		}
	}

}

void Minesweeper::Print()
{
	//clear window
	for (int i = 0; i < 20; ++i)
	{
		cout << endl;
	}

	m_grid->Print();
}
