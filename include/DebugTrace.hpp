/// DebugTrace-hpp 1.1.0-beta2
/// (C) 2017 Masato Kokubo
#ifndef DBUEGTRACE_HPP_
#define DBUEGTRACE_HPP_

#if defined DEBUG || defined _DEBUG
    #define ENABLE_DEBUG_TRACE 1
#endif
#if defined ENABLE_DEBUG_TRACE
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
    #if defined _WIN32
        // Windows
        #include <windows.h>
    #endif
    #include <cuchar>

    #if defined CP_ACP // if Windows
        #define DEBUG_TRACE_STATIC \
            namespace debugtrace {\
            bool DebugTrace::_inited;\
            int DebugTrace::_codeNestLevel;\
            int DebugTrace::_beforeCodeNestLevel;\
            int DebugTrace::_dataNestLevel;\
            unsigned int DebugTrace::_codePage = CP_ACP;\
            } // namespace debugtrace
    #else
        #define DEBUG_TRACE_STATIC \
            namespace debugtrace {\
            bool DebugTrace::_inited;\
            int DebugTrace::_codeNestLevel;\
            int DebugTrace::_beforeCodeNestLevel;\
            int DebugTrace::_dataNestLevel;\
            } // namespace debugtrace
    #endif

    #if defined __PRETTY_FUNCTION__
        // GCC, Clang
        #define DEBUG_TRACE debugtrace::DebugTrace trace(__PRETTY_FUNCTION__, __FILE__, __LINE__);
    #elif defined __FUNCSIG__
        // Visual C++
        #define DEBUG_TRACE debugtrace::DebugTrace trace(__FUNCSIG__, __FILE__, __LINE__);
    #else
        // Others
        #define DEBUG_TRACE debugtrace::DebugTrace trace(__func__, __FILE__, __LINE__);
    #endif
    #define DEBUG_MESSAGE(message) debugtrace::DebugTrace::print(message, __FILE__, __LINE__);
    #define DEBUG_PRINT(var) debugtrace::DebugTrace::print(#var, var, __FILE__, __LINE__);
#else // defined ENABLE_DEBUG_TRACE
    #define DEBUG_TRACE_STATIC
    #define DEBUG_TRACE
    #define DEBUG_MESSAGE(message)
    #define DEBUG_PRINT(var)
#endif // defined ENABLE_DEBUG_TRACE

#if defined ENABLE_DEBUG_TRACE
namespace debugtrace {
/// A utility class for debugging.
/// Call DebugTrace.enter and DebugTrace.leave methods when enter and leave your methods,
/// then outputs execution trace of the program.
class DebugTrace {
private:

    static constexpr const char* libraryName       () {return "DebugTrace-cpp 1.1.0-beta2";}
    static constexpr const char* enterString       () {return "Enter ";}
    static constexpr const char* leaveString       () {return "Leave ";}
    static constexpr const char* codeIndentString  () {return "| ";}
    static constexpr const char* dataIndentString  () {return "  ";}
    static constexpr const char* startString       () {return "{";}
    static constexpr const char* endString         () {return "}";}
    static constexpr const char* delimiter         () {return ", ";}
    static constexpr const char* nameValueSeparator() {return " = ";}
    static constexpr const char* pairSeparator     () {return ":";}

    static const int _maxCodeIndents = 40;
    static const int _maxDataIndents = 40;
    static bool _inited;
    static std::ostream& stream() {return std::cerr;}
    static int _codeNestLevel;
    static int _beforeCodeNestLevel;
    static int _dataNestLevel;

    const char* _funcName = nullptr;

    static void init() noexcept {
        if (!_inited) {
            printSub([&] {stream() << libraryName();});
            printSub([] {});
            _inited = true;
        }
    }

    static unsigned int _codePage; // for Windows since 1.1.0

public:

    DebugTrace() = delete;
    DebugTrace(DebugTrace const&) = delete;

    /// Outputs a message when entering the function.
    /// @param funcName the function name
    /// @param fileName the source file name of the code that called this constructor
    /// @param lineNumber the line number of the code that called this function
    DebugTrace(const char funcName[], const char fileName[], int lineNumber) noexcept {
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
        // Others
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
    static void print(const char message[], const char fileName[], int lineNumber) noexcept {
        printSub([&] {stream() << message;}, fileName, lineNumber);
    }

    /// Outputs the name and a string representation of the object.
    /// @param name the name of the value
    /// @param value the value to output
    /// @param fileName the source file name of the code that called this function
    /// @param lineNumber the line number of the code that called this function
    template <typename T>
    static void print(const char name[], const T& value, const char fileName[], int lineNumber) noexcept {
        printSub([&] {
            stream() << name << nameValueSeparator();
            printValue(value);
        }, fileName, lineNumber);
    }

    /// Sets Windwos Code Page
    /// @param codePage the code page (e.g.: CP_ACP, CP_UTF8)
    /// @since 1.1.0
    static void setCodePage(unsigned int codePage) {
        _codePage = codePage;
    }

private:

    /// Outputs by outputer.
    /// @param outputer the output function
    /// @param fileName the source file name of the code that called this function
    /// @param lineNumber the line number of the code that called this function
    template <typename Function>
    static void printSub(Function outputer, const char fileName[] = "", int lineNumber = 0) noexcept {
        _dataNestLevel = 0;
        printDateTime();
        printIndent();

        outputer();

        if (fileName[0] != '\0') {
            const char *fileName2 = std::strrchr(fileName, '/');
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
    static void printType(const T& value) noexcept {
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
    /// @param pointer the pointer of the value to output
    /// @since 1.0.2
    template <typename T>
    static void printValue(T* pointer) noexcept {
        printType(pointer);
        if (pointer == nullptr)
            stream() << "nullptr";
        else {
            stream() << '&';
            printValue(*pointer);
        }
    }

    /// Outputs a string representation of the value.
    /// @param pointer the pointer of the value to output
    /// @since 1.0.1
    template <typename T>
    static void printValue(const T* pointer) noexcept {
        printType(pointer);
        if (pointer == nullptr)
            stream() << "nullptr";
        else {
            stream() << '&';
            printValue(*pointer);
        }
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    template <typename T>
    static void printValue(const T& value) noexcept {
        printType(value);
        stream() << value;
    }

    /// Outputs a string representation of the container object.
    /// @param container the container object to output
    template <class C>
    static void printContainer(const C& container) noexcept {
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
    static void printValue(const bool& value) noexcept {
        stream() << (value ? "true" : "false");
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    static void printValue(const char& value) noexcept {
        stream() << '\'' << value << '\'';
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    static void printValue(const signed char& value) noexcept {
        stream() << "(signed char)'" << value <<  '\'';
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    static void printValue(const unsigned char& value) noexcept {
        stream() << "(unsigned char)'" << value << '\'';
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    static void printValue(const short& value) noexcept {
        stream() << "(short)" << value;
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    static void printValue(const unsigned short& value) noexcept {
        stream() << "(unsigned short)" << value;
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    static void printValue(const int& value) noexcept {
        stream() << value;
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    static void printValue(const unsigned int& value) noexcept {
        stream() << value << 'u';
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    static void printValue(const long& value) noexcept {
        stream() << value << 'L';
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    static void printValue(const unsigned long& value) noexcept {
        stream() << value << "uL";
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    static void printValue(const long long& value) noexcept {
        stream() << value << "LL";
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    static void printValue(const unsigned long long& value) noexcept {
        stream() << value << "uLL";
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    static void printValue(const float& value) noexcept {
        stream() << value << 'F';
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    static void printValue(const double& value) noexcept {
        stream() << value;
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    static void printValue(const long double& value) noexcept {
        stream() << value << 'L';
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    /// @since 1.0.2
    static void printValue(const wchar_t& value) noexcept {
        stream() << "(wchar_t)" << value;
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    static void printValue(char* const& value) noexcept {
        if (value == nullptr)
            stream() << "(char*)nullptr";
        else
            stream() << "(char*)\"" << value << '"';
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    static void printValue(const char* const& value) noexcept {
        if (value == nullptr)
            stream() << "(const char*)nullptr";
        else
            stream() << "(const char*)\"" << value << '"';
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
    static void printValue(const signed char* const& value) noexcept {
        if (value == nullptr)
            stream() << "(const signed char*)nullptr";
        else
            stream() << "(const signed char*)\"" << value << '"';
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
    static void printValue(const unsigned char* const& value) noexcept {
        if (value == nullptr)
            stream() << "(const unsigned char*)nullptr";
        else
            stream() << "(const unsigned char*)\"" << value << '"';
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    /// @since 1.1.0
    static void printValue(wchar_t* const& value) noexcept {
        if (value == nullptr)
            stream() << "(wchar_t*)nullptr";
        else {
            auto string = to_string(std::wstring(value));
            stream() << "(wchar_t*)\"" << string.c_str() << '"';
        }
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    /// @since 1.1.0
    static void printValue(const wchar_t* const& value) noexcept {
        if (value == nullptr)
            stream() << "(const wchar_t*)nullptr";
        else {
            auto string = to_string(std::wstring(value));
            stream() << "(const wchar_t*)\"" << string.c_str() << '"';
        }
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    /// @since 1.1.0
    static void printValue(char16_t* const& value) noexcept {
        if (value == nullptr)
            stream() << "(char16_t*)nullptr";
        else {
            auto string = to_string(std::u16string(value));
            stream() << "(char16_t*)\"" << string.c_str() << '"';
        }
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    /// @since 1.1.0
    static void printValue(const char16_t* const& value) noexcept {
        if (value == nullptr)
            stream() << "(const char16_t*)nullptr";
        else {
            auto string = to_string(std::u16string(value));
            stream() << "(const char16_t*)\"" << string.c_str() << '"';
        }
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    /// @since 1.1.0
    static void printValue(char32_t* const& value) noexcept {
        if (value == nullptr)
            stream() << "(char32_t*)nullptr";
        else {
            auto string = to_string(std::u32string(value));
            stream() << "(char32_t*)\"" << string.c_str() << '"';
        }
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    /// @since 1.1.0
    static void printValue(const char32_t* const& value) noexcept {
        if (value == nullptr)
            stream() << "(const char32_t*)nullptr";
        else {
            auto string = to_string(std::u32string(value));
            stream() << "(const char32_t*)\"" << string.c_str() << '"';
        }
    }

#if defined __cpp_char8_t
    /// Outputs a string representation of the value.
    /// @param value the value to output
    /// @since 1.1.0
    static void printValue(char8_t* const& value) noexcept {
        if (value == nullptr)
            stream() << "(char8_t*)nullptr";
        else {
            auto string = to_string((std::u8string(value)));
            stream() << "(char8_t*)\"" << string.c_str() << '"';
        }
    }

   /// Outputs a string representation of the value.
    /// @param value the value to output
    /// @since 1.1.0
    static void printValue(const char8_t* const& value) noexcept {
        if (value == nullptr)
            stream() << "(const char8_t*)nullptr";
        else {
            auto string = to_string((std::u8string(value)));
            stream() << "(const char8_t*)\"" << string.c_str() << '"';
        }
    }
#endif

    /// Outputs a string representation of the value.
    /// @param value the value to output
    static void printValue(const std::string& value) noexcept {
        stream() << "(std::string)\"" << value.c_str() << '"';
    }

    /// Convert std::wstring to std::string.
    /// @param wstring the std::wstring
    /// @return a converted std::string
    /// @since 1.1.0
    static std::string to_string(const std::wstring& wstring) noexcept {
    #if defined _WIN32
        // Windows
        auto wstringLen = (int)wstring.length();
        auto stringLen = WideCharToMultiByte(_codePage, 0, wstring.c_str(), wstringLen, nullptr, 0, 0, 0);
        std::string string(stringLen, '\0');
        WideCharToMultiByte(_codePage, 0, wstring.c_str(), wstringLen, &string[0], stringLen, 0, 0);
        return string;
    #else
        // Non-Windows
        mbstate_t mbstate{};
        char char_buf[wstring.length() * sizeof(std::wstring::value_type) + 1];
        auto char_ptr = char_buf;
        for (auto wchar : wstring) {
            auto converted_count = wcrtomb(char_ptr, wchar, &mbstate);
            if (converted_count == (size_t)-1)
                return "<Cannot convert the wstring to string>";
            char_ptr += converted_count;
        }
        *char_ptr = '\0';
        return char_buf;        
    #endif
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    /// @since 1.1.0
    static void printValue(const std::wstring& value) noexcept {
        stream() << "(std::wstring)\"" << to_string(value).c_str() << '"';
    }

    /// Convert std::u16string to std::string.
    /// @param u16string the std::u16string
    /// @since 1.1.0
    static std::string to_string(const std::u16string& u16string) noexcept {
    #if defined _WIN32
        // Windows
        auto u16stringLen = (int)u16string.length();
        auto stringLen = WideCharToMultiByte(_codePage, 0, (LPCWCH)u16string.c_str(), u16stringLen, nullptr, 0, 0, 0);
        std::string string(stringLen, '\0');
        WideCharToMultiByte(_codePage, 0, (LPCWCH)u16string.c_str(), u16stringLen, &string[0], stringLen, 0, 0);
        return string;
    #else
        // Non-Windows
        mbstate_t mbstate{};
        char char_buf[u16string.length() * sizeof(std::u16string::value_type) + 1];
        auto char_ptr = char_buf;
        for (auto char16 : u16string) {
            auto converted_count = c16rtomb(char_ptr, char16, &mbstate);
            if (converted_count == (size_t)-1)
                return "<Cannot convert the u16string to string>";
            char_ptr += converted_count;
        }
        *char_ptr = '\0';
        return char_buf;        
    #endif
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    /// @since 1.1.0
    static void printValue(const std::u16string& value) noexcept {
        stream() << "(std::u16string)\"" << to_string(value).c_str() << '"';
    }

    /// Convert std::u32string to std::string.
    /// @param u32string the std::u32string
    /// @since 1.1.0
    static std::string to_string(const std::u32string& u32string) noexcept {
#if defined _WIN32
        return "<Unimplemented(string <- u32string)>";
#else
        mbstate_t mbstate{};
        char char_buf[u32string.length() * sizeof(std::u32string::value_type) + 1];
        auto char_ptr = char_buf;
        for (auto char32 : u32string) {
            auto converted_count = c32rtomb(char_ptr, char32, &mbstate);
            if (converted_count == (size_t)-1)
                return "<Cannot convert the u32string to string>";
            char_ptr += converted_count;
        }
        *char_ptr = '\0';
        return char_buf;        
#endif
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    /// @since 1.1.0
    static void printValue(const std::u32string& value) noexcept {
        stream() << "(std::u32string)\"" << to_string(value).c_str() << '"';
    }

#if defined __cpp_char8_t
    /// Convert std::u8string to std::string.
    /// @param u8string the std::u8string
    /// @since 1.1.0
    static std::string to_string(const std::u8string& u8string) noexcept {
    #if defined _WIN32
        // Windows
        if (_codePage == CP_UTF8)
            return std::string((const char *)u8string.c_str());

        auto u8stringLen = (int)u8string.length();
        auto wstringLen = MultiByteToWideChar(CP_UTF8, 0, (const char *)u8string.c_str(), u8stringLen, nullptr, 0);
        std::wstring wstring(wstringLen, '\0');
        MultiByteToWideChar(CP_UTF8, 0, (const char *)u8string.c_str(), u8stringLen, &wstring[0], wstringLen);

        auto stringLen = WideCharToMultiByte(_codePage, 0, wstring.c_str(), wstringLen, nullptr, 0, 0, 0);
        std::string string(stringLen, '\0');
        WideCharToMultiByte(_codePage, 0, wstring.c_str(), wstringLen, &string[0], stringLen, 0, 0);
        return string;
    #else
        // Non-Windows
        return std::string((const char *)u8string.c_str());
    #endif
    }

    /// Outputs a string representation of the value.
    /// @param value the value to output
    /// @since 1.1.0
    static void printValue(const std::u8string& value) noexcept {
        stream() << "(std::u8string)\"" << to_string(value).c_str() << '"';
    }
#endif

    /// Outputs a string representation of the value.
    /// @param value the value to output
    template <typename T1, typename T2>
    static void printValue(const std::pair<T1, T2>& value) noexcept {
        stream() << value.first << pairSeparator() << value.second;
    }

    /// Outputs a string representation of the container object.
    /// @param container the container object to output
    template <typename T, size_t N>
    static void printValue(const std::array<T, N>& container) noexcept {
        printContainer(container);
    }

    /// Outputs a string representation of the container object.
    /// @param container the container object to output
    template <typename T, class Allocator = std::allocator<T>>
    static void printValue(const std::deque<T, Allocator>& container) noexcept {
        printContainer(container);
    }

    /// Outputs a string representation of the container object.
    /// @param container the container object to output
    template <typename T, class Allocator = std::allocator<T>>
    static void printValue(const std::list<T, Allocator>& container) noexcept {
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
    static void printValue(const std::map<Key, T, Compare, Allocator>& container) noexcept {
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
    static void printValue(const std::multimap<Key, T, Compare, Allocator>& container) noexcept {
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
    static void printValue(const std::unordered_map<Key, T, Hash, Pred, Allocator>& container) noexcept {
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
    static void printValue(const std::unordered_multimap<Key, T, Hash, Pred, Allocator>& container) noexcept {
        printContainer(container);
    }

    /// Outputs a string representation of the container object.
    /// @param container the container object to output
    template <
        typename Key,
        class Compare = std::less<Key>,
        class Allocator = std::allocator<Key>
    >
    static void printValue(const std::set<Key, Compare, Allocator>& container) noexcept {
        printContainer(container);
    }

    /// Outputs a string representation of the container object.
    /// @param container the container object to output
    template <
        typename Key,
        class Compare = std::less<Key>,
        class Allocator = std::allocator<Key>
    >
    static void printValue(const std::multiset<Key, Compare, Allocator>& container) noexcept {
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
    static void printValue(const std::unordered_set<Key, Hash, Pred, Allocator>& container) noexcept {
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
    static void printValue(const std::unordered_multiset<Key, Hash, Pred, Allocator>& container) noexcept {
        printContainer(container);
    }

    /// Outputs a string representation of the container object.
    /// @param container the container object to output
    template <typename T, class Allocator = std::allocator<T>>
    static void printValue(const std::vector<T, Allocator>& container) noexcept {
        printContainer(container);
    }
};

} // namespace debugtrace

#endif // defined ENABLE_DEBUG_TRACE
#endif // ifndef DBUEGTRACE_HPP_
