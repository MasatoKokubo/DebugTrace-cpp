/// Example1.cpp 
/// (C) 2017 Masato Kokubo
#include "Example.hpp"
#include "debugtrace.hpp"

/// func1
void ClassA::func1() const noexcept {
	DEBUGTRACE_ENTER // for Debugging
    bool const         bool0   = false;
    bool               bool1   = true;
    const char         char1   = 'A';
    signed char        schar1  = 'B';
    unsigned char      uchar1  = 'C';
    short const        short1  = -1;
    signed short       sshort1 = -2;
    unsigned short     ushort1 =  2;
    int const          int1    = -11;
    signed int         sint1   = -22;
    unsigned int       uint1   =  22;
    const long         long1   = -111L;
    signed long        slong1  = -222L;
    unsigned long      ulong1  =  222L;
    const long long    llong1  = -1111LL;
    signed long long   sllong1 = -2222LL;
    unsigned long long ullong1 =  2222LL;
    const float        float1  = -11.11F;
    double             double1 = -2222.2222;
    long double        ldouble1 = -333333.333333L;

    DEBUGTRACE_PRINT(bool0  ) // for Debugging
    DEBUGTRACE_PRINT(bool1  ) // for Debugging
    DEBUGTRACE_PRINT(char1  ) // for Debugging
    DEBUGTRACE_PRINT(schar1 ) // for Debugging
    DEBUGTRACE_PRINT(uchar1 ) // for Debugging
    DEBUGTRACE_PRINT(short1 ) // for Debugging
    DEBUGTRACE_PRINT(sshort1) // for Debugging
    DEBUGTRACE_PRINT(ushort1) // for Debugging
    DEBUGTRACE_PRINT(int1   ) // for Debugging
    DEBUGTRACE_PRINT(sint1  ) // for Debugging
    DEBUGTRACE_PRINT(uint1  ) // for Debugging
    DEBUGTRACE_PRINT(long1  ) // for Debugging
    DEBUGTRACE_PRINT(slong1 ) // for Debugging
    DEBUGTRACE_PRINT(ulong1 ) // for Debugging
    DEBUGTRACE_PRINT(llong1 ) // for Debugging
    DEBUGTRACE_PRINT(sllong1) // for Debugging
    DEBUGTRACE_PRINT(ullong1) // for Debugging
    DEBUGTRACE_PRINT(float1 ) // for Debugging
    DEBUGTRACE_PRINT(double1) // for Debugging
    DEBUGTRACE_PRINT(ldouble1) // for Debugging
}
