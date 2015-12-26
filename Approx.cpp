#pragma once

#include <iostream>
#include <fstream>
#include "MapGenerator.h"
#include "TspApx.h"
#include <ctime>
#include "Solution.h"
#include "MapLoader.h"

const bool TEST = false;

void test()
{
	using namespace std;
	auto generator = new MapGenerator();
	unsigned sizes[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
	unsigned sizesLenght = 17;
	unsigned repeats = 100;
	ofstream file;
	file.open("results.txt", ios_base::app);
	for (unsigned size = 0; size < sizesLenght; size++)
	{
		double average = 0;
		for (unsigned repeat = 0; repeat < repeats; repeat++)
		{
			auto map = generator->generate(sizes[size]);
			auto dp = new TspApx(map);
			auto begin = clock();
			auto result = dp->solve();
			auto end = clock();
			cout << "Suma: " << result->cost << endl;
			auto elapsed_secs = double(end - begin);
			average += elapsed_secs;
			delete dp;
		}
		average /= sizesLenght;
		file << sizes[size] << '\t' << average << endl;
	}
	file.close();
	delete generator;
}

void presentation()
{
	using namespace std;
	//cout << "ATSP Dynamicznie" << endl;
	auto loader = new MapLoader();
	//	while (true)
	//	{
	auto map = loader->load("att48.txt");
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
	cin.get();
	//	}
	delete loader;
}

int main(void)
{
	if (TEST)
	{
		test();
	}
	else
	{
		presentation();
	}
	return 0;
}

