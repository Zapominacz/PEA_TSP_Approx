#pragma once
#include <iostream>

/*
Miko³aj Styœ, 209773
Reprezentuje mapê miast z wagami przejœæ
*/

float INF = std::numeric_limits<float>::infinity();
unsigned NO_VERTEX = std::numeric_limits<unsigned>::max();
float DELTA = 0.00001; //ró¿nica przy której zak³adamy, ¿e liczby s¹ równe

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

