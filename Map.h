#pragma once
#include <iostream>

/*
Miko�aj Sty�, 209773
Reprezentuje map� miast z wagami przej��
*/

float INF = std::numeric_limits<float>::infinity();
unsigned NO_VERTEX = std::numeric_limits<unsigned>::max();
float DELTA = 0.00001; //r�nica przy kt�rej zak�adamy, �e liczby s� r�wne

class Map
{
public:
	unsigned size;
	float** matrix;

	Map(unsigned size)
	{
		this->size = size;
		matrix = new float*[size];
		for (unsigned row = 0; row < size; row++)
		{
			matrix[row] = new float[size];
			for (unsigned col = 0; col < size; col++)
			{
				matrix[row][col] = INF;
			}
		}
	}

	Map(unsigned size, float**matrix)
	{
		this->size = size;
		this->matrix = matrix;
	}

	~Map(void)
	{
		for (unsigned row = 0; row < size; row++)
		{
			delete[] matrix[row];
		}
		delete[] matrix;
	}

};

