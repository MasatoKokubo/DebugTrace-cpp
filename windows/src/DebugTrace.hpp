// DebugTrace.hpp
//
// (C) 2017 Masato Kokubo
#pragma once
#if defined _MSC_VER
	#pragma message("    include DebugTrace.hpp start")
#endif

#if defined DEBUG || defined _DEBUG
	#define ENABLE_DEBUGTRACE 1
#endif
#if defined ENABLE_DEBUGTRACE
	#include <algorithm>
	#include <array>
	#include <deque>
	#include <iostream>
	#include <list>
	#include <map>
	#include <memory>
	#include <set>
	#if defined _MSC_VER
		#include <string>
	#else
		namespace std {
			#include <string.h>
		}
		#include <cxxabi.h> // abi::__cxa_demangle()
	#endif
	#include <unordered_map>
	#include <unordered_set>
	#include <vector>

	#define DEBUG_TRACE(func) debugtrace::DebugTrace trace(func, __FILE__, __LINE__)
	#define DEBUG_MESSAGE(message) debugtrace::DebugTrace::print(message, __FILE__, __LINE__)
	#define DEBUG_PRINT(var) debugtrace::DebugTrace::print(#var, var, __FILE__, __LINE__)
#else
	#define DEBUG_TRACE(func)
	#define DEBUG_MESSAGE(message)
	#define DEBUG_PRINT(var)
#endif

#if defined ENABLE_DEBUGTRACE
namespace debugtrace {
	/**
	* A utility class for debugging.
	* Call DebugTrace.enter and DebugTrace.leave methods when enter and leave your methods,
	* then outputs execution trace of the program.
	*
	* @author Masato Kokubo
	*/
	class DebugTrace {
		private:
			// The library name and version c-string
			static const char* _libraryName;

			// The enter c-string
			static const char* _enterString;

			// The leave c-string
			static const char* _leaveString;

			// The separator c-string of name and value
			static const char* _separator;

			// The indent c-string
			static const char* _indentString;

			// Max indents
			static const size_t _maxIndents;

			// The initialized flag
			static bool _inited;

			// Array of indent strings
			static std::vector<std::string> _indents;

			// The output stream
			static std::ostream& _stream;

			// The nest level
			static int _nestLevel;

			// The before nest Leval
			static int _beforeNestLevel;

			// Function name
			const char* _funcName = nullptr;

			/**
			 * Initializes this library.
			 */
			static void init() noexcept;

		public:
			/// No default constructor
			DebugTrace() = delete;

			/// No copy constructor
			DebugTrace(const DebugTrace&) = delete;

			/**
			 * Outputs a message when entering the function.
			 *
			 * @param funcName the function name
			 * @param fileName the source file name of the code that called this constructor
			 * @param lineNumber the line number of the code that called this function
			 */
			DebugTrace(const char* funcName, const char* fileName, int lineNumber) noexcept;

			/// Outputs a message when leaving the function
			~DebugTrace() noexcept;

			/// No assignment operator.
			DebugTrace& operator =(const DebugTrace&) = delete;

			/**
			 * Returns the space string of length corresponding to the current indentation.
			 *
			 * @return the space string of length corresponding to the current indentation.
			 */
			static const char* indent() noexcept;

		private:
			/// Outputs the date and time to stderr.
			static void printDateTime() noexcept;

			/**
			 * Outputs the message to stderr.
			 *
			 * @param outputer the output function
			 * @param fileName the source file name of the code that called this function
			 * @param lineNumber the line number of the code that called this function
			 */
			template <typename Function>
			static void printSub(Function outputer, const char* fileName = nullptr, int lineNumber = 0) noexcept {
				printDateTime();
				_stream << indent();
				outputer();

				if (fileName != nullptr) {
					const char *fileName2 = std::strrchr(fileName, '/');
					if (fileName2 == nullptr) {
						fileName2 = std::strrchr(fileName, '\\');
						if (fileName2 == nullptr)
							fileName2 = fileName;
						else
							++fileName2;
					} else
						++fileName2;

					_stream << " (" << fileName2 << ':' << lineNumber << ')';
				}

				_stream << std::endl;
			}

			/**
			 * Outputs the name and value to stderr.
			 *
			 * @param name the name
			 * @param outputer the output function of the value
			 * @param fileName the source file name of the code that called this function
			 * @param lineNumber the line number of the code that called this function
			 */
			template <typename Function>
			static void printValue(const char* name, Function outputer, const char* fileName, int lineNumber) noexcept {
				printSub([&] {_stream << name << " = "; outputer();}, fileName, lineNumber);
			}

		public:
			/**
			 * Outputs the message to stderr.
			 *
			 * @param message the message
			 * @param fileName the source file name of the code that called this function
			 * @param lineNumber the line number of the code that called this function
			 */
			static void print(const char* message, const char* fileName, int lineNumber) noexcept;

			/**
			 * Outputs the name and a string representation of the value to stderr.
			 *
			 * @param name the name of the value
			 * @param value the value to output
			 * @param fileName the source file name of the code that called this function
			 * @param lineNumber the line number of the code that called this function
			 */
			static void print(const char* name, bool value, const char* fileName, int lineNumber) noexcept;

			/**
			 * Outputs the name and a string representation of the value to stderr.
			 *
			 * @param name the name of the value
			 * @param value the value to output
			 * @param fileName the source file name of the code that called this function
			 * @param lineNumber the line number of the code that called this function
			 */
			static void print(const char* name, char value, const char* fileName, int lineNumber) noexcept;

			/**
			 * Outputs the name and a string representation of the value to stderr.
			 *
			 * @param name the name of the value
			 * @param value the value to output
			 * @param fileName the source file name of the code that called this function
			 * @param lineNumber the line number of the code that called this function
			 */
			static void print(const char* name, unsigned char value, const char* fileName, int lineNumber) noexcept;

			/**
			 * Outputs the name and a string representation of the value to stderr.
			 *
			 * @param name the name of the value
			 * @param value the value to output
			 * @param fileName the source file name of the code that called this function
			 * @param lineNumber the line number of the code that called this function
			 */
			static void print(const char* name, short value, const char* fileName, int lineNumber) noexcept;

			/**
			 * Outputs the name and a string representation of the value to stderr.
			 *
			 * @param name the name of the value
			 * @param value the value to output
			 * @param fileName the source file name of the code that called this function
			 * @param lineNumber the line number of the code that called this function
			 */
			static void print(const char* name, unsigned short value, const char* fileName, int lineNumber) noexcept;

			/**
			 * Outputs the name and a string representation of the value to stderr.
			 *
			 * @param name the name of the value
			 * @param value the value to output
			 * @param fileName the source file name of the code that called this function
			 * @param lineNumber the line number of the code that called this function
			 */
			static void print(const char* name, int value, const char* fileName, int lineNumber) noexcept;

			/**
			 * Outputs the name and a string representation of the value to stderr.
			 *
			 * @param name the name of the value
			 * @param value the value to output
			 * @param fileName the source file name of the code that called this function
			 * @param lineNumber the line number of the code that called this function
			 */
			static void print(const char* name, unsigned int value, const char* fileName, int lineNumber) noexcept;

			/**
			 * Outputs the name and a string representation of the value to stderr.
			 *
			 * @param name the name of the value
			 * @param value the value to output
			 * @param fileName the source file name of the code that called this function
			 * @param lineNumber the line number of the code that called this function
			 */
			static void print(const char* name, long value, const char* fileName, int lineNumber) noexcept;

			/**
			 * Outputs the name and a string representation of the value to stderr.
			 *
			 * @param name the name of the value
			 * @param value the value to output
			 * @param fileName the source file name of the code that called this function
			 * @param lineNumber the line number of the code that called this function
			 */
			static void print(const char* name, unsigned long value, const char* fileName, int lineNumber) noexcept;

			/**
			 * Outputs the name and a string representation of the value to stderr.
			 *
			 * @param name the name of the value
			 * @param value the value to output
			 * @param fileName the source file name of the code that called this function
			 * @param lineNumber the line number of the code that called this function
			 */
			static void print(const char* name, long long value, const char* fileName, int lineNumber) noexcept;

			/**
			 * Outputs the name and a string representation of the value to stderr.
			 *
			 * @param name the name of the value
			 * @param value the value to output
			 * @param fileName the source file name of the code that called this function
			 * @param lineNumber the line number of the code that called this function
			 */
			static void print(const char* name, unsigned long long value, const char* fileName, int lineNumber) noexcept;

			/**
			 * Outputs the name and a string representation of the value to stderr.
			 *
			 * @param name the name of the value
			 * @param value the value to output
			 * @param fileName the source file name of the code that called this function
			 * @param lineNumber the line number of the code that called this function
			 */
			static void print(const char* name, float value, const char* fileName, int lineNumber) noexcept;

			/**
			 * Outputs the name and a string representation of the value to stderr.
			 *
			 * @param name the name of the value
			 * @param value the value to output
			 * @param fileName the source file name of the code that called this function
			 * @param lineNumber the line number of the code that called this function
			 */
			static void print(const char* name, double value, const char* fileName, int lineNumber) noexcept;

			/**
			 * Outputs the name and a string representation of the value to stderr.
			 *
			 * @param name the name of the value
			 * @param value the value to output
			 * @param fileName the source file name of the code that called this function
			 * @param lineNumber the line number of the code that called this function
			 */
			static void print(const char* name, const char* value, const char* fileName, int lineNumber) noexcept;

			/**
			 * Outputs the name and a string representation of the value to stderr.
			 *
			 * @param name the name of the value
			 * @param value the value to output
			 * @param fileName the source file name of the code that called this function
			 * @param lineNumber the line number of the code that called this function
			 */
			static void print(const char* name, const std::string& value, const char* fileName, int lineNumber) noexcept;

			/**
			 * Outputs the message and a string representation of the object to stderr.
			 *
			 * @param name the name of the value
			 * @param object the object to output
			 * @param fileName the source file name of the code that called this function
			 * @param lineNumber the line number of the code that called this function
			 */
			template <typename T>
			static void print(const char* name, const T& object, const char* fileName, int lineNumber) noexcept {
				printValue(name, [&] {
				#if defined _MSC_VER
					_stream << '(' << typeid(object).name() << ')' << object;
				#else
					int status;
					char* typeName = abi::__cxa_demangle(typeid(object).name(), nullptr, nullptr, &status);
					_stream << '(' << (typeName == nullptr ? "?" : typeName) << ')' << object;
					if (typeName != nullptr)
						free(typeName);
				#endif
				}, fileName, lineNumber);
			}
	};
}

/**
 * Outputs the string to the output stream.
 *
 * @param stream the output stream
 * @param string the string to output
 */
std::ostream& operator <<(std::ostream& stream, const std::string& string) noexcept;

/**
 * Outputs the pair to the output stream.
 *
 * @param stream the output stream
 * @param pair the pair to output
 */
template <class T1, class T2>
std::ostream& operator <<(std::ostream& stream, const std::pair<T1, T2>& pair) noexcept {
	return stream << pair.first << ":" << pair.second;
}

/**
 * Outputs the message and the array to stderr.
 *
 * @param stream the output stream
 * @param array the array to output
 */
template <class T, size_t N>
std::ostream& operator <<(std::ostream& stream, const std::array<T, N>& array) noexcept {
	stream << '[';

	auto delimiter = "";
	std::for_each(array.cbegin(), array.cend(),
		[&](const T& element) {
			stream << delimiter << element;
			delimiter = ", ";
		}
	);

	return stream << ']';
}

/**
 * Outputs the deque to the output stream.
 *
 * @param stream the output stream
 * @param deque the deque to output
 */
template <class T, class Allocator = std::allocator<T>>
std::ostream& operator <<(std::ostream& stream, const std::deque<T, Allocator>& deque) noexcept {
	stream << '[';

	auto delimiter = "";
	std::for_each(deque.cbegin(), deque.cend(),
		[&](const T& element) {
			stream << delimiter << element;
			delimiter = ", ";
		}
	);

	return stream << ']';
}

/**
 * Outputs the list to the output stream.
 *
 * @param stream the output stream
 * @param list the list to output
 */
template <class T, class Allocator = std::allocator<T>>
std::ostream& operator <<(std::ostream& stream, const std::list<T, Allocator>& list) noexcept {
	stream << '[';

	auto delimiter = "";
	std::for_each(list.cbegin(), list.cend(),
		[&](const T& element) {
			stream << delimiter << element;
			delimiter = ", ";
		}
	);

	return stream << ']';
}

/**
 * Outputs the map to the output stream.
 *
 * @param stream the output stream
 * @param map the map to output
 */
template <
	class Key,
	class T,
	class Compare = std::less<Key>,
	class Allocator = std::allocator<std::pair<const Key, T>>
>
std::ostream& operator <<(std::ostream& stream, const std::map<Key, T, Compare, Allocator>& map) noexcept {
	stream << '[';

	auto delimiter = "";
	std::for_each(map.cbegin(), map.cend(),
		[&](const std::pair<Key, T>& element) {
			stream << delimiter << element;
			delimiter = ", ";
		}
	);

	return stream << ']';
}

/**
 * Outputs the multimap to the output stream.
 *
 * @param stream the output stream
 * @param map the map to output
 */
template <
	class Key,
	class T,
	class Compare = std::less<Key>,
	class Allocator = std::allocator<std::pair<const Key, T>>
>
std::ostream& operator <<(std::ostream& stream, const std::multimap<Key, T, Compare, Allocator>& map) noexcept {
	stream << '[';

	auto delimiter = "";
	std::for_each(map.cbegin(), map.cend(),
		[&](const std::pair<Key, T>& element) {
			stream << delimiter << element;
			delimiter = ", ";
		}
	);

	return stream << ']';
}

/**
 * Outputs the unordered_map to the output stream.
 *
 * @param stream the output stream
 * @param map the unordered_map to output
 */
template <
	class Key,
	class T,
	class Hash = std::hash<Key>,
	class Pred = std::equal_to<Key>,
	class Allocator = std::allocator<std::pair<const Key, T>>
>
std::ostream& operator <<(std::ostream& stream, const std::unordered_map<Key, T, Hash, Pred, Allocator>& map) noexcept {
	stream << '[';

	auto delimiter = "";
	std::for_each(map.cbegin(), map.cend(),
		[&](const std::pair<Key, T>& element) {
			stream << delimiter << element;
			delimiter = ", ";
		}
	);

	return stream << ']';
}

/**
 * Outputs the unordered_multimap to the output stream.
 *
 * @param stream the output stream
 * @param map the unordered_map to output
 */
template <
	class Key,
	class T,
	class Hash = std::hash<Key>,
	class Pred = std::equal_to<Key>,
	class Allocator = std::allocator<std::pair<const Key, T>>
>
std::ostream& operator <<(std::ostream& stream, const std::unordered_multimap<Key, T, Hash, Pred, Allocator>& map) noexcept {
	stream << '[';

	auto delimiter = "";
	std::for_each(map.cbegin(), map.cend(),
		[&](const std::pair<Key, T>& element) {
			stream << delimiter << element;
			delimiter = ", ";
		}
	);

	return stream << ']';
}

/**
 * Outputs the set to the output stream.
 *
 * @param stream the output stream
 * @param set the set to output
 */
template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key>>
std::ostream& operator <<(std::ostream& stream, const std::set<Key, Compare, Allocator>& set) noexcept {
	stream << '[';

	auto delimiter = "";
	std::for_each(set.cbegin(), set.cend(),
		[&](const Key& element) {
			stream << delimiter << element;
			delimiter = ", ";
		}
	);

	return stream << ']';
}

/**
 * Outputs the multiset to the output stream.
 *
 * @param stream the output stream
 * @param set the set to output
 */
template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key>>
std::ostream& operator <<(std::ostream& stream, const std::multiset<Key, Compare, Allocator>& set) noexcept {
	stream << '[';

	auto delimiter = "";
	std::for_each(set.cbegin(), set.cend(),
		[&](const Key& element) {
			stream << delimiter << element;
			delimiter = ", ";
		}
	);

	return stream << ']';
}

/**
 * Outputs the unordered_set to the output stream.
 *
 * @param stream the output stream
 * @param set the unordered_set to output
 */
template <
	class Key,
	class Hash = std::hash<Key>,
	class Pred = std::equal_to<Key>,
	class Allocator = std::allocator<Key>
>
std::ostream& operator <<(std::ostream& stream, const std::unordered_set<Key, Hash, Pred, Allocator>& set) noexcept {
	stream << '[';

	auto delimiter = "";
	std::for_each(set.cbegin(), set.cend(),
		[&](const Key& element) {
			stream << delimiter << element;
			delimiter = ", ";
		}
	);

	return stream << ']';
}

/**
 * Outputs the unordered_multiset to the output stream.
 *
 * @param stream the output stream
 * @param set the unordered_set to output
 */
template <
	class Key,
	class Hash = std::hash<Key>,
	class Pred = std::equal_to<Key>,
	class Allocator = std::allocator<Key>
>
std::ostream& operator <<(std::ostream& stream, const std::unordered_multiset<Key, Hash, Pred, Allocator>& set) noexcept {
	stream << '[';

	auto delimiter = "";
	std::for_each(set.cbegin(), set.cend(),
		[&](const Key& element) {
			stream << delimiter << element;
			delimiter = ", ";
		}
	);

	return stream << ']';
}

/**
 * Outputs the vector to the output stream.
 *
 * @param stream the output stream
 * @param vector the vector to output
 */
template <class T, class Allocator = std::allocator<T>>
std::ostream& operator <<(std::ostream& stream, const std::vector<T, Allocator>& vector) noexcept {
	stream << '[';

	auto delimiter = "";
	std::for_each(vector.cbegin(), vector.cend(),
		[&](const T& element) {
			stream << delimiter << element;
			delimiter = ", ";
		}
	);

	return stream << "]";
}
#endif

#if defined _MSC_VER
	#pragma message("    include DebugTrace.hpp end")
#endif
