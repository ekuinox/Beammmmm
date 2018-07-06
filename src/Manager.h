#pragma once

#include <vector>
#include <algorithm>
#include "PaintObject.h"

template <typename _T>
std::vector<std::vector<_T>> combinations(std::vector<_T> v, int cnt = 2)
{
	std::vector<bool> bitset(v.size() - cnt, 0);
	bitset.resize(v.size(), 1);

	std::vector<std::vector<_T>> result;

	do {
		std::vector<_T> tmp;
		for (size_t i = 0; i != v.size(); ++i) {
			if (bitset[i])
				tmp.push_back(v[i]);
		}
		result.push_back(tmp);
	} while (std::next_permutation(bitset.begin(), bitset.end()));

	return result;
}

template <typename _T>
void swap(_T &a, _T &b)
{
	auto tmp = a;
	a = b;
	b = tmp;
}

class Manager {
private:
	std::vector<PaintObjectInterface*> polygons;
	void init();
public:
	Manager();
	~Manager();
	void update();
	void input(DWORD);
	void draw(HWND);
};
