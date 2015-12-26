#pragma once

#include <queue>

#include "Solution.h"
#include "AdjacencyMap.h"

using namespace std;

class TspApx
{
private:
	Map* baseMap;
	AdjacencyMap* adjacencyMap;
	vector<unsigned>* eulerianCircuit;
	Solution* solution;

	vector<unsigned>* findOddDegreeVertexes() const;
	void createPrimsMst() const;
	void greedyPerfectMatching() const;
	void findEulerianCycle() const;
	void removeVisitedVertexes() const;
public:
	TspApx(Map* map);
	~TspApx(void);
	Solution* solve() const;
};

