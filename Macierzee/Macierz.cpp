#include "stdafx.h"
#include "Macierz.h"




Macierz::Macierz(int rowCount, int colCount)
	:_rowCount(rowCount), _colCount(colCount)
{
	_M = new double *[_rowCount];
	for (int i = 0; i < _rowCount; i++)
	{
		_M[i] = new double[_colCount];
		srand(time(NULL));
		for (int j = 0; j < colCount; j++)
		{
			_M[i][j] = rand() % 10;
		}
	}
}

Macierz::Macierz(const Macierz & other)
	:_rowCount(other._rowCount), _colCount(other._colCount)
{
	_M = new double*[_rowCount];

	for (int i = 0; i < _rowCount; i++)
	{
		_M[i] = new double[_colCount];
		for (int j = 0; j < _colCount; j++)
		{
			_M[i][j] = other._M[i][j];
		}
	}
}

Macierz::~Macierz()
{
	if (_M != NULL)
	{
		for (int i = 0; i < _rowCount; i++)
		{
			delete[] _M[i];
		}

		delete[] _M;
		_M = NULL;
	}
}

Macierz Macierz::operator=(const Macierz & other)
{
	this->~Macierz();
	_rowCount = other._rowCount;
	_colCount = other._colCount;

	_M = new double*[_rowCount];
	for (int i = 0; i < _rowCount; i++)
	{
		_M[i] = new double[_colCount];
		for (int j = 0; j < _colCount; j++)
		{
			_M[i][j] = other._M[i][j];
		}
	}

	return *this;
}



Macierz Macierz::operator=(double value)
{
	for (int i = 0; i < _rowCount; i++)
	{
		for (int j = 0; j < _colCount; j++)
		{
			_M[i][j] = value;
		}
	}
	return *this;
}

Macierz Macierz::operator+(const Macierz & other)
{
	if (_rowCount == other._rowCount && _colCount == other._colCount)
	{
		Macierz result = *this;

		for (int i = 0; i < _rowCount; i++)
		{
			for (int j = 0; j < _colCount; j++)
			{
				result._M[i][j] += other._M[i][j];
			}
		}
		return result;
	}

	else
	{
		throw "Rozmiar macierzy nie jest jednakowa";
	}

}

Macierz Macierz::operator-(const Macierz & other)
{
	if (_rowCount == other._rowCount && _colCount == other._colCount)
	{
		Macierz result(*this);

		for (int i = 0; i < _rowCount; i++)
			for (int j = 0; j < _colCount; j++)
			{
				result._M[i][j] -= other._M[i][i];
			}
		return result;

	}
	else
	{
		throw "Rozmiar macierzy nie sa jednakowe";
	}
		
	
}

Macierz Macierz::operator*(double value)
{
	for (int i = 0; i < _rowCount; i++)
		for (int j = 0; j < _colCount; j++)
			_M[i][j] *= value;

	

	return *this;
}

Macierz Macierz::operator*(const Macierz & other)
{
	if (this->_colCount == other._rowCount)
	{
		Macierz result(this->_rowCount, other._colCount );



		for (int i = 0; i < result._rowCount; i++)
		{

			for (int j = 0; j < result._colCount; j++)
			{
				result._M[i][j] = 0;

				for (int k = 0; k < other._rowCount; k++)
					result._M[i][j] += _M[i][k] * other._M[k][j];

			}

			
		}
		
		return result;
	}
}

Macierz Macierz::operator()(string)
{
	return Macierz();
}

double Macierz::operator~()		//wyznacznik macierzy
{
	if (_rowCount == _colCount)
	{
		double det = 1;
		Macierz result = *this;

		for (int i = 0; i < _rowCount - 1; i++)
			for (int j = i + 1; j < _rowCount; j++)
				for (int k = i + 1; k < _rowCount; k++)
					result._M[j][k] -= result._M[j][i] / result._M[i][i] * result._M[i][k];

		for (int i = 0; i < _rowCount; i++)
			det *= result._M[i][i];

		Macierz other(1, 1);
		other = det;
		

		return det;
	}
}

Macierz Macierz::operator!()
{
	if (_rowCount && _colCount == 2)
	{
		Macierz dopelnien(_rowCount, _colCount);
		Macierz other = *this;
		
		for (int i = 0, l = _rowCount; i < _rowCount; i++, l--)
			for (int j = 0, k = _colCount; j < _colCount; j++, k--)
			{
				dopelnien._M[i][j] = pow(-1, i + j) * _M[l - 1][k - 1];
			}

		&dopelnien;
		double det = ~*this;
		for (int i = 0; i < dopelnien._rowCount; i++)
			for (int j = 0; j < dopelnien._colCount; j++)
			{
				_M[i][j] = dopelnien._M[i][j] / det;
			}

		return *this;
	}

}

Macierz Macierz::operator&()					//transponowanie macierzy;
{
	Macierz result(_colCount, _rowCount);
	
	for (int i = 0; i < result._rowCount; i++)
		for (int j = 0; j < result._colCount; j++)
			result._M[j][i] = _M[i][j];
	return result;
}



Macierz Macierz::operator++()
 {
	for(int i = 0; i < _rowCount; i++)
		for (int j = 0; j < _colCount; j++)
		{
			_M[i][j]++;
		}
	return *this;
}

Macierz Macierz::operator++(int)
{
	Macierz oldValue(*this);
	
	for(int i = 0; i < _rowCount; i++)
		for (int j = 0; j < _rowCount; j++)
		{
			_M[i][j]++;
		}
	return oldValue;
}




Macierz operator*(const Macierz & other)
{
	return Macierz();
}

ostream & operator<<(ostream & out, const Macierz & other)
{
	for (int i = 0; i < other._rowCount; i++)
	{
		for (int j = 0; j < other._colCount; j++)
		{
			
			
			out << other._M[i][j] << " ";
		}

		cout << endl;
	}

	return out;
	// TODO: tu wstawiæ instrukcjê return
}

istream & operator>>(istream & in, const Macierz & other)
{
	for(int i = 0; i < other._rowCount;i++)
		for (int j = 0; j < other._colCount; j++)
		{
			in >> other._M[i][j];
		}
	return in;
	// TODO: tu wstawiæ instrukcjê return
}
