#pragma once
#include <iostream>
#include <bitset>
#include "Map.h"

typedef uint8_t ubyte;
typedef int8_t byte;
typedef int32_t integer;
typedef uint32_t uinteger;
/*
Miko�aj Sty�, 209773
Zbi�r w kt�rym zapisywane s� po�rednie rozwi�zania
*/
class SolutionSet
{
public:
	static const ubyte V_INF = UINT8_MAX; //brak wierzcho�ka

	class Solution //rozwi�zanie dla danej kombinacji wierzcho�k�w i wierzcho�ka
	{
	public:
		float value; //warto��, na pocz�tku INF
		uinteger lastVertex; //wierzcho�ek, kt�ry "wyprowadza" podrozwi�zanie do po��czenia z kolejnym
		Solution()
		{
			value = Map::INF();
			lastVertex = V_INF;
		}
	};


	class SolutionListItem //tworzy list� trzymaj�c� rozwi�zania dla danego zbioru
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
		//pobieramy dany podzbi�r
		SolutionListItem* item = solutionsArray + map;
		SolutionListItem* prev = nullptr;
		//szukamy rozwi�zania
		while(item != nullptr && item->vertex != vertex)
		{
			prev = item;
			item = item->next;
		}
		if(item == nullptr) //je�li go nie ma, tworzymy ("leniwie")
		{
			SolutionListItem* newItem = new SolutionListItem();
			newItem->vertex = vertex;
			newItem->item = new Solution();
			prev->next = newItem;
			item = newItem;
		}
		return item->item; //zwracamy dane rozwi�zanie
	}
private:
	byte size;
};
