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
//�aduje znane rozwiazania, czyli zbiory jednoelementowe
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
//ostatni wierzcho�ek
//backtracking do znalezienia kolejno�ci wierzcho�k�w
{
	Solution* result = new Solution(map->size); //tworze tablice rozwi�za�
	uinteger currentSet = finalSolutionIndex();
	SolutionSet::Solution* solution;
	for (ubyte city = map->size - 1; city > 0; city--)
	{
		result->order[city] = static_cast<unsigned>(vertex); //zapisuje wierzcho�ek
		solution = solutions->getSolution(currentSet, vertex);
		//szukam podrozwi�zania
		currentSet ^= (1 << (vertex - 1));
		//usuwam wierzcho�ek do znalezienia podrz�dnego zbioru
		vertex = solution->lastVertex;
		//dodaje nowy wierzcho�ek
	}
	result->order[0] = 0; //wierzcho�ek z kt�rego zaczynamy
	for (unsigned v = 1; v < result->size; ++v)
	{
		result->cost += map->matrix[result->order[v - 1]][result->order[v]];
	}
	result->cost += map->matrix[result->order[result->size - 1]][0];
	return result;
}

//pomocnicza funkcja do obliczania zbioru pe�nego
inline uinteger TspDp::finalSolutionIndex() const
{
	return ((1 << (map->size - 1)) - 1);
}

//wylicza rozwi�zanie, leniwie rozwi�zauj�c podrozwi�zania
Solution* TspDp::loadFinal() const
{
	uinteger fullSet = finalSolutionIndex();
	ubyte bestVertex = SolutionSet::V_INF;
	float bestCost = Map::INF();
	for (ubyte vertex = 1; vertex < map->size; vertex++)
	{
		//do wszystkich rozwi�za� maj�cych wszystkie wierzcho�ki
		//dodaje kraw�d� tworz�c� cykl
		float cost = load(fullSet, vertex) + map->matrix[vertex][0];
		//szukam najlepszego
		if (bestCost > cost)
		{
			bestVertex = vertex;
			bestCost = cost;
		}
	}
	//wyliczam rozwi�zanie (etap 4)
	return getSolution(bestVertex);
}

Solution* TspDp::solve() const
{
	loadKnownSolutions();
	return loadFinal();
}

//Leniwie �aduje rozwi�zania, czyli je�eli nie zosta�o jeszcze utworzone - tworzy
float TspDp::load(uinteger vertexMap, ubyte endVertex) const
{
	//pobieranie rozwi�zania
	SolutionSet::Solution* solution = solutions->getSolution(vertexMap, endVertex);
	if(!isLoaded(solution)) //sprawdzem, czy musz� je utworzy�
	{
		ubyte bestVertex = SolutionSet::V_INF;
		float bestCost = Map::INF();
		vertexMap = vertexMap ^ (1 << (endVertex - 1)); 
		//zgodnie z algorytmem Held'a-Karp'a jest to podzbi�r bez tego wierzcho�ka
		for (ubyte startVertex = 1; startVertex < map->size; startVertex++)
		{
			if(isSet(vertexMap, startVertex))
			{
				//pobieram warto�ci podrozwi�za� (tak�e je �aduj�c, jezli trzeba)
				float cost = load(vertexMap, startVertex) 
					+ map->matrix[startVertex][endVertex];
				//szukam najlepszego z doadtkow� kraw�dzi� tworz�c� ten zbi�r
				if (bestCost > cost)
				{
					bestVertex = startVertex;
					bestCost = cost;
				}
			}
		}
		//zapisuje najlepszy wynik jak warto�� danego rozwi�zania
		solution->lastVertex = bestVertex;
		solution->value = bestCost;
	}
	return solution->value;
}
