#pragma once
#include "Map.h"

/*
Miko³aj Styœ, 209773
£aduje z pliku instancje problemu
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
	Map* load(char *path);
	Map* getLastLoaded() const;
};

