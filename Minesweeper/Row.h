/*************************************************************
* Author: Dillon Wall
* Filename: Row.h
* Date Created: 1/19/2019
* Modifications:
**************************************************************/

#pragma once

#include "Exception.h"

template <typename T>
class Array2D;

/************************************************************************
* Class: Row
*
* Purpose: This class is a helper class to signify a row in a 2D array
*
* Manager functions:
* Row(Array2D<T>& arr, int row)
*		Creates a Row with the specified position from the specified Array2D
* T& operator[](int column);
*		Returns the object from this row at the specified column
* const T& operator[](int column) const;
*		Returns a const version of the object from this row at the specified column.
*		This is only used with a const Array2D
*
* Methods:
*
*************************************************************************/
template <typename T>
class Row
{
public:
	Row(Array2D<T>& arr, int row);
	T& operator[](int column);
	const T& operator[](int column) const;

private:
	Array2D<T>& m_array2D;
	int m_row;
};

/// Source Code ///

template<typename T>
inline Row<T>::Row(Array2D<T> & arr, int row) : m_array2D(arr), m_row(row)
{
}

template<typename T>
inline T & Row<T>::operator[](int column)
{
	if (column < 0 || column > m_array2D.m_cols - 1) throw Exception("Column index out of bounds");
	return m_array2D.m_array[(m_row * m_array2D.m_cols) + column];
}

template<typename T>
inline const T& Row<T>::operator[](int column) const
{
	if (column < 0 || column > m_array2D.m_cols - 1) throw Exception("Column index out of bounds");
	return m_array2D.m_array[(m_row * m_array2D.m_cols) + column];
}
