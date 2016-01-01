#pragma once
#include <iostream>
#include <bitset>
#include "Map.h"

typedef uint8_t ubyte;
typedef int8_t byte;
typedef int32_t integer;
typedef uint32_t uinteger;
/*
Miko³aj Styœ, 209773
Zbiór w którym zapisywane s¹ poœrednie rozwi¹zania
*/
class SolutionSet
{
public:
	static const ubyte V_INF = UINT8_MAX; //brak wierzcho³ka

	class Solution //rozwi¹zanie dla danej kombinacji wierzcho³ków i wierzcho³ka
	{
	public:
		float value; //wartoœæ, na pocz¹tku INF
		uinteger lastVertex; //wierzcho³ek, który "wyprowadza" podrozwi¹zanie do po³¹czenia z kolejnym
		Solution()
		{
			value = Map::INF();
			lastVertex = V_INF;
		}
	};


	class SolutionListItem //tworzy listê trzymaj¹c¹ rozwi¹zania dla danego zbioru
	{
	public:
		SolutionListItem* next;
		Solution* item;
		ubyte vertex;

		SolutionListItem()
		{
			next = nullptr;
			item = nullptr;
			vertex = V_INF;
		}

		~SolutionListItem()
		{
			delete item;
			item = nullptr;
			next = nullptr;
		}
	};

	SolutionListItem* solutionsArray;

	SolutionSet(byte size)
	{
		this->size = size;
		auto requiredSize = 1 << (size - 1);
		solutionsArray = new SolutionListItem[requiredSize];
	}

	~SolutionSet(void)
	{
		delete[] solutionsArray;
	}

	Solution* getSolution(uinteger map, ubyte vertex) const
	{
		//pobieramy dany podzbiór
		SolutionListItem* item = solutionsArray + map;
		SolutionListItem* prev = nullptr;
		//szukamy rozwi¹zania
		while(item != nullptr && item->vertex != vertex)
		{
			prev = item;
			item = item->next;
		}
		if(item == nullptr) //jeœli go nie ma, tworzymy ("leniwie")
		{
			SolutionListItem* newItem = new SolutionListItem();
			newItem->vertex = vertex;
			newItem->item = new Solution();
			prev->next = newItem;
			item = newItem;
		}
		return item->item; //zwracamy dane rozwi¹zanie
	}
private:
	byte size;
};
