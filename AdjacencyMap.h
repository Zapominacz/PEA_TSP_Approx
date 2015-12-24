#pragma once
#include "Map.h";
#include <vector>

using namespace std;
class AdjacencyMap
{
private:
	vector<unsigned>** lists;
	unsigned size;
public:

	vector<unsigned>* getFor(int vertex) const
	{
		return lists[vertex];
	}

	AdjacencyMap(Map* map)
	{
		size = map->size;
		lists = new vector<unsigned>*[size];
		for (unsigned v1 = 0; v1 < size; ++v1)
		{
			lists[v1] = new vector<unsigned>;
			for (unsigned v2 = 0; v2 < size; ++v2)
			{
				if(map->matrix[v1][v2] != INF)
				{
					lists[v1]->push_back(v2);
				}
			}
		}
	}

	~AdjacencyMap(void)
	{
		if(lists != nullptr) {
			for (unsigned vertex = 0; vertex < size; ++vertex)
			{
				delete lists[vertex];
			}
			delete[] lists;
			lists = nullptr;
		}
	}

	void addSymmetric(unsigned v1, unsigned v2) const
	{
		getFor(v1)->push_back(v2);
		getFor(v2)->push_back(v1);
	}

	AdjacencyMap(AdjacencyMap* const map)
	{
		size = map->size;
		lists = new vector<unsigned>*[size];
		for (unsigned vertex = 0; vertex < size; ++vertex)
		{
			lists[vertex] = new vector<unsigned>;
			lists[vertex] = map->lists[vertex];
		}
	}
};
