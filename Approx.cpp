#pragma once

#include <iostream>
#include <fstream>
#include "Map.h"
#include "TspApx.h"
#include "MapLoader.h"
#include "MapGenerator.h"
#include <ctime>
#include "Solution.h"

const bool TEST = false;

void test()
{
	using namespace std;
	MapGenerator* generator = new MapGenerator();
	unsigned sizes[] = { 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
	unsigned sizesLenght = 17;
	unsigned repeats = 100;
	ofstream file;
	file.open("results.txt", ios_base::app);
	for (unsigned size = 0; size < sizesLenght; size++)
	{
		double average = 0;
		for (unsigned repeat = 0; repeat < repeats; repeat++)
		{
			Map* map = generator->generate(sizes[size]);
			TspApx* dp = new TspApx(map);
			clock_t begin = clock();
			Solution* result = dp->solve();
			clock_t end = clock();
			cout << "Suma: " << result->cost << endl;
			double elapsed_secs = double(end - begin);
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
	cout << "ATSP Dynamicznie" << endl;
	MapLoader* loader = new MapLoader();
	while (true)
	{
		Map* map = loader->load();
		if (map != nullptr) {
			TspApx* dp = new TspApx(map);
			Solution* result = dp->solve();
			cout << result;
			delete dp;
		}
	}
	delete loader;
}

int main(void) {
	if (TEST) {
		test();
	}
	else {
		presentation();
	}
	return 0;
}