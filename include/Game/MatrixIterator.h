#pragma once

#include <vector>

template<typename T>
class MatrixIterator {
	MatrixIterator(std::vector<std::vector<T>>& matrix)
		:m_mat(matrix), m_it1(matrix.begin()), m_it2(m_it1->begin()) {}
	T* operator*();

private:
	std::vector<std::vector<T>>& m_mat;
	std::vector<std::vector<T>>::iterator m_it1;
	std::vector<std::vector<T>>::iterator m_it2;
	int m_i = 0;
	//T* m_pointer;
};

template<typename T>
T* MatrixIterator<T>::operator*()
{
	if (m_it1 == m_mat.end())
		//TODO: throw;
		break;
	else
	{
		if (m_it2 == m_mat[m_i].end())
		{

		}
	}
	return *m_it2;
}
