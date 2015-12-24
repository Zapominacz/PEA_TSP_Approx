#pragma once
#include "Map.h"
#include "Point.h"

/*
Miko�aj Sty�, 209773
Generator intancji symetrycznego problemu komiwoja�era, w kt�rym kraw�dzie spe�niaj�
nier�wno�� tr�jk�ta
*/
class MapGenerator
{
private:
	Map* lastGenerated;
	Point* vertexPositions;
	const unsigned MAX_SIZE = 100;
	void cleanUp();
	bool isUniquePosition(Point* point, unsigned size);
	void computePositions(unsigned size);
	void computeLengths(unsigned size);
	float distance(Point* point1, Point* point2) const;
public:
	MapGenerator(void);
	~MapGenerator(void);
	Map* generate(unsigned size);
	Map* getLastGenerated();
};