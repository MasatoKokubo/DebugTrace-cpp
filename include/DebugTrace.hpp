/// DebugTrace.hpp
/// (C) 2017 Masato Kokubo
#ifndef DBUEGTRACE_HPP_
#define DBUEGTRACE_HPP_

#if defined DEBUG || defined _DEBUG
	#define ENABLE_DEBUGTRACE 1
#endif
#if defined ENABLE_DEBUGTRACE
	#include <algorithm>
	#include <array>
	#include <cstdlib>
	#include <cstring>
	#include <ctime>
	#include <deque>
	#include <iomanip>
	#include <iostream>
	#include <list>
	#include <map>
	#include <memory>
	#include <set>
	#include <string>
	#if defined __GNUC__
		#include <cxxabi.h> // abi::__cxa_demangle()
	#endif
	#include <unordered_map>
	#include <unordered_set>
	#include <vector>

	#define DEBUG_TRACE_STATIC \
		namespace debugtrace {\
		bool DebugTrace::_inited;\
		int DebugTrace::_codeNestLevel;\
		int DebugTrace::_beforeCodeNestLevel;\
		int DebugTrace::_dataNestLevel;\
		} // namespace debugtrace

	#if defined __PRETTY_FUNCTION__
		// GCC, Clang
		#define DEBUG_TRACE debugtrace::DebugTrace trace(__PRETTY_FUNCTION__, __FILE__, __LINE__);
	#elif defined __FUNCSIG__
		// Visual C++
		#define DEBUG_TRACE debugtrace::DebugTrace trace(__FUNCSIG__, __FILE__, __LINE__);
	#else
		// etc
		#define DEBUG_TRACE debugtrace::DebugTrace trace(__func__, __FILE__, __LINE__);
	#endif
	#define DEBUG_MESSAGE(message) debugtrace::DebugTrace::print(message, __FILE__, __LINE__);
	#define DEBUG_PRINT(var) debugtrace::DebugTrace::print(#var, var, __FILE__, __LINE__);
#else // defined ENABLE_DEBUGTRACE
	#define DEBUG_TRACE_STATIC
	#define DEBUG_TRACE
	#define DEBUG_MESSAGE(message)
	#define DEBUG_PRINT(var)
#endif // defined ENABLE_DEBUGTRACE

#if defined ENABLE_DEBUGTRACE
namespace debugtrace {
/// A utility class for debugging.
/// Call DebugTrace.enter and DebugTrace.leave methods when enter and leave your methods,
/// then outputs execution trace of the program.
class DebugTrace {
private:

	static constexpr char const* libraryName       () {return "DebugTrace-cpp 1.0.0";}
	static constexpr char const* enterString       () {return "Enter ";}
	static constexpr char const* leaveString       () {return "Leave ";}
	static constexpr char const* codeIndentString  () {return "| ";}
	static constexpr char const* dataIndentString  () {return "  ";}
	static constexpr char const* startString       () {return "{";}
	static constexpr char const* endString         () {return "}";}
	static constexpr char const* delimiter         () {return ", ";}
	static constexpr char const* nameValueSeparator() {return " = ";}
	static constexpr char const* pairSeparator     () {return ":";}

	static int const _maxCodeIndents = 40;
	static int const _maxDataIndents = 40;
	static bool _inited;
	static std::ostream& stream() {return std::cerr;}
	static int _codeNestLevel;
	static int _beforeCodeNestLevel;
	static int _dataNestLevel;

	char const* _funcName = nullptr;

	static void init() noexcept {
		if (!_inited) {
			printSub([&] {stream() << libraryName();});
			printSub([] {});
			_inited = true;
		}
	}

public:

	DebugTrace() = delete;
	DebugTrace(DebugTrace const&) = delete;

	/// Outputs a message when entering the function.
	/// @param funcName the function name
	/// @param fileName the source file name of the code that called this constructor
	/// @param lineNumber the line number of the code that called this function
	DebugTrace(char const funcName[], char const fileName[], int lineNumber) noexcept {
		init();
		_funcName = funcName;

		if (_beforeCodeNestLevel > _codeNestLevel)
			printSub([] {});

		printSub([&] {stream() << enterString() << _funcName;}, fileName, lineNumber);

		_beforeCodeNestLevel = _codeNestLevel;
		++_codeNestLevel;
	}

	/// Outputs a message when leaving the function
	~DebugTrace() noexcept {
		_beforeCodeNestLevel = _codeNestLevel;
		--_codeNestLevel;

		printSub([&] {stream() << leaveString() << _funcName;});
	}

	DebugTrace& operator =(const DebugTrace&) = delete;

private:

	/// Outputs charasters for indent.
	static void printIndent() noexcept {
		for (int index = 0; index < _codeNestLevel; ++index)
			stream() << codeIndentString();

		for (int index = 0; index < _dataNestLevel; ++index)
			stream() << dataIndentString();
	}

	/// Outputs the date and time.
	static void printDateTime() noexcept {
		auto now = std::time(nullptr);
	#if defined(_MSC_VER)
		// Visual C++
		struct std::tm dateTime;
		localtime_s(&dateTime, &now);
	#else
		// Other
		auto dateTime = *std::localtime(&now);
	#endif
		stream()
			                                     << dateTime.tm_year + 1900 << '-'
			<< std::setfill('0') << std::setw(2) << dateTime.tm_mon + 1     << '-'
			<< std::setfill('0') << std::setw(2) << dateTime.tm_mday        << ' '
			<< std::setfill('0') << std::setw(2) << dateTime.tm_hour        << ':'
			<< std::setfill('0') << std::setw(2) << dateTime.tm_min         << ':'
			<< std::setfill('0') << std::setw(2) << dateTime.tm_sec         << ' ';
	}

public:

	/// Outputs the message.
	/// @param message the message
	/// @param fileName the source file name of the code that called this function
	/// @param lineNumber the line number of the code that called this function
	static void print(char const message[], char const fileName[], int lineNumber) noexcept {
		printSub([&] {stream() << message;}, fileName, lineNumber);
	}

	/// Outputs the name and a string representation of the object.
	/// @param name the name of the value
	/// @param value the value to output
	/// @param fileName the source file name of the code that called this function
	/// @param lineNumber the line number of the code that called this function
	template <typename T>
	static void print(char const name[], T const& value, char const fileName[], int lineNumber) noexcept {
		printSub([&] {
			stream() << name << nameValueSeparator();
			printValue(value);
		}, fileName, lineNumber);
	}

private:

	/// Outputs by outputer.
	/// @param outputer the output function
	/// @param fileName the source file name of the code that called this function
	/// @param lineNumber the line number of the code that called this function
	template <typename Function>
	static void printSub(Function outputer, char const fileName[] = "", int lineNumber = 0) noexcept {
		_dataNestLevel = 0;
		printDateTime();
		printIndent();

		outputer();

		if (fileName[0] != '\0') {
			char const *fileName2 = std::strrchr(fileName, '/');
			if (fileName2 == nullptr) {
				fileName2 = std::strrchr(fileName, '\\');
				if (fileName2 == nullptr)
					fileName2 = fileName;
				else
					++fileName2;
			} else
				++fileName2;

			stream() << " (" << fileName2 << pairSeparator() << lineNumber << ')';
		}

		stream() << std::endl;
	}

	/// Outputs a string representation of the type of the value.
	/// @param value the value to output
	template <typename T>
	static void printType(T const& value) noexcept {
	#if defined _MSC_VER
		stream() << '(' << typeid(value).name() << ')';
	#else
		int status;
		char* typeName = abi::__cxa_demangle(typeid(value).name(), nullptr, nullptr, &status);
		stream() << '(' << (typeName == nullptr ? "?" : typeName) << ')';
		if (typeName != nullptr)
			free(typeName);
	#endif
	}

	/// Outputs for line feed.
	static void printNextLine() noexcept {
		stream() << std::endl;
		printDateTime();
		printIndent();
	}

	/// Outputs a string representation of the value.
	/// @param value the value to output
	template <typename T>
	static void printValue(T const& value) noexcept {
		printType(value);
		stream() << value;
	}

	/// Outputs a string representation of the container object.
	/// @param container the container object to output
	template <class C>
	static void printContainer(C const& container) noexcept {
		bool multiLine = container.size() >= 2;

		printType(container);
		stream() << startString();
		if (multiLine) ++_dataNestLevel;

		auto delim = "";
		std::for_each(container.cbegin(), container.cend(),
			[&](auto element) {
				stream() << delim;
				if (multiLine)
					printNextLine();
				printValue(element);
				delim = delimiter();
			}
		);

		if (multiLine) {
			--_dataNestLevel;
			printNextLine();
		}
		stream() << endString();
	}

	/// Outputs a string representation of the value.
	/// @param value the value to output
	static void printValue(bool const& value) noexcept {
		stream() << (value ? "true" : "false");
	}

	/// Outputs a string representation of the value.
	/// @param value the value to output
	static void printValue(char const& value) noexcept {
		stream() << '\'' << value << '\'';
	}

	/// Outputs a string representation of the value.
	/// @param value the value to output
	static void printValue(signed char const& value) noexcept {
		stream() << "(signed char)'" << value <<  '\'';
	}

	/// Outputs a string representation of the value.
	/// @param value the value to output
	static void printValue(unsigned char const& value) noexcept {
		stream() << "(unsigned char)'" << value << '\'';
	}

	/// Outputs a string representation of the value.
	/// @param value the value to output
	static void printValue(short const& value) noexcept {
		stream() << "(unsigned short)" << value;
	}

	/// Outputs a string representation of the value.
	/// @param value the value to output
	static void printValue(unsigned short const& value) noexcept {
		stream() << "(unsigned short)" << value;
	}

	/// Outputs a string representation of the value.
	/// @param value the value to output
	static void printValue(int const& value) noexcept {
		stream() << value;
	}

	/// Outputs a string representation of the value.
	/// @param value the value to output
	static void printValue(unsigned int const& value) noexcept {
		stream() << value << 'u';
	}

	/// Outputs a string representation of the value.
	/// @param value the value to output
	static void printValue(long const& value) noexcept {
		stream() << value << 'L';
	}

	/// Outputs a string representation of the value.
	/// @param value the value to output
	static void printValue(unsigned long const& value) noexcept {
		stream() << value << "uL";
	}

	/// Outputs a string representation of the value.
	/// @param value the value to output
	static void printValue(long long const& value) noexcept {
		stream() << value << "LL";
	}

	/// Outputs a string representation of the value.
	/// @param value the value to output
	static void printValue(unsigned long long const& value) noexcept {
		stream() << value << "uLL";
	}

	/// Outputs a string representation of the value.
	/// @param value the value to output
	static void printValue(float const& value) noexcept {
		stream() << value << 'F';
	}

	/// Outputs a string representation of the value.
	/// @param value the value to output
	static void printValue(double const& value) noexcept {
		stream() << value;
	}

	/// Outputs a string representation of the value.
	/// @param value the value to output
	static void printValue(long double const& value) noexcept {
		stream() << value << 'L';
	}

	/// Outputs a string representation of the value.
	/// @param value the value to output
	static void printValue(char* const& value) noexcept {
		if (value == nullptr)
			stream() << "(char*)nullptr";
		else
			stream() << '"' << value << '"';
	}

	/// Outputs a string representation of the value.
	/// @param value the value to output
	static void printValue(signed char* const& value) noexcept {
		if (value == nullptr)
			stream() << "(signed char*)nullptr";
		else
			stream() << "(signed char*)\"" << value << '"';
	}

	/// Outputs a string representation of the value.
	/// @param value the value to output
	static void printValue(unsigned char* const& value) noexcept {
		if (value == nullptr)
			stream() << "(unsigned char*)nullptr";
		else
			stream() << "(unsigned char*)\"" << value << '"';
	}

	/// Outputs a string representation of the value.
	/// @param value the value to output
	static void printValue(char const* const& value) noexcept {
		if (value == nullptr)
			stream() << "(char const*)nullptr";
		else
			stream() << '"' << value << '"';
	}

	/// Outputs a string representation of the value.
	/// @param value the value to output
	static void printValue(signed char const* const& value) noexcept {
		if (value == nullptr)
			stream() << "(signed char const*)nullptr";
		else
			stream() << "(signed char const*)\"" << value << '"';
	}

	/// Outputs a string representation of the value.
	/// @param value the value to output
	static void printValue(unsigned char const* const& value) noexcept {
		if (value == nullptr)
			stream() << "(unsigned char const*)nullptr";
		else
			stream() << "(unsigned char const*)\"" << value << '"';
	}

	/// Outputs a string representation of the value.
	/// @param value the value to output
	static void printValue(std::string const& value) noexcept {
		stream() << "(std::string)\"" << value.c_str() << '"';
	}

	/// Outputs a string representation of the value.
	/// @param value the value to output
	template <typename T1, typename T2>
	static void printValue(std::pair<T1, T2> const& value) noexcept {
		stream() << value.first << pairSeparator() << value.second;
	}


	/// Outputs a string representation of the container object.
	/// @param container the container object to output
	template <typename T, size_t N>
	static void printValue(std::array<T, N> const& container) noexcept {
		printContainer(container);
	}

	/// Outputs a string representation of the container object.
	/// @param container the container object to output
	template <typename T, class Allocator = std::allocator<T>>
	static void printValue(std::deque<T, Allocator> const& container) noexcept {
		printContainer(container);
	}

	/// Outputs a string representation of the container object.
	/// @param container the container object to output
	template <typename T, class Allocator = std::allocator<T>>
	static void printValue(std::list<T, Allocator> const& container) noexcept {
		printContainer(container);
	}

	/// Outputs a string representation of the container object.
	/// @param container the container object to output
	template <
		typename Key,
		typename T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<std::pair<Key const, T>>
	>
	static void printValue(std::map<Key, T, Compare, Allocator> const& container) noexcept {
		printContainer(container);
	}

	/// Outputs a string representation of the container object.
	/// @param container the container object to output
	template <
		typename Key,
		typename T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<std::pair<Key const, T>>
	>
	static void printValue(std::multimap<Key, T, Compare, Allocator> const& container) noexcept {
		printContainer(container);
	}

	/// Outputs a string representation of the container object.
	/// @param container the container object to output
	template <
		typename Key,
		typename T,
		class Hash = std::hash<Key>,
		class Pred = std::equal_to<Key>,
		class Allocator = std::allocator<std::pair<Key const, T>>
	>
	static void printValue(std::unordered_map<Key, T, Hash, Pred, Allocator> const& container) noexcept {
		printContainer(container);
	}

	/// Outputs a string representation of the container object.
	/// @param container the container object to output
	template <
		typename Key,
		typename T,
		class Hash = std::hash<Key>,
		class Pred = std::equal_to<Key>,
		class Allocator = std::allocator<std::pair<Key const, T>>
	>
	static void printValue(std::unordered_multimap<Key, T, Hash, Pred, Allocator> const& container) noexcept {
		printContainer(container);
	}

	/// Outputs a string representation of the container object.
	/// @param container the container object to output
	template <
		typename Key,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<Key>
	>
	static void printValue(std::set<Key, Compare, Allocator> const& container) noexcept {
		printContainer(container);
	}

	/// Outputs a string representation of the container object.
	/// @param container the container object to output
	template <
		typename Key,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<Key>
	>
	static void printValue(std::multiset<Key, Compare, Allocator> const& container) noexcept {
		printContainer(container);
	}

	/// Outputs a string representation of the container object.
	/// @param container the container object to output
	template <
		typename Key,
		class Hash = std::hash<Key>,
		class Pred = std::equal_to<Key>,
		class Allocator = std::allocator<Key>
	>
	static void printValue(std::unordered_set<Key, Hash, Pred, Allocator> const& container) noexcept {
		printContainer(container);
	}

	/// Outputs a string representation of the container object.
	/// @param container the container object to output
	template <
		typename Key,
		class Hash = std::hash<Key>,
		class Pred = std::equal_to<Key>,
		class Allocator = std::allocator<Key>
	>
	static void printValue(std::unordered_multiset<Key, Hash, Pred, Allocator> const& container) noexcept {
		printContainer(container);
	}

	/// Outputs a string representation of the container object.
	/// @param container the container object to output
	template <typename T, class Allocator = std::allocator<T>>
	static void printValue(std::vector<T, Allocator> const& container) noexcept {
		printContainer(container);
	}
};

} // namespace debugtrace

#endif // defined ENABLE_DEBUGTRACE
#endif // ifndef DBUEGTRACE_HPP_
