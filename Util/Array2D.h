#pragma once

template<class T> class Array2D
{
public:
	Array2D() :m_array(0) {}
	~Array2D() { delete[] m_array; m_array = 0; }

	void setSize(int _x, int _y)
	{
		if(m_array) { delete[] m_array; m_array = 0; }
		x = _x;
		y = _y;
		m_array = new T[_x * _y];
	}
	T& operator()(int _x, int _y) { return m_array[_y * x + _x]; }
	const T& operator()(int _x, int _y) const { return m_array[_y * x + _x]; }

private:
	T* m_array;
	int x;
	int y;
};