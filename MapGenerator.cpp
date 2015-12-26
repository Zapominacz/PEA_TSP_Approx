#pragma once
#include "MapGenerator.h"
#include <random>

void MapGenerator::cleanUp()
{
	if (lastGenerated != nullptr)
	{
		delete lastGenerated;
		lastGenerated = nullptr;
	}
	if (vertexPositions != nullptr)
	{
		delete vertexPositions;
		vertexPositions = nullptr;
	}
}

bool MapGenerator::isUniquePosition(Point* point, unsigned size) const
{
	for (unsigned i = 0; i < size; ++i)
	{
		if (abs(vertexPositions[i].x - point->x) < Map::DELTA() && abs(vertexPositions[i].y - point->y) < Map::DELTA())
		{
			return false;
		}
	}
	return true;
}

void MapGenerator::computePositions(unsigned size)
{
	using namespace std;
	default_random_engine generator;
	float maxPos = MAX_SIZE / sqrt(2.0f); // odleg³oœæ nie przekroczy MAX_SIZE
	uniform_real_distribution<float> distribution(0, maxPos);
	vertexPositions = new Point[size];
	for (unsigned vertex = 0; vertex < size; vertex++)
	{
		Point* point = &vertexPositions[vertex];
		do
		{
			point->x = distribution(generator);
			point->y = distribution(generator);
		}
		while (isUniquePosition(point, size));
	}
}

void MapGenerator::computeLengths(unsigned size) const
{
	for (unsigned row = 0; row < size; ++row)
	{
		for (unsigned col = 0; col < size; ++col)
		{
			if (row != col)
			{
				lastGenerated->matrix[row][col] = distance(vertexPositions + row, vertexPositions + col);
			}
		}
	}
}

float inline MapGenerator::distance(Point* point1, Point* point2) const
{
	return sqrt(pow(point1->x + point2->x, 2) + pow(point1->y + point2->y, 2));
}

MapGenerator::MapGenerator()
{
	lastGenerated = nullptr;
	vertexPositions = nullptr;
}

MapGenerator::~MapGenerator()
{
	cleanUp();
}

Map* MapGenerator::generate(unsigned size)
{
	using namespace std;
	cleanUp();
	lastGenerated = new Map(size);
	computePositions(size);
	computeLengths(size);
	return lastGenerated;
}

Map* MapGenerator::getLastGenerated() const
{
	return lastGenerated;
}

