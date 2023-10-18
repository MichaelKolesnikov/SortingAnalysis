#include <iostream>
#include "SortingClass.h"
#include <random>
#include <string>
#include <thread>
#include <algorithm>

using namespace std;

void EnterTheAverageOperatingTimeIntoTheTable(function<vector<int>(const vector<int>&)> sortFunction, int n, vector<vector<float>>& timeResults, int sortNumber, int nNumber, int countOfTests) {
	float averageTime = -1;
	vector<int> sequence(n);
	for (int measureNumber = 1; measureNumber <= countOfTests; ++measureNumber) {
		for (auto& it : sequence) {
			it = rand();
		}
		auto start = chrono::high_resolution_clock().now();
		auto tmp = sortFunction(sequence);
		auto end = chrono::high_resolution_clock().now();
		chrono::duration<float> duration = end - start;
		if (measureNumber == 1) {
			averageTime = duration.count();
		}
		else {
			averageTime = ((measureNumber - 1) * averageTime + duration.count()) / measureNumber;
			// ans[i] = ((i - 1)*ans[i - 1] + a[i]) / i
		}
	}
	timeResults[sortNumber][nNumber] = averageTime;
}

int main() {
	Sorter<int> sorter([](int a, int b) {return b - a;});
	vector<string> sortingNamesN2 = { "Bubble" };
	vector<string> sortingNamesNLogN = { "Merge" };

	int countN2 = sortingNamesN2.size();
	int countNLogN = sortingNamesNLogN.size();
	int countSortingMethods = countN2 + countNLogN;

	vector<int> nForN2 = { 0, 5, 100, (int)1e3, (int)1e4 };
	vector<int> nForNLogN = { (int)1e5, (int)1e6, (int)1e7 };
	auto n = nForN2;
	n.insert(n.end(), nForNLogN.begin(), nForNLogN.end());

	vector<vector<float>> timeResults(countSortingMethods, vector<float>(nForN2.size() + nForNLogN.size()));
	vector<vector<thread>> threads(countSortingMethods);

	int sortNumber = 0;
	for (int nNumber = 0; nNumber < nForN2.size(); ++nNumber) {
		int currentN = n[nNumber];
		int countOfTests = nForN2.size() - nNumber;
		function<vector<int>(const vector<int>&)> sortFunction = [&sorter](const vector<int>& sequence) {return sorter.Bubble(sequence);};
		threads[sortNumber].push_back(thread(EnterTheAverageOperatingTimeIntoTheTable, sortFunction, currentN, std::ref(timeResults), sortNumber, nNumber, countOfTests));
		++sortNumber;
		// for other kind of sort
		sortNumber = 0;
	}
	sortNumber = sortingNamesN2.size();
	for (int nNumber = 0; nNumber < n.size(); ++nNumber) {
		int currentN = n[nNumber];
		int countOfTests = n.size() - nNumber;
		function<vector<int>(const vector<int>&)> sortFunction = [&sorter](const vector<int>& sequence) { return sorter.Quick(sequence);};
		threads[sortNumber].push_back(thread(EnterTheAverageOperatingTimeIntoTheTable, sortFunction, currentN, std::ref(timeResults), sortNumber, nNumber, countOfTests));
		++sortNumber;
		// for other kind of sort
		sortNumber = sortingNamesN2.size();
	}

	for (auto& v : threads) {
		for (auto& th : v) {
			th.join();
		}
	}

	for (auto& v : timeResults) {
		for (auto& it : v) {
			cout << it << ' ';
		}
		cout << endl;
	}
}
