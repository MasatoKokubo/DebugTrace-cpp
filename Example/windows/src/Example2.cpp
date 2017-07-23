/// Example2.cpp 
/// (C) 2017 Masato Kokubo
#if defined _MSC_VER
	#include "stdafx.h"
#endif

#include <string>

#include "Example.hpp"
#include "DebugTrace.hpp"

/// ClassA::func2
void ClassA::func2() const noexcept {
/**/DEBUG_TRACE
/**/DEBUG_MESSAGE("")

	char* cstring1 = "This is a (char*) string.";
/**/DEBUG_PRINT(cstring1)

	char const* cstring2 = "This is a (char const*) string.";
/**/DEBUG_PRINT(cstring2)

	char* const cstring3 = "This is a (char* const) string.";
/**/DEBUG_PRINT(cstring3)

	char const* const cstring4 = "This is a (char const* const) string.";
/**/DEBUG_PRINT(cstring4)

/**/DEBUG_MESSAGE("")

	signed char* scstring1 = (signed char*)"This is a (signed char*) c-string.";
/**/DEBUG_PRINT(scstring1)

	signed char const* scstring2 = (signed char const*)"This is a (signed char const*) c-string.";
/**/DEBUG_PRINT(scstring2)

	signed char* const scstring3 = (signed char* const)"This is a (signed char* const) c-string.";
/**/DEBUG_PRINT(scstring3)

	signed char const* const scstring4 = (signed char const* const)"This is a (signed char const* const) c-string.";
/**/DEBUG_PRINT(scstring4)

/**/DEBUG_MESSAGE("")

	unsigned char* ucstring1 = (unsigned char*)"This is a (unsigned char*) c-string.";
/**/DEBUG_PRINT(ucstring1)

	unsigned char const* ucstring2 = (unsigned char const*)"This is a (unsigned char const*) c-string.";
/**/DEBUG_PRINT(ucstring2)

	unsigned char* const ucstring3 = (unsigned char* const)"This is a (unsigned char* const) c-string.";
/**/DEBUG_PRINT(ucstring3)

	unsigned char const* const ucstring4 = (unsigned char const* const)"This is a (unsigned char const* const) c-string.";
/**/DEBUG_PRINT(ucstring4)

/**/DEBUG_MESSAGE("")

	char const* cstring_null = nullptr;
/**/DEBUG_PRINT(cstring_null)

	signed char const* scstring_null = nullptr;
/**/DEBUG_PRINT(scstring_null)

	unsigned char const* ucstring_null = nullptr;
/**/DEBUG_PRINT(ucstring_null)

/**/DEBUG_MESSAGE("")

	std::string string1("This is a (std::string) string.");
/**/DEBUG_PRINT(string1)

	std::string const string2("This is a (std::string const) string.");
/**/DEBUG_PRINT(string2)

/**/DEBUG_MESSAGE("")
}
