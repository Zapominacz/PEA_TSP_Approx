#pragma once
#include "Map.h"
#include <vector>

using namespace std;

class AdjacencyMap
{
private:
	vector<unsigned>* lists;
	unsigned size;
public:

	vector<unsigned>* getFor(int vertex) const
	{
		return &lists[vertex];
	}

	~AdjacencyMap(void)
	{
		if (lists != nullptr)
		{
			delete[] lists;
			lists = nullptr;
		}
	}

	AdjacencyMap(unsigned size)
	{
		this->size = size;
		lists = new vector<unsigned>[size];
	}


	void addSymmetric(unsigned v1, unsigned v2) const
	{
		lists[v1].push_back(v2);
		lists[v2].push_back(v1);
	}

	void removeSymmetric(unsigned v1, unsigned v2) const
	{
		lists[v1].erase(find(lists[v1].begin(), lists[v1].end(), v2));
		lists[v2].erase(find(lists[v2].begin(), lists[v2].end(), v1));
	}
};

