#pragma once

#include <iostream>
#include <fstream>
#include <ctime>
#include "MapGenerator.h"
#include "TspApx.h"
#include "TspDp.h"
#include "Solution.h"
#include "MapLoader.h"

using namespace std;
const unsigned repeats = 100;

void test()
{
	auto generator = new MapGenerator();
	ofstream file;
	file.open("result1.txt", ios_base::app);
	for (unsigned size = 4; size < 22; ++size)
	{
		double averageDp = 0;
		double averageApx = 0;
		double averageOpt = 0;
		for (unsigned repeat = 0; repeat < repeats; ++repeat)
		{
			auto map = generator->generate(size);
			auto apx = new TspApx(map);
			auto dp = new TspDp(map);
			auto begin = clock();
			auto result = dp->solve();
			auto end = clock();
			cout << "DP " << result->cost << " ";
			averageDp += (double(end - begin) * double(1000.0 / CLOCKS_PER_SEC)) / double(repeats);
			begin = clock();
			auto result2 = apx->solve();
			end = clock();
			cout << "APX " << result2->cost << " ";
			averageApx += (double(end - begin) * double(1000.0 / CLOCKS_PER_SEC)) / double(repeats);
			averageOpt += (result2->cost / result->cost) / static_cast<double>(repeats);
			delete dp;
			delete apx;
		}
		cout << "Zakoñczono " << size << endl;
		file << size << '\t' << averageDp << '\t' << averageApx << '\t' << averageOpt << endl;
	}
	file.close();
	delete generator;
}

void presentation()
{
	using namespace std;
	auto loader = new MapLoader();
	char c = 0;
	while (c != 'q')
	{
		auto map = loader->load();
		if (map != nullptr)
		{
			auto dp = new TspApx(map);
			auto result = dp->solve();
			for (unsigned i = 0; i < result->size; ++i)
			{
				cout << result->order[i] << " ";
			}
			cout << "\nWaga: " << result->cost << endl;
			delete dp;
		}
		c = cin.get();
	}
	delete loader;
}

int main(void)
{
	test();
	//presentation();
	return 0;
}

