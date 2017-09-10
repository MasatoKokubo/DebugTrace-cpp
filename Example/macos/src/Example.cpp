/// Example.cpp 
/// (C) 2017 Masato Kokubo
#include "stdafx.h"
#include "Example.hpp"
#include "DebugTrace.hpp"

DEBUG_TRACE_STATIC

int main(int argc, char const* argv[]) {
/**/DEBUG_TRACE
	ClassA classA;
	classA.func1();
	classA.func2();
	classA.func3();
	classA.func4();
	return 0;
}
