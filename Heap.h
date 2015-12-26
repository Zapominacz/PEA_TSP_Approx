#pragma once
#include <queue>
#include <vector>

class Heap
{
private:
	static bool cmp(const pair<float, unsigned>& lhs, const pair<float, unsigned>& rhs) {
		return lhs.first > rhs.first;
	}
	vector<pair<float, unsigned>>* values;
public:

	Heap()
	{
		values = new vector<pair<float, unsigned>>();
		make_heap(values->begin(), values->end(), cmp);
	}

	~Heap(void)
	{
		delete values;
	}

	void push(float key, unsigned value) const
	{
		values->push_back({ key, value });
		push_heap(values->begin(), values->end(), cmp);
	}

	bool isEmpty() const
	{
		return values->empty();
	}

	unsigned pop() const
	{
		pop_heap(values->begin(), values->end(), cmp);
		auto result = values->back().second;
		values->pop_back();
		return result;
	}

	float getKey(unsigned value) const
	{
		float result = FP_NAN;
		for (auto it = values->begin(); it != values->end(); ++it)
		{
			if(it->second == value)
			{
				result = it->first;
				break;
			}
		}
		return result;
	}

	void setKey(float key, unsigned value) const
	{
		for (auto it = values->begin(); it != values->end(); ++it)
		{
			if (it->second == value)
			{
				it->first = key;
				break;
			}
		}
		make_heap(values->begin(), values->end(), cmp);
	}
};

