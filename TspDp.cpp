#pragma once
#include "TspDp.h"

inline bool TspDp::isLoaded(SolutionSet::Solution* solution)
{
	return solution->value != Map::INF();
}

TspDp::TspDp(Map* map)
{
	this->map = map;
	solutions = new SolutionSet(map->size);
}

TspDp::~TspDp(void)
{
	delete solutions;
	solutions = nullptr;
}

void TspDp::loadKnownSolutions() const 
//£aduje znane rozwiazania, czyli zbiory jednoelementowe
{
	uinteger set = 0x00000001;
	SolutionSet::Solution* solution;
	for (ubyte vertex = 1; vertex < map->size; vertex++)
	{
		solution = solutions->getSolution(set, vertex);
		solution->value = map->matrix[0][vertex];
		solution->lastVertex = 0;
		set = set << 1;
	}
}

inline bool TspDp::isSet(uinteger vertexMap, ubyte vertex) //czy bit jest ustawiony - do odczytu zawartosci zbioru
{
	return !(!(vertexMap & (1 << (vertex - 1))));
}

Solution* TspDp::getSolution(ubyte vertex) const
//ostatni wierzcho³ek
//backtracking do znalezienia kolejnoœci wierzcho³ków
{
	Solution* result = new Solution(map->size); //tworze tablice rozwi¹zañ
	uinteger currentSet = finalSolutionIndex();
	SolutionSet::Solution* solution;
	for (ubyte city = map->size - 1; city > 0; city--)
	{
		result->order[city] = static_cast<unsigned>(vertex); //zapisuje wierzcho³ek
		solution = solutions->getSolution(currentSet, vertex);
		//szukam podrozwi¹zania
		currentSet ^= (1 << (vertex - 1));
		//usuwam wierzcho³ek do znalezienia podrzêdnego zbioru
		vertex = solution->lastVertex;
		//dodaje nowy wierzcho³ek
	}
	result->order[0] = 0; //wierzcho³ek z którego zaczynamy
	for (unsigned v = 1; v < result->size; ++v)
	{
		result->cost += map->matrix[result->order[v - 1]][result->order[v]];
	}
	result->cost += map->matrix[result->order[result->size - 1]][0];
	return result;
}

//pomocnicza funkcja do obliczania zbioru pe³nego
inline uinteger TspDp::finalSolutionIndex() const
{
	return ((1 << (map->size - 1)) - 1);
}

//wylicza rozwi¹zanie, leniwie rozwi¹zauj¹c podrozwi¹zania
Solution* TspDp::loadFinal() const
{
	uinteger fullSet = finalSolutionIndex();
	ubyte bestVertex = SolutionSet::V_INF;
	float bestCost = Map::INF();
	for (ubyte vertex = 1; vertex < map->size; vertex++)
	{
		//do wszystkich rozwi¹zañ maj¹cych wszystkie wierzcho³ki
		//dodaje krawêdŸ tworz¹c¹ cykl
		float cost = load(fullSet, vertex) + map->matrix[vertex][0];
		//szukam najlepszego
		if (bestCost > cost)
		{
			bestVertex = vertex;
			bestCost = cost;
		}
	}
	//wyliczam rozwi¹zanie (etap 4)
	return getSolution(bestVertex);
}

Solution* TspDp::solve() const
{
	loadKnownSolutions();
	return loadFinal();
}

//Leniwie ³aduje rozwi¹zania, czyli je¿eli nie zosta³o jeszcze utworzone - tworzy
float TspDp::load(uinteger vertexMap, ubyte endVertex) const
{
	//pobieranie rozwi¹zania
	SolutionSet::Solution* solution = solutions->getSolution(vertexMap, endVertex);
	if(!isLoaded(solution)) //sprawdzem, czy muszê je utworzyæ
	{
		ubyte bestVertex = SolutionSet::V_INF;
		float bestCost = Map::INF();
		vertexMap = vertexMap ^ (1 << (endVertex - 1)); 
		//zgodnie z algorytmem Held'a-Karp'a jest to podzbiór bez tego wierzcho³ka
		for (ubyte startVertex = 1; startVertex < map->size; startVertex++)
		{
			if(isSet(vertexMap, startVertex))
			{
				//pobieram wartoœci podrozwi¹zañ (tak¿e je ³aduj¹c, jezli trzeba)
				float cost = load(vertexMap, startVertex) 
					+ map->matrix[startVertex][endVertex];
				//szukam najlepszego z doadtkow¹ krawêdzi¹ tworz¹c¹ ten zbiór
				if (bestCost > cost)
				{
					bestVertex = startVertex;
					bestCost = cost;
				}
			}
		}
		//zapisuje najlepszy wynik jak wartoœæ danego rozwi¹zania
		solution->lastVertex = bestVertex;
		solution->value = bestCost;
	}
	return solution->value;
}
