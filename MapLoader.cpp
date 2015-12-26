#pragma once
#include "MapLoader.h"
#include <iostream>
#include <fstream>

void MapLoader::cleanUp()
{
	if (lastLoaded != nullptr)
	{
		delete lastLoaded;
		lastLoaded = nullptr;
	}
}

MapLoader::MapLoader()
{
	lastLoaded = nullptr;
}

MapLoader::~MapLoader()
{
	cleanUp();
}

Map* MapLoader::load()
{
	using namespace std;
	char path[240];
	cout << "Podaj sciezke:" << endl;
	cin >> path;
	return load(path);
}

Map* MapLoader::load(char* path)
{
	using namespace std;
	ifstream file;
	file.open(path);

	if (file.is_open())
	{
		unsigned size = 0;
		file >> size;
		cleanUp();
		lastLoaded = new Map(size);
		for (unsigned row = 0; row < size; row++)
		{
			for (unsigned col = 0; col < size; col++)
			{
				float weight = -1;
				file >> weight;
				if (weight >= 0)
				{
					lastLoaded->matrix[row][col] = weight;
				}
			}
		}
		file.close();
	}
	else cout << "Nie moge otworzyc pliku!";
	return lastLoaded;
}

Map* MapLoader::getLastLoaded() const
{
	return lastLoaded;
}

