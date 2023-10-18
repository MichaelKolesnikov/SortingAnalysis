#pragma once
#include <vector>
#include <functional>
#include <queue>

template <class T>
class Sorter {
private:
	std::function<int(T, T)> Comparator;

public:
	Sorter(std::function<int(T, T)> comparator) : Comparator(comparator) {}

	std::vector<T> Bubble(const std::vector<T>& sequence) const {
		std::vector<T> answer = sequence;
		int n = answer.size();
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n - i - 1; ++j) {
				if (Comparator(answer[j], answer[j + 1]) > 0) {
					std::swap(answer[j], answer[j + 1]);
				}
			}
		}
		return answer;
	}

	static std::pair<int, int> Partition(std::vector<T>& a, int l, int r, std::function<int(T, T)> comparator) {
		auto m1 = rand() % (r - l + 1) + l;
		std::swap(a[l], a[m1]);
		m1 = l;
		auto m2 = m1;
		for (auto i = l + 1; i <= r; ++i) {
			if (comparator(a[m1], a[i]) == 0) {
				++m2;
				std::swap(a[i], a[m2]);
			}
			else if (comparator(a[m1], a[i]) > 0) {
				std::swap(a[i], a[m1]);
				++m1;
				++m2;
				std::swap(a[i], a[m2]);
			}
		}
		return { m1, m2 };
	}

	static void QuickSort(std::vector<T>& a, int l, int r, std::function<int(T, T)> comparator) {
		while (l < r) {
			std::pair<int, int> p = Partition(a, l, r, comparator);
			auto m1 = p.first, m2 = p.second;
			if (m1 - l < r - m2) {
				QuickSort(a, l, m1 - 1, comparator);
				l = m2 + 1;
			}
			else {
				QuickSort(a, m2 + 1, r, comparator);
				r = m1 - 1;
			}
		}
	}

	std::vector<T> Quick(const std::vector<T>& sequence) const {
		auto answer = sequence;
		QuickSort(answer, 0, answer.size() - 1, Comparator);
		return answer;
	}
};

