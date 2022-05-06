#pragma once

#include <vector>

template<typename T>
class MatrixIterator {
public:
	MatrixIterator(std::vector<std::vector<T>>& matrix)
		:m_mat(matrix), m_it1(matrix.begin()), m_it2(m_it1->begin()) {}
	T* operator*();
	MatrixIterator operator++();
	MatrixIterator operator++(int);
	bool operator==(const MatrixIterator& other);
	bool operator!=(const MatrixIterator& other);
	bool isEnd();

private:
	std::vector<std::vector<T>>& m_mat;
	std::vector<std::vector<T>>::iterator m_it1;
	std::vector<T>::iterator m_it2;
	int m_i = 0;
};

template<typename T>
inline T* MatrixIterator<T>::operator*()
{
		if (m_it1 == m_mat.end())
			int i = 8; //TODO: throw;
		//if (m_it2 == m_mat[m_i].end()) {
		//	//TODO: throw?;
		//}
	
		return *m_it2;
}

template<typename T>
inline MatrixIterator<T> MatrixIterator<T>::operator++()
{
	if (m_it1 == m_mat.end())
		int i;	//TODO: throw?;		
	if (m_it2 != m_mat[m_i].end()) {
		m_it2++;
		if (m_it2 != m_mat[m_i].end())
			return *this;
	}
	m_i++;
	m_it1++;	//TODO: what if i got end()?
	if (m_it1 == m_mat.end())
		;// return nullptr;
	m_it2 = m_it1->begin();
	return *this;
}

template<typename T>
inline MatrixIterator<T> MatrixIterator<T>::operator++(int)
{
	MatrixIterator res(*this);
	operator++();
	return res;
}


template<typename T>
inline bool MatrixIterator<T>::operator==(const MatrixIterator& other)
{
	return m_it2 == other.m_it2;
}

template<typename T>
inline bool MatrixIterator<T>::operator!=(const MatrixIterator& other)
{
	return !(* this == other);
}

template<typename T>
inline bool MatrixIterator<T>::isEnd()
{
	return m_it1 == m_mat.end();
}
