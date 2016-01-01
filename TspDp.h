#pragma once
#include "SolutionSet.h"
#include "Map.h"
#include "Solution.h"
/*
Miko³aj Styœ, 209773
Reprezentuje klasê rozwi¹zauj¹c¹ problem komiwoja¿era metod¹ Dynamic Programming
*/
class TspDp
{
private:
	Map* map;
	SolutionSet* solutions;
	static bool isLoaded(SolutionSet::Solution* solution);
	void loadKnownSolutions() const;
	static bool isSet(uinteger vertex_map, ubyte vertex);
	Solution* getSolution(ubyte vertex) const;
	float load(uinteger vertexMap, ubyte vertex) const;
	uinteger finalSolutionIndex() const;
	Solution* loadFinal() const;
public:
	TspDp(Map* map);
	~TspDp(void);
	Solution* solve() const;
};