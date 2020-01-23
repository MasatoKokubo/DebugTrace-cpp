#pragma once
/// debugtrace.hpp
/// (C) 2017 Masato Kokubo
#if defined DEBUG || defined _DEBUG
    #define DEBUGTRACE_ENABLED 1
#endif
#ifdef DEBUGTRACE_ENABLED
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
    #ifdef __GNUC__
        #include <cxxabi.h> // abi::__cxa_demangle()
    #endif
    #include <unordered_map>
    #include <unordered_set>
    #include <vector>
    #ifdef _WIN32
        #include <windows.h>
    #endif
    #include <cuchar>

    #ifdef __cpp_inline_variables
        #define DEBUGTRACE_VARIABLES
    #else
        #define DEBUGTRACE_VARIABLES \
            namespace debugtrace {\
            const char* const library_name   = "DebugTrace-cpp 2.0.0a1";\
            const char* enter_string         = "Enter ";\
            const char* leave_string         = "Leave ";\
            const char* code_indent_string   = "| ";\
            const char* data_indent_string   = "  ";\
            const char* start_string         = "{";\
            const char* end_string           = "}";\
            const char* delimiter            = ", ";\
            const char* name_value_separator = " = ";\
            const char* pair_separator       = ":";\
            const int _max_code_indents = 20;\
            const int _max_data_indents = 20;\
            bool _initialized;\
            std::ostream& stream = std::cerr;\
            int _code_nest_level;\
            int _before_code_nest_level;\
            int _data_nest_level;\
            unsigned int _code_page = 65001\
            }
    #endif // __cpp_inline_variables

    #ifdef __PRETTY_FUNCTION__
        // GCC, Clang
        #define DEBUGTRACE_ENTER debugtrace::DebugTrace trace(__PRETTY_FUNCTION__, __FILE__, __LINE__);
    #elif defined __FUNCSIG__
        // Visual C++
        #define DEBUGTRACE_ENTER debugtrace::DebugTrace trace(__FUNCSIG__, __FILE__, __LINE__);
    #else
        // Others
        #define DEBUGTRACE_ENTER debugtrace::DebugTrace trace(__func__, __FILE__, __LINE__);
    #endif // __PRETTY_FUNCTION__
    #define DEBUGTRACE_MESSAGE(message) debugtrace::print(message, __FILE__, __LINE__);
    #define DEBUGTRACE_PRINT(var) debugtrace::print(#var, var, __FILE__, __LINE__);
#else
    #define DEBUGTRACE_VARIABLES
    #define DEBUGTRACE_ENTER
    #define DEBUGTRACE_MESSAGE(message)
    #define DEBUGTRACE_PRINT(var)
#endif // DEBUGTRACE_ENABLED

#ifdef DEBUGTRACE_ENABLED
namespace debugtrace {
#ifdef __cpp_inline_variables
    inline const char* const library_name   = "DebugTrace-cpp 2.0.0a1";
    inline const char* enter_string         = "Enter ";
    inline const char* leave_string         = "Leave ";
    inline const char* code_indent_string   = "| ";
    inline const char* data_indent_string   = "  ";
    inline const char* start_string         = "{";
    inline const char* end_string           = "}";
    inline const char* delimiter            = ", ";
    inline const char* name_value_separator = " = ";
    inline const char* pair_separator       = ":";
    inline const int _max_code_indents = 20;
    inline const int _max_data_indents = 20;
    inline bool _initialized;
    inline std::ostream& stream = std::cerr;
    inline int _code_nest_level;
    inline int _before_code_nest_level;
    inline int _data_nest_level;
    inline unsigned int _code_page = 65001; // UTF-8
#else
    extern const char* const library_name;
    extern const char* enter_string;
    extern const char* leave_string;
    extern const char* code_indent_string;
    extern const char* data_indent_string;
    extern const char* start_string;
    extern const char* end_string;
    extern const char* delimiter;
    extern const char* name_value_separator;
    extern const char* pair_separator;
    extern const int _max_code_indents;
    extern const int _max_data_indents;
    extern bool _initialized;
    extern std::ostream& stream;
    extern int _code_nest_level;
    extern int _before_code_nest_level;
    extern int _data_nest_level;
    extern unsigned int _code_page;
#endif // __cpp_inline_variables

/// Outputs charasters for indent.
inline void _print_indent() noexcept {
    for (int index = 0; index < _code_nest_level; ++index)
        stream << code_indent_string;

    for (int index = 0; index < _data_nest_level; ++index)
        stream << data_indent_string;
}

/// Outputs the date and time.
inline void _print_datetime() noexcept {
    auto now = std::time(nullptr);
#ifdef _MSC_VER
    // Visual C++
    struct std::tm date_time;
    localtime_s(&date_time, &now);
#else
    // Others
    auto date_time = *std::localtime(&now);
#endif // _MSC_VER
    stream
                                             << date_time.tm_year + 1900 << '-'
        << std::setfill('0') << std::setw(2) << date_time.tm_mon + 1     << '-'
        << std::setfill('0') << std::setw(2) << date_time.tm_mday        << ' '
        << std::setfill('0') << std::setw(2) << date_time.tm_hour        << ':'
        << std::setfill('0') << std::setw(2) << date_time.tm_min         << ':'
        << std::setfill('0') << std::setw(2) << date_time.tm_sec         << ' ';
}

/// Outputs by outputer.
/// @param outputer the output function
/// @param file_name the source file name of the code that called this function
/// @param line_number the line number of the code that called this function
template <typename Function>
inline void _print_sub(Function outputer, const char file_name[] = "", int line_number = 0) noexcept {
    _data_nest_level = 0;
    _print_datetime();
    _print_indent();

    outputer();

    if (file_name[0] != '\0') {
        const char *file_name2 = std::strrchr(file_name, '/');
        if (file_name2 == nullptr) {
            file_name2 = std::strrchr(file_name, '\\');
            if (file_name2 == nullptr)
                file_name2 = file_name;
            else
                ++file_name2;
        } else
            ++file_name2;

        stream << " (" << file_name2 << pair_separator << line_number << ')';
    }

    stream << std::endl;
}

/// Outputs the message.
/// @param message the message
/// @param file_name the source file name of the code that called this function
/// @param line_number the line number of the code that called this function
inline void print(const char message[], const char file_name[], int line_number) noexcept {
    _print_sub([&] {stream << message;}, file_name, line_number);
}

/// Sets Windwos Code Page
/// @param codePage the code page (e.g.: CP_ACP, CP_UTF8)
/// @since 1.1.0
inline void set_code_page(unsigned int codePage) {
    _code_page = codePage;
}

/// Outputs a string representation of the type of the value.
/// @param value the value to output
template <typename T>
inline void _print_type(const T& value) noexcept {
#ifdef _MSC_VER
    stream << '(' << typeid(value).name() << ')';
#else
    int status;
    char* type_name = abi::__cxa_demangle(typeid(value).name(), nullptr, nullptr, &status);
    stream << '(' << (type_name == nullptr ? "?" : type_name) << ')';
    if (type_name != nullptr)
        free(type_name);
#endif // _MSC_VER
}

/// Outputs for line feed.
inline void _print_next_line() noexcept {
    stream << std::endl;
    _print_datetime();
    _print_indent();
}

/// Outputs a string representation of the value.
/// @param value the value to output
inline void print_value(const bool& value) noexcept {
    stream << (value ? "true" : "false");
}

/// Outputs a string representation of the value.
/// @param value the value to output
inline void print_value(const char& value) noexcept {
    stream << '\'' << value << '\'';
}

/// Outputs a string representation of the value.
/// @param value the value to output
inline void print_value(const signed char& value) noexcept {
    stream << "(signed char)'" << value <<  '\'';
}

/// Outputs a string representation of the value.
/// @param value the value to output
inline void print_value(const unsigned char& value) noexcept {
    stream << "(unsigned char)'" << value << '\'';
}

/// Outputs a string representation of the value.
/// @param value the value to output
inline void print_value(const short& value) noexcept {
    stream << "(short)" << value;
}

/// Outputs a string representation of the value.
/// @param value the value to output
inline void print_value(const unsigned short& value) noexcept {
    stream << "(unsigned short)" << value;
}

/// Outputs a string representation of the value.
/// @param value the value to output
inline void print_value(const int& value) noexcept {
    stream << value;
}

/// Outputs a string representation of the value.
/// @param value the value to output
inline void print_value(const unsigned int& value) noexcept {
    stream << value << 'u';
}

/// Outputs a string representation of the value.
/// @param value the value to output
inline void print_value(const long& value) noexcept {
    stream << value << 'L';
}

/// Outputs a string representation of the value.
/// @param value the value to output
inline void print_value(const unsigned long& value) noexcept {
    stream << value << "uL";
}

/// Outputs a string representation of the value.
/// @param value the value to output
inline void print_value(const long long& value) noexcept {
    stream << value << "LL";
}

/// Outputs a string representation of the value.
/// @param value the value to output
inline void print_value(const unsigned long long& value) noexcept {
    stream << value << "uLL";
}

/// Outputs a string representation of the value.
/// @param value the value to output
inline void print_value(const float& value) noexcept {
    stream << value << 'F';
}

/// Outputs a string representation of the value.
/// @param value the value to output
inline void print_value(const double& value) noexcept {
    stream << value;
}

/// Outputs a string representation of the value.
/// @param value the value to output
inline void print_value(const long double& value) noexcept {
    stream << value << 'L';
}

/// Outputs a string representation of the value.
/// @param value the value to output
/// @since 1.0.2
inline void print_value(const wchar_t& value) noexcept {
    stream << "(wchar_t)" << value;
}

/// Outputs a string representation of the value.
/// @param value the value to output
inline void print_value(char* const& value) noexcept {
    if (value == nullptr)
        stream << "(char*)nullptr";
    else
        stream << "(char*)\"" << value << '"';
}

/// Outputs a string representation of the value.
/// @param value the value to output
inline void print_value(const char* const& value) noexcept {
    if (value == nullptr)
        stream << "(const char*)nullptr";
    else
        stream << "(const char*)\"" << value << '"';
}


/// Outputs a string representation of the value.
/// @param value the value to output
inline void print_value(signed char* const& value) noexcept {
    if (value == nullptr)
        stream << "(signed char*)nullptr";
    else
        stream << "(signed char*)\"" << value << '"';
}

/// Outputs a string representation of the value.
/// @param value the value to output
inline void print_value(const signed char* const& value) noexcept {
    if (value == nullptr)
        stream << "(const signed char*)nullptr";
    else
        stream << "(const signed char*)\"" << value << '"';
}

/// Outputs a string representation of the value.
/// @param value the value to output
inline void print_value(unsigned char* const& value) noexcept {
    if (value == nullptr)
        stream << "(unsigned char*)nullptr";
    else
        stream << "(unsigned char*)\"" << value << '"';
}

/// Outputs a string representation of the value.
/// @param value the value to output
inline void print_value(const unsigned char* const& value) noexcept {
    if (value == nullptr)
        stream << "(const unsigned char*)nullptr";
    else
        stream << "(const unsigned char*)\"" << value << '"';
}

/// Convert std::wstring to std::string.
/// @param wstring the std::wstring
/// @return a converted std::string
/// @since 1.1.0
inline std::string to_string(const std::wstring& wstring) noexcept {
#ifdef _WIN32
    auto wstringLen = (int)wstring.length();
    auto stringLen = WideCharToMultiByte(_code_page, 0, wstring.c_str(), wstringLen, nullptr, 0, 0, 0);
    std::string string(stringLen, '\0');
    WideCharToMultiByte(_code_page, 0, wstring.c_str(), wstringLen, &string[0], stringLen, 0, 0);
    return string;
#else
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
#endif // _WIN32
}

/// Outputs a string representation of the value.
/// @param value the value to output
/// @since 1.1.0
inline void print_value(wchar_t* const& value) noexcept {
    if (value == nullptr)
        stream << "(wchar_t*)nullptr";
    else {
        auto string = to_string(std::wstring(value));
        stream << "(wchar_t*)\"" << string.c_str() << '"';
    }
}

/// Outputs a string representation of the value.
/// @param value the value to output
/// @since 1.1.0
inline void print_value(const wchar_t* const& value) noexcept {
    if (value == nullptr)
        stream << "(const wchar_t*)nullptr";
    else {
        auto string = to_string(std::wstring(value));
        stream << "(const wchar_t*)\"" << string.c_str() << '"';
    }
}

/// Convert std::u16string to std::string.
/// @param u16string the std::u16string
/// @since 1.1.0
inline std::string to_string(const std::u16string& u16string) noexcept {
#ifdef _WIN32
    auto u16stringLen = (int)u16string.length();
    auto stringLen = WideCharToMultiByte(_code_page, 0, (LPCWCH)u16string.c_str(), u16stringLen, nullptr, 0, 0, 0);
    std::string string(stringLen, '\0');
    WideCharToMultiByte(_code_page, 0, (LPCWCH)u16string.c_str(), u16stringLen, &string[0], stringLen, 0, 0);
    return string;
#else
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
#endif // _WIN32
}

/// Outputs a string representation of the value.
/// @param value the value to output
/// @since 1.1.0
inline void print_value(const std::u16string& value) noexcept {
    stream << "(std::u16string)\"" << to_string(value).c_str() << '"';
}

/// Outputs a string representation of the value.
/// @param value the value to output
/// @since 1.1.0
inline void print_value(char16_t* const& value) noexcept {
    if (value == nullptr)
        stream << "(char16_t*)nullptr";
    else {
        auto string = to_string(std::u16string(value));
        stream << "(char16_t*)\"" << string.c_str() << '"';
    }
}

/// Outputs a string representation of the value.
/// @param value the value to output
/// @since 1.1.0
inline void print_value(const char16_t* const& value) noexcept {
    if (value == nullptr)
        stream << "(const char16_t*)nullptr";
    else {
        auto string = to_string(std::u16string(value));
        stream << "(const char16_t*)\"" << string.c_str() << '"';
    }
}

/// Convert std::u32string to std::string.
/// @param u32string the std::u32string
/// @since 1.1.0
inline std::string to_string(const std::u32string& u32string) noexcept {
#ifdef _WIN32
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
#endif // _WIN32
}

/// Outputs a string representation of the value.
/// @param value the value to output
/// @since 1.1.0
inline void print_value(const std::u32string& value) noexcept {
    stream << "(std::u32string)\"" << to_string(value).c_str() << '"';
}

/// Outputs a string representation of the value.
/// @param value the value to output
/// @since 1.1.0
inline void print_value(char32_t* const& value) noexcept {
    if (value == nullptr)
        stream << "(char32_t*)nullptr";
    else {
        auto string = to_string(std::u32string(value));
        stream << "(char32_t*)\"" << string.c_str() << '"';
    }
}

/// Outputs a string representation of the value.
/// @param value the value to output
/// @since 1.1.0
inline void print_value(const char32_t* const& value) noexcept {
    if (value == nullptr)
        stream << "(const char32_t*)nullptr";
    else {
        auto string = to_string(std::u32string(value));
        stream << "(const char32_t*)\"" << string.c_str() << '"';
    }
}

#ifdef __cpp_char8_t
/// Convert std::u8string to std::string.
/// @param u8string the std::u8string
/// @since 1.1.0
inline std::string to_string(const std::u8string& u8string) noexcept {
#ifdef _WIN32
    if (_code_page == CP_UTF8)
        return std::string((const char *)u8string.c_str());

    auto u8stringLen = (int)u8string.length();
    auto wstringLen = MultiByteToWideChar(CP_UTF8, 0, (const char *)u8string.c_str(), u8stringLen, nullptr, 0);
    std::wstring wstring(wstringLen, '\0');
    MultiByteToWideChar(CP_UTF8, 0, (const char *)u8string.c_str(), u8stringLen, &wstring[0], wstringLen);

    auto stringLen = WideCharToMultiByte(_code_page, 0, wstring.c_str(), wstringLen, nullptr, 0, 0, 0);
    std::string string(stringLen, '\0');
    WideCharToMultiByte(_code_page, 0, wstring.c_str(), wstringLen, &string[0], stringLen, 0, 0);
    return string;
#else
    return std::string((const char *)u8string.c_str());
#endif // _WIN32
}

/// Outputs a string representation of the value.
/// @param value the value to output
/// @since 1.1.0
inline void print_value(const std::u8string& value) noexcept {
    stream << "(std::u8string)\"" << to_string(value).c_str() << '"';
}

/// Outputs a string representation of the value.
/// @param value the value to output
/// @since 1.1.0
inline void print_value(char8_t* const& value) noexcept {
    if (value == nullptr)
        stream << "(char8_t*)nullptr";
    else {
        auto string = to_string((std::u8string(value)));
        stream << "(char8_t*)\"" << string.c_str() << '"';
    }
}

/// Outputs a string representation of the value.
/// @param value the value to output
/// @since 1.1.0
inline void print_value(const char8_t* const& value) noexcept {
    if (value == nullptr)
        stream << "(const char8_t*)nullptr";
    else {
        auto string = to_string((std::u8string(value)));
        stream << "(const char8_t*)\"" << string.c_str() << '"';
    }
}
#endif // __cpp_char8_t

/// Outputs a string representation of the value.
/// @param value the value to output
inline void print_value(const std::string& value) noexcept {
    stream << "(std::string)\"" << value.c_str() << '"';
}

/// Outputs a string representation of the value.
/// @param value the value to output
/// @since 1.1.0
inline void print_value(const std::wstring& value) noexcept {
    stream << "(std::wstring)\"" << to_string(value).c_str() << '"';
}

/// Outputs a string representation of the value.
/// @param value the value to output
template <typename T1, typename T2>
void print_value(const std::pair<T1, T2>& value) noexcept {
    stream << value.first << pair_separator << value.second;
}

template <class C>
void _print_container(const C& container) noexcept;

/// Outputs a string representation of the container object.
/// @param container the container object to output
template <typename T, size_t N>
void print_value(const std::array<T, N>& container) noexcept {
    _print_container(container);
}

/// Outputs a string representation of the container object.
/// @param container the container object to output
template <typename T, class Allocator = std::allocator<T>>
void print_value(const std::deque<T, Allocator>& container) noexcept {
    _print_container(container);
}

/// Outputs a string representation of the container object.
/// @param container the container object to output
template <typename T, class Allocator = std::allocator<T>>
void print_value(const std::list<T, Allocator>& container) noexcept {
    _print_container(container);
}

/// Outputs a string representation of the container object.
/// @param container the container object to output
template <
    typename Key,
    typename T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<Key const, T>>
>
void print_value(const std::map<Key, T, Compare, Allocator>& container) noexcept {
    _print_container(container);
}

/// Outputs a string representation of the container object.
/// @param container the container object to output
template <
    typename Key,
    typename T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<Key const, T>>
>
void print_value(const std::multimap<Key, T, Compare, Allocator>& container) noexcept {
    _print_container(container);
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
void print_value(const std::unordered_map<Key, T, Hash, Pred, Allocator>& container) noexcept {
    _print_container(container);
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
void print_value(const std::unordered_multimap<Key, T, Hash, Pred, Allocator>& container) noexcept {
    _print_container(container);
}

/// Outputs a string representation of the container object.
/// @param container the container object to output
template <
    typename Key,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<Key>
>
void print_value(const std::set<Key, Compare, Allocator>& container) noexcept {
    _print_container(container);
}

/// Outputs a string representation of the container object.
/// @param container the container object to output
template <
    typename Key,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<Key>
>
void print_value(const std::multiset<Key, Compare, Allocator>& container) noexcept {
    _print_container(container);
}

/// Outputs a string representation of the container object.
/// @param container the container object to output
template <
    typename Key,
    class Hash = std::hash<Key>,
    class Pred = std::equal_to<Key>,
    class Allocator = std::allocator<Key>
>
void print_value(const std::unordered_set<Key, Hash, Pred, Allocator>& container) noexcept {
    _print_container(container);
}

/// Outputs a string representation of the container object.
/// @param container the container object to output
template <
    typename Key,
    class Hash = std::hash<Key>,
    class Pred = std::equal_to<Key>,
    class Allocator = std::allocator<Key>
>
void print_value(const std::unordered_multiset<Key, Hash, Pred, Allocator>& container) noexcept {
    _print_container(container);
}

/// Outputs a string representation of the container object.
/// @param container the container object to output
template <typename T, class Allocator = std::allocator<T>>
void print_value(const std::vector<T, Allocator>& container) noexcept {
    _print_container(container);
}

/// Outputs a string representation of the value.
/// @param value the value to output
template <typename T>
inline void print_value(const T& value) noexcept {
    _print_type(value);
    stream << value;
}

/// Outputs a string representation of the value.
/// @param pointer the pointer of the value to output
/// @since 1.0.2
template <typename T>
inline void print_value(T* pointer) noexcept {
    _print_type(pointer);
    if (pointer == nullptr)
        stream << "nullptr";
    else {
        stream << '&';
        print_value(*pointer);
    }
}

/// Outputs a string representation of the value.
/// @param pointer the pointer of the value to output
/// @since 1.0.1
template <typename T>
inline void print_value(const T* pointer) noexcept {
    _print_type(pointer);
    if (pointer == nullptr)
        stream << "nullptr";
    else {
        stream << '&';
        print_value(*pointer);
    }
}

/// Outputs a string representation of the container object.
/// @param container the container object to output
template <class C>
inline void _print_container(const C& container) noexcept {
    bool multiLine = container.size() >= 2;

    _print_type(container);
    stream << start_string;
    if (multiLine) ++_data_nest_level;

    auto delim = "";
    std::for_each(container.cbegin(), container.cend(),
        [&](auto element) {
            stream << delim;
            if (multiLine)
                _print_next_line();
            print_value(element);
            delim = delimiter;
        }
    );

    if (multiLine) {
        --_data_nest_level;
        _print_next_line();
    }
    stream << end_string;
}

inline void _initialize() noexcept {
    if (!_initialized) {
        _print_sub([&] {stream << library_name;});
        _print_sub([] {});
        _initialized = true;
    }
}

/// Outputs the name and a string representation of the object.
/// @param name the name of the value
/// @param value the value to output
/// @param file_name the source file name of the code that called this function
/// @param line_number the line number of the code that called this function
template <typename T>
inline void print(const char name[], const T& value, const char file_name[], int line_number) noexcept {
    _print_sub([&] {
        stream << name << name_value_separator;
        print_value(value);
    }, file_name, line_number);
}

/// A utility class for debugging.
/// Call DebugTrace.enter and DebugTrace.leave methods when enter and leave your methods,
/// then outputs execution trace of the program.
class DebugTrace {
private:
    const char* _func_name = nullptr;

public:
    DebugTrace() = delete;
    DebugTrace(DebugTrace const&) = delete;

    /// Outputs a message when entering the function.
    /// @param func_name the function name
    /// @param file_name the source file name of the code that called this constructor
    /// @param line_number the line number of the code that called this function
    DebugTrace(const char func_name[], const char file_name[], int line_number) noexcept {
        _initialize();
        _func_name = func_name;

        if (_before_code_nest_level > _code_nest_level)
            _print_sub([] {});

        _print_sub([&] {stream << enter_string << _func_name;}, file_name, line_number);

        _before_code_nest_level = _code_nest_level;
        ++_code_nest_level;
    }

    /// Outputs a message when leaving the function
    ~DebugTrace() noexcept {
        _before_code_nest_level = _code_nest_level;
        --_code_nest_level;

        _print_sub([&] {stream << leave_string << _func_name;});
    }

    DebugTrace& operator =(const DebugTrace&) = delete;
};

} // namespace debugtrace
#endif // DEBUGTRACE_ENABLED
