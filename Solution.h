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
		if(order != nullptr)
		{
			delete order;
			order = nullptr;
		}
	}

	friend std::ostream& operator<< (std::ostream & out, Solution const& data) {
		for (auto i = 0; i < data.size; ++i) {
			out << data.order[data.size] << " ";
		}
		out << "\nWaga: " << data.cost << std::endl;
		return out;
	}
};