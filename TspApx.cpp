#pragma once
#include "TspApx.h"
#include "Heap.h"
#include <stack>
#include <filesystem>

TspApx::TspApx(Map* map)
{
	baseMap = map;
	adjacencyMap = new AdjacencyMap(map->size);
	eulerianCircuit = new vector<unsigned>();
	solution = new Solution(map->size);
};

TspApx::~TspApx(void)
{
	if (adjacencyMap != nullptr)
	{
		delete adjacencyMap;
		adjacencyMap = nullptr;
	}
	if (eulerianCircuit != nullptr)
	{
		delete eulerianCircuit;
		eulerianCircuit = nullptr;
	}
}

Solution* TspApx::solve() const
{
	createPrimsMst();
	greedyPerfectMatching();
	findEulerianCycle();
	removeVisitedVertexes();
	return solution;
};

void TspApx::createPrimsMst() const
{
	const auto size = baseMap->size;
	auto heap = Heap();
	auto included = new bool[size];
	auto parent = new unsigned[size];
	auto cost = new float[size];
	parent[0] = Map::NO_VERTEX();
	heap.push(0, 0);
	for (unsigned vertex = 1; vertex < size; vertex++)
	{
		heap.push(Map::INF(), vertex);
		parent[vertex] = Map::NO_VERTEX();
		included[vertex] = false;
	}
	while (!heap.isEmpty())
	{
		auto v1 = heap.pop();
		included[v1] = true;
		for (unsigned v2 = 0; v2 < size; ++v2)
		{
			auto weight = baseMap->matrix[v1][v2];
			if (!included[v2] && weight < heap.getKey(v2))
			{
				heap.setKey(weight, v2);
				parent[v2] = v1;
				cost[v2] = weight;
			}
		}
	}
	for (unsigned v1 = 0; v1 < size; v1++)
	{
		auto v2 = parent[v1];
		if (v2 != Map::NO_VERTEX())
		{
			adjacencyMap->addSymmetric(v1, v2);
		}
	}
	delete[] included;
	delete[] cost;
	delete[] parent;
};

vector<unsigned>* TspApx::findOddDegreeVertexes() const
{
	auto result = new vector<unsigned>();
	for (unsigned vertex = 0; vertex < baseMap->size; ++vertex)
	{
		if (adjacencyMap->getFor(vertex)->size() % 2 != 0)
		{
			result->push_back(vertex);
		}
	}
	return result;
}

void TspApx::greedyPerfectMatching() const
{
	auto oddVertexes = findOddDegreeVertexes();
	while (!oddVertexes->empty())
	{
		unsigned closest = FP_NAN;
		vector<unsigned>::iterator best;
		auto first = oddVertexes->front();
		float cost = FLT_MAX;
		for (auto it = oddVertexes->begin() + 1; it != oddVertexes->end(); ++it)
		{
			if (baseMap->matrix[first][*it] < cost)
			{
				cost = baseMap->matrix[first][*it];
				closest = *it;
				best = it;
			}
		}
		//Od razu dodawane do ścieżki
		adjacencyMap->addSymmetric(closest, first);
		oddVertexes->erase(best);
		oddVertexes->erase(oddVertexes->begin());
	}
	delete oddVertexes;
}

void TspApx::findEulerianCycle() const
{
	unsigned currentVertex = 0;
	auto vertexStack = new stack<unsigned>();
	while (!vertexStack->empty() || !adjacencyMap->getFor(currentVertex)->empty())
	{
		if (adjacencyMap->getFor(currentVertex)->empty())
		{
			eulerianCircuit->push_back(currentVertex);
			currentVertex = vertexStack->top();
			vertexStack->pop();
		}
		else
		{
			vertexStack->push(currentVertex);
			auto neighbour = adjacencyMap->getFor(currentVertex)->back();
			adjacencyMap->removeSymmetric(neighbour, currentVertex);
			currentVertex = neighbour;
		}
	}
	delete vertexStack;
}


void TspApx::removeVisitedVertexes() const
{
	const auto size = baseMap->size;
	auto visited = new bool[size];
	for (auto v = 0; v < size; v++)
	{
		visited[v] = false;
	}
	unsigned solutionIndex = 1;
	visited[*eulerianCircuit->begin()] = true;
	solution->order[0] = *eulerianCircuit->begin();
	for (auto it = eulerianCircuit->begin() + 1; it != eulerianCircuit->end(); ++it)
	{
		auto vertex = *it;
		if (!visited[vertex])
		{
			solution->order[solutionIndex] = vertex;
			solution->cost +=
				baseMap->matrix[solution->order[solutionIndex - 1]]
				[vertex];
			visited[vertex] = true;
			++solutionIndex;
		}
	}
	solution->cost += baseMap->matrix[solution->order[solution->size - 1]][0];
	delete visited;
}

