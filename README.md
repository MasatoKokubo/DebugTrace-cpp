DebugTrace-cpp
==============

DebugTrace-cpp is a C++14 library for outputting debug logs.  
You can use DebugTrace-cpp by simply downloading DebugTrace-cpp.zip and including DebugTrace.hpp contained in it.  
It is a library of a header file only, and there are no linked files (*.lib, *.a, etc).  
The C++ compiler requires C++14.

### How to use

Use the following macros.

|Macro name (argument)|Description|
|:--|:--|
|`DEBUG_TRACE_STATIC`    |Write it only in one of the source files (for example, the file containing the main function).|
|`DEBUG_TRACE`           |By describing it at the start position of the function, outputs a log at the start and end of the function.|
|`DEBUG_MESSAGE(message)`|Outputs the message.|
|`DEBUG_PRINT(var)`      |Outputs the name and value of the variable.|

### An example of use
```
#if defined _MSC_VER
    #include "stdafx.h"
#endif
#include "DebugTrace.hpp"
#include <vector>

DEBUG_TRACE_STATIC // Described in only one source

template <typename T> class Point {
    private:
        T _x = 0;
        T _y = 0;
    public:
        Point(T const& x, T const& y) noexcept : _x(x), _y(y) {}
        auto x() const noexcept {return _x;}
        auto y() const noexcept {return _y;}
};
template <typename T> auto operator +(Point<T> const& p1, Point<T> const& p2) noexcept {
    return Point<T>(p1.x() + p2.x(), p1.y() + p2.y());
}
template <typename T> std::ostream& operator <<(std::ostream& stream, Point<T> const& p) {
    return stream << "(x:" << p.x() << ", y:" << p.y() << ')';
}

void sub() {
    DEBUG_TRACE
    Point<int> p1 = Point<int>(1, 2);
    Point<int> p2 = Point<int>(3, 4);
    Point<int> p3 = p1 + p2;
    std::vector<Point<int>> v = {p1, p2, p3};
    DEBUG_PRINT(p1)
    DEBUG_PRINT(p2)
    DEBUG_PRINT(p3)
    DEBUG_PRINT(v)
}

int main() {
    DEBUG_TRACE
    sub();
    return 0;
}
```



### An example of execution (on Linux / GCC 6.3.0)
```
2017-07-23 14:52:40 DebugTrace-cpp 1.0.0
2017-07-23 14:52:40 
2017-07-23 14:52:40 Enter main (READMEexample.cpp:38)
2017-07-23 14:52:40 | Enter sub (READMEexample.cpp:26)
2017-07-23 14:52:40 | | p1 = (Point<int>)(x:1, y:2) (READMEexample.cpp:31)
2017-07-23 14:52:40 | | p2 = (Point<int>)(x:3, y:4) (READMEexample.cpp:32)
2017-07-23 14:52:40 | | p3 = (Point<int>)(x:4, y:6) (READMEexample.cpp:33)
2017-07-23 14:52:40 | | v = (std::vector<Point<int>, std::allocator<Point<int> > >){
2017-07-23 14:52:40 | |   (Point<int>)(x:1, y:2), 
2017-07-23 14:52:40 | |   (Point<int>)(x:3, y:4), 
2017-07-23 14:52:40 | |   (Point<int>)(x:4, y:6)
2017-07-23 14:52:40 | | } (READMEexample.cpp:34)
2017-07-23 14:52:40 | Leave sub
2017-07-23 14:52:40 Leave main
```

### An example of execution (on macOS / Xcode 8.3.3)
```
2017-07-23 16:12:05 DebugTrace-cpp 1.0.0
2017-07-23 16:12:05 
2017-07-23 16:12:05 Enter main (READMEexample.cpp:38)
2017-07-23 16:12:05 | Enter sub (READMEexample.cpp:26)
2017-07-23 16:12:05 | | p1 = (Point<int>)(x:1, y:2) (READMEexample.cpp:31)
2017-07-23 16:12:05 | | p2 = (Point<int>)(x:3, y:4) (READMEexample.cpp:32)
2017-07-23 16:12:05 | | p3 = (Point<int>)(x:4, y:6) (READMEexample.cpp:33)
2017-07-23 16:12:05 | | v = (std::__1::vector<Point<int>, std::__1::allocator<Point<int> > >){
2017-07-23 16:12:05 | |   (Point<int>)(x:1, y:2), 
2017-07-23 16:12:05 | |   (Point<int>)(x:3, y:4), 
2017-07-23 16:12:05 | |   (Point<int>)(x:4, y:6)
2017-07-23 16:12:05 | | } (READMEexample.cpp:34)
2017-07-23 16:12:05 | Leave sub
2017-07-23 16:12:05 Leave main
```

### An example of execution (on Windows / Visual C++ 2017)
```
2017-07-23 15:12:27 DebugTrace-cpp 1.0.0
2017-07-23 15:12:27
2017-07-23 15:12:27 Enter int __cdecl main(void) (readmeexample.cpp:38)
2017-07-23 15:12:27 | Enter void __cdecl sub(void) (readmeexample.cpp:26)
2017-07-23 15:12:27 | | p1 = (class Point<int>)(x:1, y:2) (readmeexample.cpp:31)
2017-07-23 15:12:27 | | p2 = (class Point<int>)(x:3, y:4) (readmeexample.cpp:32)
2017-07-23 15:12:27 | | p3 = (class Point<int>)(x:4, y:6) (readmeexample.cpp:33)
2017-07-23 15:12:27 | | v = (class std::vector<class Point<int>,class std::allocator<class Point<int> > >){
2017-07-23 15:12:27 | |   (class Point<int>)(x:1, y:2),
2017-07-23 15:12:27 | |   (class Point<int>)(x:3, y:4),
2017-07-23 15:12:27 | |   (class Point<int>)(x:4, y:6)
2017-07-23 15:12:27 | | } (readmeexample.cpp:34)
2017-07-23 15:12:27 | Leave void __cdecl sub(void)
2017-07-23 15:12:27 Leave int __cdecl main(void)
```
