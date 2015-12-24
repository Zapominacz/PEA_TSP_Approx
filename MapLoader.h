#pragma once
#include "Map.h"
/*
Miko�aj Sty�, 209773
�aduje z pliku instancje problemu
*/
class MapLoader
{
private:
	Map* lastLoaded;
	void cleanUp();
public:
	MapLoader(void);
	~MapLoader(void);
	Map* load();
	Map* getLastLoaded();
};