#include "pch.h"
#include "../SortingAnalysis/SortingClass.h"
#include <random>
#include <iostream>

using namespace std;

TEST(Sorter, N2)
{
	Sorter<int> sorter([](int a, int b) {return a - b;});

	vector<int> countsForN2 = { 0, 1, 2, 10, (int)1e3 };

	for (int n : countsForN2)
	{
		vector<int> sequence(n);
		for (int i = 0; i < n; ++i)
		{
			sequence[i] = rand();
		}

		for (auto& sortedSequence : vector<vector<int>> 
			{
			sorter.Bubble(sequence), 
			sorter.Quick(sequence)
			})
		{
			for (int i = 0; i < n - 1; ++i) 
			{
				EXPECT_TRUE(sortedSequence[i] <= sortedSequence[i + 1]);
			}
		}
	}
}

TEST(Sorter, NLogN)
{
	Sorter<int> sorter([](int a, int b) {return a - b;});

	vector<int> countsForN2 = { 0, 1, 2, 10, (int)1e3 };
	vector<int> countsForNLogN = { (int)1e4, (int)1e5, (int)1e6 };

	vector<int> sequence;
	sequence.reserve((int)1e6);

	for (int n : countsForNLogN)
	{
		sequence.resize(n);
		for (int i = 0; i < n; ++i)
		{
			sequence[i] = rand();
		}

		for (auto& sortedSequence : vector<vector<int>>
			{
			sorter.Quick(sequence)
			})
		{
			for (int i = 0; i < n - 1; ++i)
			{
				EXPECT_TRUE(sortedSequence[i] <= sortedSequence[i + 1]);
			}
		}
		cout << n << endl;
	}
}
