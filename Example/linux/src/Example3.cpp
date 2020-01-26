/// Example3.cpp 
/// (C) 2017 Masato Kokubo
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
#include "debugtrace.hpp"

/// ClassA::func3
void ClassA::func3() const noexcept {
	DEBUGTRACE_ENTER // for Debugging
    Point<int> p1(1, -2);
    const Point<int> p2(2, -3);
    Point<int> p3(3, -4);
    const Point<int> p4(4, -5);
    const Point<int> p5(5, -6);
    const Point<int>* p2p = &p2;
    const Point<int>* const * const p2pp = &p2p;
    const Point<int>& p2r = p2;
    const Point<int>* const p3p = nullptr;

    DEBUGTRACE_PRINT(p1) // for Debugging
    DEBUGTRACE_PRINT(p2) // for Debugging
    DEBUGTRACE_PRINT(*p2p) // for Debugging
    DEBUGTRACE_PRINT(p2p) // for Debugging
    DEBUGTRACE_PRINT(**p2pp) // for Debugging
    DEBUGTRACE_PRINT(*p2pp) // for Debugging
//  DEBUGTRACE_PRINT(p2pp) // for Debugging
    DEBUGTRACE_PRINT(p2r) // for Debugging
    DEBUGTRACE_PRINT(p3p) // for Debugging
    DEBUGTRACE_PRINT(p1 + p2) // for Debugging
    DEBUGTRACE_PRINT(p1 * p2) // for Debugging

    DEBUGTRACE_MESSAGE("p2p <- nullptr") // for Debugging
    p2p = nullptr;
    DEBUGTRACE_PRINT(p2p) // for Debugging

    // std::array<T>
    std::array<Point<int>, 0> array0 = {};
    DEBUGTRACE_PRINT(array0) // for Debugging

    std::array<Point<int>, 1> array1 = {p1};
    DEBUGTRACE_PRINT(array1) // for Debugging

    std::array<Point<int>, 4> array2 = {p1, p2, p3, p4};
    DEBUGTRACE_PRINT(array2) // for Debugging

    // std::array<T1<T2>>
    std::array<Point<Point<int>>, 4> array2_2 = {
        Point<Point<int>>(Point<int>(1, 2), Point<int>(3, 4)),
        Point<Point<int>>(Point<int>(4, 5), Point<int>(6, 7))
    };
    DEBUGTRACE_PRINT(array2_2) // for Debugging

    // std::deque<T>
    const std::deque<Point<int>> deque0 = {};
    DEBUGTRACE_PRINT(deque0) // for Debugging

    const std::deque<Point<int>> deque1 = {p1};
    DEBUGTRACE_PRINT(deque1) // for Debugging

    const std::deque<Point<int>> deque4 = {p1, p2, p3, p4};
    DEBUGTRACE_PRINT(deque4) // for Debugging

    // std::list<T>
    std::list<Point<int>> list0 = {};
    DEBUGTRACE_PRINT(list0) // for Debugging

    std::list<Point<int>> list1 = {p1};
    DEBUGTRACE_PRINT(list1) // for Debugging

    std::list<Point<int>> list4 = {p1, p2, p3, p4};
    DEBUGTRACE_PRINT(list4) // for Debugging

    // std::map<Key, T>
    auto maximum_data_output_width = debugtrace::maximum_data_output_width;
    std::map<int, int> map0 = {};
    DEBUGTRACE_PRINT(map0) // for Debugging

    debugtrace::maximum_data_output_width = 200;
    std::map<int, int> map1 = {std::make_pair(1, 2)};
    DEBUGTRACE_PRINT(map1) // for Debugging

    std::map<int, int> map4 = {
        std::make_pair(1, 2),
        std::make_pair(2, 3),
        std::make_pair(3, 4),
        std::make_pair(4, 5)
    };
    DEBUGTRACE_PRINT(map4) // for Debugging
    debugtrace::maximum_data_output_width = maximum_data_output_width;

    // std::map<Key, T>
    std::map<int, Point<int>> map2_0 = {};
    DEBUGTRACE_PRINT(map2_0) // for Debugging

    std::map<int, Point<int>> map2_1 = {std::make_pair(1, p1)};
    DEBUGTRACE_PRINT(map2_1) // for Debugging

    std::map<int, Point<int>> map2_4 = {
        std::make_pair(1, p1),
        std::make_pair(2, p2),
        std::make_pair(3, p3),
        std::make_pair(4, p4)
    };
    DEBUGTRACE_PRINT(map2_4) // for Debugging

    // std::map<Key, vector<T>>
    std::map<Point<int>, std::vector<Point<int>>> map3_0 = {};
    DEBUGTRACE_PRINT(map3_0) // for Debugging

    std::map<Point<int>, std::vector<Point<int>>> map3_1 = {
        std::make_pair(p1, std::vector<Point<int>>({p2, p3, p4}))
    };
    DEBUGTRACE_PRINT(map3_1) // for Debugging

    std::map<Point<int>, std::vector<Point<int>>> map3_4 = {
        std::make_pair(p1, std::vector<Point<int>>({p2, p3, p4})),
        std::make_pair(p2, std::vector<Point<int>>({p3, p4, p5})),
        std::make_pair(p3, std::vector<Point<int>>({p4, p5, p1})),
        std::make_pair(p4, std::vector<Point<int>>({p5, p1, p2}))
    };
    DEBUGTRACE_PRINT(map3_4) // for Debugging

    // std::map<Key, T, Compare>
    const std::map<int, Point<int>, std::greater<int>> map4_4 = {
        std::make_pair(10, p1),
        std::make_pair(20, p2),
        std::make_pair(30, p3),
        std::make_pair(40, p4)
    };
    DEBUGTRACE_PRINT(map4_4) // for Debugging

    // std::multimap<Key, T>
    std::multimap<int, Point<int>> multimap1 = {
        std::make_pair(1, p1),
        std::make_pair(2, p2),
        std::make_pair(3, p3),
        std::make_pair(4, p4)
    };
    DEBUGTRACE_PRINT(multimap1) // for Debugging

    // std::multimap<Key, T, Compare>
    const std::multimap<int, Point<int>, std::greater<int>> multimap2 = {
        std::make_pair(10, p1),
        std::make_pair(20, p2),
        std::make_pair(30, p3),
        std::make_pair(40, p4)
    };
    DEBUGTRACE_PRINT(multimap2) // for Debugging

    // std::unordered_map<Key, T>
    std::unordered_map<int, Point<int>> unordered_map1 = {
        std::make_pair(1, p1),
        std::make_pair(2, p2),
        std::make_pair(3, p3),
        std::make_pair(4, p4)
    };
    DEBUGTRACE_PRINT(unordered_map1) // for Debugging

    // std::unordered_multimap1<Key, T>
    const std::unordered_multimap<int, Point<int>> unordered_multimap1 = {
        std::make_pair(1, p1),
        std::make_pair(2, p2),
        std::make_pair(3, p3),
        std::make_pair(4, p4)
    };
    DEBUGTRACE_PRINT(unordered_multimap1) // for Debugging

    // std::set<Key>
    std::set<Point<int>> set0 = {};
    DEBUGTRACE_PRINT(set0) // for Debugging

    std::set<Point<int>> set1 = {p1};
    DEBUGTRACE_PRINT(set1) // for Debugging

    std::set<Point<int>> set4 = {p1, p2, p3, p4};
    DEBUGTRACE_PRINT(set4) // for Debugging

    // std::set<Key, Compare>
    const std::set<Point<int>, std::greater<Point<int>>> set2_0 = {};
    DEBUGTRACE_PRINT(set2_0) // for Debugging

    const std::set<Point<int>, std::greater<Point<int>>> set2_1 = {p1};
    DEBUGTRACE_PRINT(set2_1) // for Debugging

    const std::set<Point<int>, std::greater<Point<int>>> set2_4 = {p1, p2, p3, p4};
    DEBUGTRACE_PRINT(set2_4) // for Debugging

    // std::multiset<Key>
    std::multiset<Point<int>> multiset0 = {p1};
    DEBUGTRACE_PRINT(multiset0) // for Debugging

    std::multiset<Point<int>> multiset1 = {p1};
    DEBUGTRACE_PRINT(multiset1) // for Debugging

    std::multiset<Point<int>> multiset4 = {p1, p2, p3, p4};
    DEBUGTRACE_PRINT(multiset4) // for Debugging

    // std::multiset<Key, Compare>
    const std::multiset<Point<int>, std::greater<Point<int>>> multiset2_0 = {};
    DEBUGTRACE_PRINT(multiset2_0) // for Debugging

    const std::multiset<Point<int>, std::greater<Point<int>>> multiset2_1 = {p1};
    DEBUGTRACE_PRINT(multiset2_1) // for Debugging

    const std::multiset<Point<int>, std::greater<Point<int>>> multiset2_4 = {p1, p2, p3, p4};
    DEBUGTRACE_PRINT(multiset2_4) // for Debugging

    // std::unordered_set<Key>
    std::unordered_set<Point<int>> unordered_set0 = {};
    DEBUGTRACE_PRINT(unordered_set0) // for Debugging

    std::unordered_set<Point<int>> unordered_set1 = {p1};
    DEBUGTRACE_PRINT(unordered_set1) // for Debugging

    std::unordered_set<Point<int>> unordered_set4 = {p1, p2, p3, p4};
    DEBUGTRACE_PRINT(unordered_set4) // for Debugging

    // std::unordered_multiset<T>
    const std::unordered_multiset<Point<int>> unordered_multiset0 = {};
    DEBUGTRACE_PRINT(unordered_multiset0) // for Debugging

    const std::unordered_multiset<Point<int>> unordered_multiset1 = {p1};
    DEBUGTRACE_PRINT(unordered_multiset1) // for Debugging

    const std::unordered_multiset<Point<int>> unordered_multiset4 = {p1, p2, p3, p4};
    DEBUGTRACE_PRINT(unordered_multiset4) // for Debugging

    // std::vector<T>
    std::vector<Point<int>> vector0 = {};
    DEBUGTRACE_PRINT(vector0) // for Debugging

    std::vector<Point<int>> vector1 = {p1};
    DEBUGTRACE_PRINT(vector1) // for Debugging

    std::vector<Point<int>> vector4 = {p1, p2, p3, p4};
    DEBUGTRACE_PRINT(vector4) // for Debugging

    // std::vector<std::set<T>>
    std::vector<std::set<Point<int>>> setVector0x0 = {};
    DEBUGTRACE_PRINT(setVector0x0) // for Debugging

    // std::vector<std::set<T>>
    std::vector<std::set<Point<int>>> setVector1x1 = {
        {p1},
    };
    DEBUGTRACE_PRINT(setVector1x1) // for Debugging

    // std::vector<std::set<T>>
    std::vector<std::set<Point<int>>> setVector4x4 = {
        {p1, p2, p3, p4},
        {p2, p3, p4, p1},
        {p3, p4, p1, p2},
        {p4, p1, p2, p3}
    };
    DEBUGTRACE_PRINT(setVector4x4) // for Debugging
}
