//	DebugTrace.cpp
//
//	(C) 2016 Masato Kokubo
#include "pch.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "DebugTrace.hpp"

// The library name and version c-string
const char* DebugTrace::_libraryName = "DebugTrace.cpp14 0.1.1";

// The enter c-string
const char* DebugTrace::_enterString = "Enter ";

// The leave c-string
const char* DebugTrace::_leaveString = "Leave ";

// The separator c-string of name and value
const char* DebugTrace::_separator   = " = ";

// The indent c-string
const char* DebugTrace::_indentString   = "| ";

// Max indents
const size_t DebugTrace::_maxIndents = 40;

// The initialized flag
bool DebugTrace::_inited = false;

// Array of indent strings
std::vector<std::string> DebugTrace::_indents;

// The output stream
std::ostream& DebugTrace::_stream = std::cerr; 

// The nest level
int DebugTrace::_nestLevel = 0;

// The before nest Leval
int DebugTrace::_beforeNestLevel = 0;

// Initializes this library.
void DebugTrace::init() noexcept {
	if (!_inited) {
		for (size_t index = 0; index < _maxIndents; ++index)
			_indents.push_back(index == 0 ? std::string("") : _indents[index - 1] + _indentString);

		printSub("", [&] {_stream << _libraryName;});
		printSub("", [] {});
		_inited = true;
	}
}

// Constructor
DebugTrace::DebugTrace(const char* funcName, const char* fileName, int lineNumber) noexcept {
	init();
	_funcName = funcName;

	if (_beforeNestLevel > _nestLevel)
		printSub("", [] {});

	printSub(_enterString, [&] {_stream << _enterString << _funcName;}, fileName, lineNumber);

	_beforeNestLevel = _nestLevel;
	++_nestLevel;
}

// Destructor
DebugTrace::~DebugTrace() noexcept {
	_beforeNestLevel = _nestLevel;
	--_nestLevel;

	printSub(_leaveString, [&] {_stream << _leaveString << _funcName;});
}

// Returns the space string of length corresponding to the current indentation.
const char* DebugTrace::indent() noexcept {
	return
		_indents[
			_nestLevel < 0 ? 0
			: _nestLevel < (int)_indents.size() ? _nestLevel
			: _indents.size() - 1
		].c_str();
}

// Outputs the date and time to stderr.
void DebugTrace::printDateTime() noexcept {
	std::time_t now = std::time(nullptr);
#if defined(_MSC_VER)
	// Visual C++
	struct std::tm dateTime;
	errno_t errno = localtime_s(&dateTime, &now);
	_stream
		                                     << dateTime.tm_year + 1900 << '-'
		<< std::setfill('0') << std::setw(2) << dateTime.tm_mon + 1     << '-'
		<< std::setfill('0') << std::setw(2) << dateTime.tm_mday        << ' '
		<< std::setfill('0') << std::setw(2) << dateTime.tm_hour        << ':'
		<< std::setfill('0') << std::setw(2) << dateTime.tm_min         << ':'
		<< std::setfill('0') << std::setw(2) << dateTime.tm_sec         << ' ';
#else
	// Other
	struct std::tm *dateTime = std::localtime(&now);
	_stream
		                                     << dateTime->tm_year + 1900 << '-'
		<< std::setfill('0') << std::setw(2) << dateTime->tm_mon + 1     << '-'
		<< std::setfill('0') << std::setw(2) << dateTime->tm_mday        << ' '
		<< std::setfill('0') << std::setw(2) << dateTime->tm_hour        << ':'
		<< std::setfill('0') << std::setw(2) << dateTime->tm_min         << ':'
		<< std::setfill('0') << std::setw(2) << dateTime->tm_sec         << ' ';
#endif
}

void DebugTrace::print(const char* message, const char* fileName, int lineNumber) noexcept {
	printSub(message, [] {}, fileName, lineNumber);
}

void DebugTrace::print(const char* name, bool value, const char* fileName, int lineNumber) noexcept {
	printValue(name, [&] {_stream << (value ? "true" : "false");}, fileName, lineNumber);
}

void DebugTrace::print(const char* name, char value, const char* fileName, int lineNumber) noexcept {
	printValue(name, [&] {_stream << value;}, fileName, lineNumber);
}

void DebugTrace::print(const char* name, unsigned char value, const char* fileName, int lineNumber) noexcept {
	printValue(name, [&] {_stream << value;}, fileName, lineNumber);
}

void DebugTrace::print(const char* name, short value, const char* fileName, int lineNumber) noexcept {
	printValue(name, [&] {_stream << value;}, fileName, lineNumber);
}

void DebugTrace::print(const char* name, unsigned short value, const char* fileName, int lineNumber) noexcept {
	printValue(name, [&] {_stream << value;}, fileName, lineNumber);
}

void DebugTrace::print(const char* name, int value, const char* fileName, int lineNumber) noexcept {
	printValue(name, [&] {_stream << value;}, fileName, lineNumber);
}

void DebugTrace::print(const char* name, unsigned int value, const char* fileName, int lineNumber) noexcept {
	printValue(name, [&] {_stream << value;}, fileName, lineNumber);
}

void DebugTrace::print(const char* name, long value, const char* fileName, int lineNumber) noexcept {
	printValue(name, [&] {_stream << value;}, fileName, lineNumber);
}

void DebugTrace::print(const char* name, unsigned long value, const char* fileName, int lineNumber) noexcept {
	printValue(name, [&] {_stream << value;}, fileName, lineNumber);
}

void DebugTrace::print(const char* name, long long value, const char* fileName, int lineNumber) noexcept {
	printValue(name, [&] {_stream << value;}, fileName, lineNumber);
}

void DebugTrace::print(const char* name, unsigned long long value, const char* fileName, int lineNumber) noexcept {
	printValue(name, [&] {_stream << value;}, fileName, lineNumber);
}

void DebugTrace::print(const char* name, float value, const char* fileName, int lineNumber) noexcept {
	printValue(name, [&] {_stream << value;}, fileName, lineNumber);
}

void DebugTrace::print(const char* name, double value, const char* fileName, int lineNumber) noexcept {
	printValue(name, [&] {_stream << value;}, fileName, lineNumber);
}

std::ostream& operator <<(std::ostream& stream, const std::string& string) noexcept {
	return stream << '"' << string.c_str() << '"';
}
