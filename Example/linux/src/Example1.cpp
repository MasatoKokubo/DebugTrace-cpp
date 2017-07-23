/// Example1.cpp 
/// (C) 2017 Masato Kokubo
#if defined _MSC_VER
	#include "stdafx.h"
#endif

#include "Example.hpp"
#include "DebugTrace.hpp"

/// func1
void ClassA::func1() const noexcept {
/**/DEBUG_TRACE
	bool const         bool0   = false;
	bool               bool1   = true;
	char const         char1   = 'A';
	signed char        schar1  = 'B';
	unsigned char      uchar1  = 'C';
	short const        short1  = -1;
	signed short       sshort1 = -2;
	unsigned short     ushort1 =  2;
	int const          int1    = -11;
	signed int         sint1   = -22;
	unsigned int       uint1   =  22;
	long const         long1   = -111L;
	signed long        slong1  = -222L;
	unsigned long      ulong1  =  222L;
	long long const    llong1  = -1111LL;
	signed long long   sllong1 = -2222LL;
	unsigned long long ullong1 =  2222LL;
	float const        float1  = -11.11F;
	double             double1 = -2222.2222;
	long double        ldouble1 = -333333.333333L;

/**/DEBUG_PRINT(bool0  )
/**/DEBUG_PRINT(bool1  )
/**/DEBUG_PRINT(char1  )
/**/DEBUG_PRINT(schar1 )
/**/DEBUG_PRINT(uchar1 )
/**/DEBUG_PRINT(short1 )
/**/DEBUG_PRINT(sshort1)
/**/DEBUG_PRINT(ushort1)
/**/DEBUG_PRINT(int1   )
/**/DEBUG_PRINT(sint1  )
/**/DEBUG_PRINT(uint1  )
/**/DEBUG_PRINT(long1  )
/**/DEBUG_PRINT(slong1 )
/**/DEBUG_PRINT(ulong1 )
/**/DEBUG_PRINT(llong1 )
/**/DEBUG_PRINT(sllong1)
/**/DEBUG_PRINT(ullong1)
/**/DEBUG_PRINT(float1 )
/**/DEBUG_PRINT(double1)
/**/DEBUG_PRINT(ldouble1)
}
