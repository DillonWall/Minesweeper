/*************************************************************
* Author: Dillon Wall
* Filename: Grid.cpp
* Date Created: 1/19/2019
* Modifications:
**************************************************************/


#include "Grid.h"

HANDLE Grid::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

Grid::Grid() : m_cells(nullptr), m_numBombs(0), m_numUncovered(0)
{
}

Grid::Grid(int width, int height, int numBombs) : m_cells(nullptr), m_numBombs(numBombs), m_numUncovered(0)
{
	m_cells = new Array2D<Cell>(width, height);
	
	//create bombs
	for (int i = 0; i < numBombs; ++i)
	{
		int x = Random::GetRand(width-1);
		int y = Random::GetRand(height-1);
		while ((*m_cells)[x][y].IsBomb())
		{
			x = Random::GetRand(width-1);
			y = Random::GetRand(height-1);
		}
		(*m_cells)[x][y].SetBomb(true);
	}

	//set adjacency numbers
	for (int r = 0; r < m_cells->GetRows(); ++r)
	{
		for (int c = 0; c < m_cells->GetColumns(); ++c)
		{
			if ((*m_cells)[r][c].IsBomb())
			{
				//add to each adjacent cell
				for (int rr = -1; rr <= 1; ++rr)
				{
					for (int cc = -1; cc <= 1; ++cc)
					{
						//check if target cell is in bounds
						if (r + rr >= 0 && r + rr < m_cells->GetRows() &&
							c + cc >= 0 && c + cc < m_cells->GetColumns())
							++(*m_cells)[r + rr][c + cc]; //pre increment for cell increments m_adjacent
					}
				}
			}
		}
	}
}


Grid::~Grid()
{
	delete m_cells;

	m_cells = nullptr;
	m_numBombs = 0;
	m_numUncovered = 0;
}

Grid::Grid(const Grid & copy) : m_cells(nullptr), m_numBombs(copy.m_numBombs), m_numUncovered(copy.m_numUncovered)
{
	m_cells = new Array2D<Cell>(*copy.m_cells);
}

Grid & Grid::operator=(const Grid & rhs)
{
	if (this != &rhs)
	{
		delete m_cells;

		m_numBombs = rhs.m_numBombs;
		m_numUncovered = rhs.m_numUncovered;
		m_cells = new Array2D<Cell>(*rhs.m_cells);
	}

	return *this;
}

void Grid::Mark(int x, int y)
{
	if((*m_cells)[y][x].GetState() == Cell::COVERED)
		(*m_cells)[y][x].SetState(Cell::MARKED);
	else if((*m_cells)[y][x].GetState() == Cell::MARKED)
		(*m_cells)[y][x].SetState(Cell::COVERED);
}

bool Grid::Uncover(int x, int y)
{
	if ((*m_cells)[y][x].IsBomb())
	{
		UncoverAll();

		return false;
	}

	FloodUncover(x, y);

	//check if won
	if (Won())
	{
		UncoverAll(); //show the bombs
		return false; //end game
	}

	return true;
}

void Grid::UncoverAll()
{
	for (int r = 0; r < m_cells->GetRows(); ++r)
	{
		for (int c = 0; c < m_cells->GetColumns(); ++c)
		{
			if ((*m_cells)[r][c].GetState() == Cell::COVERED || (*m_cells)[r][c].GetState() == Cell::MARKED)
			{
				if ((*m_cells)[r][c].IsBomb())
				{
					(*m_cells)[r][c].SetState(Cell::BOMB);
				}
				else if ((*m_cells)[r][c].GetAdjacent() > 0)
				{
					(*m_cells)[r][c].SetState(Cell::NUMBER);
				}
				else
				{
					(*m_cells)[r][c].SetState(Cell::BLANK);
				}
			}
		}
	}
}

void Grid::Print()
{
	for (int r = 0; r < m_cells->GetRows(); ++r)
	{
		for (int c = 0; c < m_cells->GetColumns(); ++c)
		{
			char state = (*m_cells)[r][c].GetState();
			if (state == Cell::NUMBER)
			{
				int adj = (*m_cells)[r][c].GetAdjacent();
				if (adj > 8) throw Exception("Num adjacent bombs exceeds 8");

				SetConsoleTextAttribute(hConsole, 9); //set color of text to blue
				cout << " " << adj;
				SetConsoleTextAttribute(hConsole, 15); //back to white
			}
			else if (state == Cell::BOMB)
			{
				SetConsoleTextAttribute(hConsole, 12); //set color of text to red
				cout << " " << state;
				SetConsoleTextAttribute(hConsole, 15); //back to white
			}
			else if (state == Cell::MARKED)
			{
				SetConsoleTextAttribute(hConsole, 10); //set color of text to green
				cout << " " << state;
				SetConsoleTextAttribute(hConsole, 15); //back to white
			}
			else
				cout << " " << state;
		}
		//row indicators
		cout << " || " << r << endl;
	}

	//formatting for column indicators
	for (int c = 0; c < m_cells->GetColumns(); ++c)
	{
		cout << "--";
	}
	cout << "-" << endl;
	for (int c = 0; c < m_cells->GetColumns(); ++c)
	{
		cout << "|" << (int)(c/10);
	}
	cout << "|" << endl;
	for (int c = 0; c < m_cells->GetColumns(); ++c)
	{
		cout << "|" << c%10;
	}
	cout << "|" << endl;
}

bool Grid::Won() const
{
	return m_numUncovered == m_cells->GetRows() * m_cells->GetColumns() - m_numBombs;
}

void Grid::SetWon()
{
	m_numUncovered = m_cells->GetRows() * m_cells->GetColumns() - m_numBombs;
}

void Grid::FloodUncover(int x, int y)
{
	char state = (*m_cells)[y][x].GetState();
	if (state == Cell::COVERED || state == Cell::MARKED)
	{
		++m_numUncovered;

		///Testing///
		//if ((*m_cells)[y][x].IsBomb())
		//{
		//	(*m_cells)[y][x].SetState(Cell::BOMB);
		//	throw Exception("FloodUncover uncovered bomb");
		//}

		if ((*m_cells)[y][x].GetAdjacent() > 0)
		{
			(*m_cells)[y][x].SetState(Cell::NUMBER);
		}
		else
		{
			(*m_cells)[y][x].SetState(Cell::BLANK);

			//Recurse further (all 8 square adjacent)
			if (y - 1 >= 0)
				FloodUncover(x, y - 1);
			if (x + 1 < m_cells->GetColumns())
				FloodUncover(x + 1, y);
			if (y + 1 < m_cells->GetRows())
				FloodUncover(x, y + 1);
			if (x - 1 >= 0)
				FloodUncover(x - 1, y);
			//diagonals
			if (y - 1 >= 0 && x + 1 < m_cells->GetColumns()) //top right
				FloodUncover(x + 1, y - 1);
			if (x + 1 < m_cells->GetColumns() && y + 1 < m_cells->GetRows()) //bottom right
				FloodUncover(x + 1, y + 1);
			if (y + 1 < m_cells->GetRows() && x - 1 >= 0) // bottom left
				FloodUncover(x - 1, y + 1);
			if (x - 1 >= 0 && y - 1 >= 0) //top left
				FloodUncover(x - 1, y - 1);
		}
	}
}
