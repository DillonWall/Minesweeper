/*************************************************************
* Author: Dillon Wall
* Filename: Array2D.h
* Date Created: 1/19/2019
* Modifications:
**************************************************************/

#pragma once

#include "Array.h"
#include "Row.h"


/************************************************************************
* Class: Array2D
*
* Purpose: This class is a dynamic 2D array that uses an Array object to hold data
*
* Manager functions:
* Array2D()
*		Creates default Array2D with default array and 0 rows, 0 columns
* Array2D(int rows, int cols)
*		Creates an Array2D with a specified amount of rows and columns
* Array2D(const Array2D& other)
* Array2D<T>& operator=(const Array2D& other)
* ~Array2D()
* Row<T> operator[](int index)
*		Get an element from the array
* const Row<T> operator[](int index) const
*		Get an element from a const array
*
* Methods:
* int GetRows() const
* void SetRows(int rows)
* int GetColumns() const
* void SetColumns(int columns)
* T& Select(int row, int column)
*		Returns an element from the Array based on what row and column
*
*
*
*************************************************************************/
template <typename T>
class Array2D
{
public:
	Array2D();
	Array2D(int rows, int cols);
	Array2D(const Array2D<T>& copy);
	~Array2D();
	Array2D<T>& operator=(const Array2D<T>& rhs);
	Row<T> operator[](int index);
	const Row<T> operator[](int index) const;

	int GetRows() const;
	void SetRows(int rows);
	int GetColumns() const;
	void SetColumns(int columns);
	T& Select(int row, int column);

private:
	friend class Row<T>;

	Array<T> m_array;
	int m_rows;
	int m_cols;
};

/// Source Code ///

template<typename T>
inline Array2D<T>::Array2D() : m_array(), m_rows(0), m_cols(0)
{
}

template<typename T>
inline Array2D<T>::Array2D(int rows, int cols) : m_array(), m_rows(rows), m_cols(cols)
{
	if (rows < 0 || cols < 0) throw Exception("Cannot instantiate array with negative bounds");

	m_array = Array<T>(rows * cols);
}

template<typename T>
inline Array2D<T>::Array2D(const Array2D<T> & copy) : m_array(copy.m_array), m_rows(copy.m_rows), m_cols(copy.m_cols)
{
}

template<typename T>
inline Array2D<T>::~Array2D()
{
	m_array = Array<T>();
	m_rows = 0;
	m_cols = 0;
}

template<typename T>
inline Array2D<T> & Array2D<T>::operator=(const Array2D<T> & rhs)
{
	if (this != &rhs)
	{
		m_array = rhs.m_array;
		m_rows = rhs.m_rows;
		m_cols = rhs.m_cols;
	}

	return *this;
}

template<typename T>
inline Row<T> Array2D<T>::operator[](int index)
{
	if (index < 0 || index > m_rows - 1) throw Exception("Row index out of bounds");

	return Row<T>(*this, index);
}

template<typename T>
inline const Row<T> Array2D<T>::operator[](int index) const
{
	if (index < 0 || index > m_rows - 1) throw Exception("Row index out of bounds");

	return Row<T>(const_cast<Array2D<T>&>(*this), index);
}

template<typename T>
inline int Array2D<T>::GetRows() const
{
	return m_rows;
}

template<typename T>
inline void Array2D<T>::SetRows(int rows)
{
	if (rows < 0) throw Exception("Cannot set rows negative");

	m_array.SetLength(rows * m_cols);
	m_rows = rows;
}

template<typename T>
inline int Array2D<T>::GetColumns() const
{
	return m_cols;
}

template<typename T>
inline void Array2D<T>::SetColumns(int columns) //need to put space between data to perserve original structure, or delete specific data
{
	if (columns < 0) throw Exception("Cannot set columns negative");
	Array<T> oldArr(m_array);
	m_array.SetLength(m_rows * columns);
	for (int i = 0; i < m_rows; ++i)
	{
		for (int j = 0; j < m_cols; ++j)
		{
			if (columns > j) //dont copy this data if it should be cut off
			{
				m_array[(i * columns) + j] = oldArr[(i * m_cols) + j];
			}
		}
	}
	m_cols = columns;
}

template<typename T>
inline T & Array2D<T>::Select(int row, int column)
{
	if (row < 0 || row > m_rows - 1 || column < 0 || column > m_cols - 1) throw Exception("Select index out of bounds");

	return m_array[(row * m_cols) + column];
}