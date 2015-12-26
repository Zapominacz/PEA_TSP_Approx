#pragma once
#include <iostream>

/*
Miko�aj Sty�, 209773
Reprezentuje map� miast z wagami przej��
*/

class Map
{
public:
	static float INF()
	{
		return std::numeric_limits<float>::infinity();
	}

	static unsigned NO_VERTEX()
	{
		return std::numeric_limits<unsigned>::max();
	}

	static float DELTA()
	{ //r�nica przy kt�rej zak�adamy, �e liczby s� r�wne
		return 0.00001f;
	}

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
				matrix[row][col] = INF();
			}
		}
	}

	Map(unsigned size, float** matrix)
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

