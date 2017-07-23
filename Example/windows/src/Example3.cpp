/// Example3.cpp 
/// (C) 2017 Masato Kokubo
#if defined _MSC_VER
	#include "stdafx.h"
#endif

#include <array>
#include <deque>
#include <list>
#include <functional>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Example.hpp"
#include "DebugTrace.hpp"

/// ClassA::func3
void ClassA::func3() const noexcept {
/**/DEBUG_TRACE
	Point<int> p1(1, -2);
	const Point<int> p2(2, -3);
	Point<int> p3(3, -4);
	const Point<int> p4(4, -5);
	const Point<int>* p2p = &p2;
	const Point<int>* const * const p2pp = &p2p;
	const Point<int>& p2r = p2;
	const Point<int>* const p3p = nullptr;

/**/DEBUG_PRINT(p1)
/**/DEBUG_PRINT(p2)
/**/DEBUG_PRINT(*p2p)
/**/DEBUG_PRINT(p2p)
/**/DEBUG_PRINT(**p2pp)
/**/DEBUG_PRINT(*p2pp)
/**/DEBUG_PRINT(p2pp)
/**/DEBUG_PRINT(p2r)
/**/DEBUG_PRINT(p3p)
/**/DEBUG_PRINT(p1 + p2)
/**/DEBUG_PRINT(p1 * p2)

/**/DEBUG_MESSAGE("p2p <- nullptr")
	p2p = nullptr;
/**/DEBUG_PRINT(p2p)

	// std::array<T>
	std::array<Point<int>, 4> array1 = {p1, p2, p3, p4};
/**/DEBUG_PRINT(array1)

	// std::array<T1<T2>>
	std::array<Point<Point<int>>, 4> array2 = {
		Point<Point<int>>(Point<int>(1, 2), Point<int>(3, 4)),
		Point<Point<int>>(Point<int>(4, 5), Point<int>(6, 7))
	};
/**/DEBUG_PRINT(array2)

	// std::deque<T>
	std::deque<Point<int>> const deque1 = {p1, p2, p3, p4};
/**/DEBUG_PRINT(deque1)

	// std::list<T>
	std::list<Point<int>> list1 = {p1, p2, p3, p4};
/**/DEBUG_PRINT(list1)

	// std::map<Key, T>
	std::map<int, Point<int>> map1 = {
		std::make_pair(1, p1),
		std::make_pair(2, p2),
		std::make_pair(3, p3),
		std::make_pair(4, p4)
	};
/**/DEBUG_PRINT(map1)

	// std::map<Key, T, Compare>
	std::map<int, Point<int>, std::greater<int>> const map2 = {
		std::make_pair(10, p1),
		std::make_pair(20, p2),
		std::make_pair(30, p3),
		std::make_pair(40, p4)
	};
/**/DEBUG_PRINT(map2)

	// std::multimap<Key, T>
	std::multimap<int, Point<int>> multimap1 = {
		std::make_pair(1, p1),
		std::make_pair(2, p2),
		std::make_pair(3, p3),
		std::make_pair(4, p4)
	};
/**/DEBUG_PRINT(multimap1)

	// std::multimap<Key, T, Compare>
	std::multimap<int, Point<int>, std::greater<int>> const multimap2 = {
		std::make_pair(10, p1),
		std::make_pair(20, p2),
		std::make_pair(30, p3),
		std::make_pair(40, p4)
	};
/**/DEBUG_PRINT(multimap2)

	// std::unordered_map<Key, T>
	std::unordered_map<int, Point<int>> unordered_map1 = {
		std::make_pair(1, p1),
		std::make_pair(2, p2),
		std::make_pair(3, p3),
		std::make_pair(4, p4)
	};
/**/DEBUG_PRINT(unordered_map1)

	// std::unordered_multimap1<Key, T>
	std::unordered_multimap<int, Point<int>> const unordered_multimap1 = {
		std::make_pair(1, p1),
		std::make_pair(2, p2),
		std::make_pair(3, p3),
		std::make_pair(4, p4)
	};
/**/DEBUG_PRINT(unordered_multimap1)

	// std::set<Key>
	std::set<Point<int>> set1 = {p1, p2, p3, p4};
/**/DEBUG_PRINT(set1)

	// std::set<Key, Compare>
	std::set<Point<int>, std::greater<Point<int>>> const set2 = {p1, p2, p3, p4};
/**/DEBUG_PRINT(set2)

	// std::multiset<Key>
	std::multiset<Point<int>> multiset1 = {p1, p2, p3, p4};
/**/DEBUG_PRINT(multiset1)

	// std::multiset<Key, Compare>
	std::multiset<Point<int>, std::greater<Point<int>>> const multiset2 = {p1, p2, p3, p4};
/**/DEBUG_PRINT(multiset2)

	// std::unordered_set<Key>
	std::unordered_set<Point<int>> unordered_set1 = {p1, p2, p3, p4};
/**/DEBUG_PRINT(unordered_set1)

	// std::unordered_multiset<T>
	std::unordered_multiset<Point<int>> const unordered_multiset1 = {p1, p2, p3, p4};
/**/DEBUG_PRINT(unordered_multiset1)

	// std::vector<T>
	std::vector<Point<int>> vector1 = {p1, p2, p3, p4};
/**/DEBUG_PRINT(vector1)

	// std::vector<std::set<T>>
	std::vector<std::set<Point<int>>> setVector1 = {
		{p1, p2, p3, p4},
		{p2, p3, p4, p1},
		{p3, p4, p1, p2},
		{p4, p1, p2, p3}
	};
/**/DEBUG_PRINT(setVector1)
}
