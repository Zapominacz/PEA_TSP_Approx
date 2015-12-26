#pragma once
#include <iostream>

class Solution
{
public:
	float cost;
	unsigned* order;
	unsigned size;

	Solution(): Solution(0)
	{
	}

	Solution(unsigned size): cost(0), size(size)
	{
		order = new unsigned[size];
	}

	~Solution()
	{
		if (order != nullptr)
		{
			delete order;
			order = nullptr;
		}
	}
};

