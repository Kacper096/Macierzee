#pragma once
#include <iostream>
#include <time.h>

using namespace std;

class Macierz
{
	int _colCount, _rowCount;
	double ** _M;
	
public:

	Macierz(int rowCount = 3, int colCount = 4);
	Macierz(const Macierz &other);
	~Macierz();

	Macierz operator=(const Macierz & other);
	Macierz operator=(double value);

	Macierz operator+(const Macierz & other);		//dodawanie macierzy
	Macierz operator-(const Macierz & other);		//odejmowanie macierzy

	Macierz operator*(double value);				//mnozenie mac. przez liczbe
	Macierz operator*(const Macierz & other);		//mnozenie macierzy

	Macierz operator()(string);

double operator~();					//wyznacznik macierzy
	

	Macierz operator!();					//macierz odwrotna 2x2

	Macierz operator&();					//transponownie macierzy

	
	Macierz operator++();
	Macierz operator++(int);
	
	friend ostream & operator<< (ostream & out, const Macierz & other);
	friend istream & operator>> (istream & in, const Macierz & other);


};

