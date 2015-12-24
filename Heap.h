#pragma once
#include <unordered_map>

class Heap
{
private:
	vector<float>* keys;
	unordered_map<float, unsigned>* values;

	struct minHeap
	{
		bool operator()(const float& a, const float& b) const {
			return a > b;
		}
	};

public:
	Heap()
	{
		keys = new vector<float>();
		values = new unordered_map<float, unsigned>();
	}
	void push(float key, unsigned value)
	{
		keys->push_back(key);
		push_heap(keys->begin(), keys->end(), minHeap());
		values->insert({ key, value });
	}
	bool isEmpty() const
	{
		return keys->empty();
	}


	unsigned pop() const
	{
		auto firstKey = *keys->begin();
		auto result = values->at(firstKey);
		values->erase(firstKey);
		keys->erase(keys->begin());
		pop_heap(keys->begin(), keys->end(), minHeap());
		return result;
	}

	float getKey(unsigned value) const
	{
		for (auto it = values->begin(); it != values->end(); ++it)
		{
			if (it->second == value)
			{
				return it->first;
			}
		}
		return FP_NAN;
	}

	void setKey(float key, unsigned value) const
	{
		auto oldKey = getKey(value);
		auto it = values->find(oldKey);
		if (it != values->end()) {
			it->second = key;
		}
		make_heap(keys->begin(), keys->end(), minHeap());
	}
};
