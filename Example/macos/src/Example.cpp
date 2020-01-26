/// Example.cpp 
/// (C) 2017 Masato Kokubo
#include "Example.hpp"
#include "../../../include/debugtrace.hpp"

DEBUGTRACE_VARIABLES

int main(int argc, const char* argv[]) {
    DEBUGTRACE_ENTER // for Debugging
    ClassA classA;
    classA.func1();
    classA.func2();
    classA.func3();
    classA.func4();
    return 0;
}
