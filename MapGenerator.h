#pragma once
#include "Map.h"
#include "Point.h"

/*
Miko³aj Styœ, 209773
Generator intancji symetrycznego problemu komiwoja¿era, w którym krawêdzie spe³niaj¹
nierównoœæ trójk¹ta
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