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
    #include <cstdarg>
    #include <string>
    #ifdef __GNUG__
        #include <cxxabi.h> // abi::__cxa_demangle()
    #endif
    #include <unordered_map>
    #include <unordered_set>
    #include <vector>
    #if defined _WIN32
        #include <windows.h>
    #else
        #include <cuchar>
    #endif

    #if defined __clang__
        #define COMPILER_VERSION " (clang " __VERSION__ ")"
    #elif defined __GNUG__
        #define COMPILER_VERSION " (g++ " __VERSION__ ")"
    #elif defined _MSC_VER
        #define COMPILER_VERSION  " (Microsoft Visual C++)"
    #endif

    #define DEBUGTRACE_VERSION                   "2.0.0a2"
    #define DEBUGTRACE_START_MESSAGE             "DebugTrace-cpp " DEBUGTRACE_VERSION COMPILER_VERSION
    #define DEBUGTRACE_ENTER_STRING              "Enter "
    #define DEBUGTRACE_LEAVE_STRING              "Leave "
    #define DEBUGTRACE_LIMIT_STRING              "..."
    #define DEBUGTRACE_MAXIMUM_INDENTS           20
    #define DEBUGTRACE_CODE_INDENT_STRING        "| "
    #define DEBUGTRACE_DATA_INDENT_STRING        "  "
    #define DEBUGTRACE_OPEN_STRING               "{"
    #define DEBUGTRACE_CLOSE_STRING              "}"
    #define DEBUGTRACE_VARNAME_VALUE_SEPARATOR   " = "
    #define DEBUGTRACE_PAIR_SEPARATOR            ": "
    #define DEBUGTRACE_LOG_DATETIME_FORMAT       "%Y-%m-%d %H:%M:%S%z"
    #define DEBUGTRACE_MAXIMUM_DATA_OUTPUT_WIDTH 80
    #define DEBUGTRACE_COLLECTION_LIMIT          256

    #ifdef __cpp_inline_variables
        #define DEBUGTRACE_VARIABLES
    #else
        #define DEBUGTRACE_VARIABLES \
            namespace debugtrace {\
            const char* const _start_message            = DEBUGTRACE_START_MESSAGE;\
            const char*       enter_string              = DEBUGTRACE_ENTER_STRING;\
            const char*       leave_string              = DEBUGTRACE_LEAVE_STRING;\
            const char*       limit_string              = DEBUGTRACE_LIMIT_STRING;\
            int               maximum_indents           = DEBUGTRACE_MAXIMUM_INDENTS;\
            const char*       code_indent_string        = DEBUGTRACE_CODE_INDENT_STRING;\
            const char*       data_indent_string        = DEBUGTRACE_DATA_INDENT_STRING;\
            const char*       open_string               = DEBUGTRACE_OPEN_STRING;\
            const char*       close_string              = DEBUGTRACE_CLOSE_STRING;\
            const char*       varname_value_separator   = DEBUGTRACE_VARNAME_VALUE_SEPARATOR;\
            const char*       pair_separator            = DEBUGTRACE_PAIR_SEPARATOR;\
            const char*       log_datetime_format       = DEBUGTRACE_LOG_DATETIME_FORMAT;\
            size_t            maximum_data_output_width = DEBUGTRACE_MAXIMUM_DATA_OUTPUT_WIDTH;\
            size_t            collection_limit          = DEBUGTRACE_COLLECTION_LIMIT;\
            bool              _initialized              = false;\
            std::ostream&     output_stream             = std::cerr;\
            int               _code_nest_level          = 0;\
            int               _before_code_nest_level   = 0;\
            int               _data_nest_level          = 0;\
            unsigned int      _code_page                = 65001;\
            }
    #endif // __cpp_inline_variables

    #ifdef __PRETTY_FUNCTION__
        // GCC, Clang
        #define DEBUGTRACE_ENTER debugtrace::_DebugTrace _trace(__PRETTY_FUNCTION__, __FILE__, __LINE__);
    #elif defined __FUNCSIG__
        // Visual C++
        #define DEBUGTRACE_ENTER debugtrace::_DebugTrace _trace(__FUNCSIG__, __FILE__, __LINE__);
    #else
        // Others
        #define DEBUGTRACE_ENTER debugtrace::_DebugTrace _trace(__func__, __FILE__, __LINE__);
    #endif // __PRETTY_FUNCTION__
    #define DEBUGTRACE_MESSAGE(message) debugtrace::print_message(message, __FILE__, __LINE__);
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
    inline const char* const _start_message            = DEBUGTRACE_START_MESSAGE;
    inline const char*       enter_string              = DEBUGTRACE_ENTER_STRING;
    inline const char*       leave_string              = DEBUGTRACE_LEAVE_STRING;
    inline const char*       limit_string              = DEBUGTRACE_LIMIT_STRING;\
    inline int               maximum_indents           = DEBUGTRACE_MAXIMUM_INDENTS;
    inline const char*       code_indent_string        = DEBUGTRACE_CODE_INDENT_STRING;
    inline const char*       data_indent_string        = DEBUGTRACE_DATA_INDENT_STRING;
    inline const char*       open_string               = DEBUGTRACE_OPEN_STRING;
    inline const char*       close_string              = DEBUGTRACE_CLOSE_STRING;
    inline const char*       varname_value_separator   = DEBUGTRACE_VARNAME_VALUE_SEPARATOR;
    inline const char*       pair_separator            = DEBUGTRACE_PAIR_SEPARATOR;
    inline const char*       log_datetime_format       = DEBUGTRACE_LOG_DATETIME_FORMAT;
    inline size_t            maximum_data_output_width = DEBUGTRACE_MAXIMUM_DATA_OUTPUT_WIDTH;
    inline size_t            collection_limit          = DEBUGTRACE_COLLECTION_LIMIT;
    inline bool              _initialized              = false;
    inline std::ostream&     output_stream             = std::cerr;
    inline int               _code_nest_level          = 0;
    inline int               _before_code_nest_level   = 0;
    inline int               _data_nest_level          = 0;
    inline unsigned int      _code_page                = 65001; // UTF-8
#else
    extern const char* const _start_message;
    extern const char*       enter_string;
    extern const char*       leave_string;
    extern const char*       limit_string;
    extern int               maximum_indents;
    extern const char*       code_indent_string;
    extern const char*       data_indent_string;
    extern const char*       open_string;
    extern const char*       close_string;
    extern const char*       varname_value_separator;
    extern const char*       pair_separator;
    extern const char*       log_datetime_format;
    extern size_t            maximum_data_output_width;
    extern size_t            collection_limit;
    extern bool              _initialized;
    extern std::ostream&     output_stream;
    extern int               _code_nest_level;
    extern int               _before_code_nest_level;
    extern int               _data_nest_level;
    extern unsigned int      _code_page;
#endif // __cpp_inline_variables

/// Returns a string for code indent.
inline std::string _get_code_indent_string() noexcept {
    std::string indent_str;
    for (auto index = 0; index < _code_nest_level && index < maximum_indents; ++index)
        indent_str += code_indent_string;
    return indent_str;
}

/// Returns a string for data indent.
inline std::string _get_data_indent_string() noexcept {
    std::string indent_str;
    for (auto index = 0; index < _data_nest_level && index < maximum_indents; ++index)
        indent_str += data_indent_string;
    return indent_str;
}

/// Outputs the date and time.
inline std::string _get_log_datetime() noexcept {
    const auto now = std::time(nullptr);
#ifdef _MSC_VER
    // Visual C++
    struct std::tm datetime;
    localtime_s(&datetime, &now);
#else
    // Others
    const auto datetime = *std::localtime(&now);
#endif // _MSC_VER
    char buff[64];
    std::strftime(buff, sizeof(buff), log_datetime_format, &datetime);
    return buff;
}

/// Sets Windwos Code Page
/// @param codePage the code page (e.g.: CP_ACP, CP_UTF8)
inline void set_code_page(unsigned int codePage) {
    _code_page = codePage;
}

/// Returns a string representation of the type of the value.
/// @param value the value to output
template <typename T>
std::string _get_type_string(const T& value, size_t size = -1) noexcept {
    auto type_string = std::string("(");
#ifdef _MSC_VER
    // Visual C++
    type_string += typeid(value).name();
#else
    // gcc, clang
    int status;
    char* type_name = abi::__cxa_demangle(typeid(value).name(), nullptr, nullptr, &status);
    type_string += (type_name == nullptr ? "?" : type_name);
    if (type_name != nullptr)
        free(type_name);
#endif // _MSC_VER
    if ((int)size != -1) {
        type_string += " size:";
        type_string += std::to_string(size);
    }
    type_string += ')';
    return type_string;
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const bool& value) noexcept {
    return std::vector<std::string>({value ? "true" : "false"});
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const char& value) noexcept {
    return std::vector<std::string>({"(char)" + std::to_string(value)});
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const signed char& value) noexcept {
    return std::vector<std::string>({"(signed char)" + std::to_string(value)});
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const unsigned char& value) noexcept {
    return std::vector<std::string>({"(unsigned char)" + std::to_string(value)});
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const short& value) noexcept {
    return std::vector<std::string>({"(short)" + std::to_string(value)});
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const unsigned short& value) noexcept {
    return std::vector<std::string>({"(unsigned short)" + std::to_string(value)});
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const int& value) noexcept {
    return std::vector<std::string>({std::to_string(value)});
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const unsigned int& value) noexcept {
    return std::vector<std::string>({std::to_string(value) + 'u'});
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const long& value) noexcept {
    return std::vector<std::string>({std::to_string(value) + 'l'});
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const unsigned long& value) noexcept {
    return std::vector<std::string>({std::to_string(value) + "ul"});
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const long long& value) noexcept {
    return std::vector<std::string>({std::to_string(value) + "ll"});
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const unsigned long long& value) noexcept {
    return std::vector<std::string>({std::to_string(value) + "ull"});
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const float& value) noexcept {
    return std::vector<std::string>({std::to_string(value) + 'f'});
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const double& value) noexcept {
    return std::vector<std::string>({std::to_string(value)});
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const long double& value) noexcept {
    return std::vector<std::string>({std::to_string(value) + 'l'});
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const wchar_t& value) noexcept {
    return std::vector<std::string>({"(wchar_t)" + std::to_string(value)});
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(char* const& value) noexcept {
    return std::vector<std::string>({value == nullptr
        ? "(char*)nullptr})"
        : "(char*)\"" + std::string(value) + '"'
    });
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const char* const& value) noexcept {
    return std::vector<std::string>({value == nullptr
        ? "(const char*)nullptr"
        : "(const char*)\"" + std::string(value) + '"'
    });
}


/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(signed char* const& value) noexcept {
    return std::vector<std::string>({value == nullptr
        ? "(signed char*)nullptr"
        : "(signed char*)\"" + std::string((char*)value) + '"'
    });
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const signed char* const& value) noexcept {
    return std::vector<std::string>({value == nullptr
        ?"(const signed char*)nullptr"
        :"(const signed char*)\"" + std::string((const char*)value) + '"'
    });
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(unsigned char* const& value) noexcept {
    return std::vector<std::string>({value == nullptr
        ? "(unsigned char*)nullptr"
        : "(unsigned char*)\"" + std::string((char *)value) + '"'
    });
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const unsigned char* const& value) noexcept {
    return std::vector<std::string>({value == nullptr
        ? "(const unsigned char*)nullptr"
        : "(const unsigned char*)\"" + std::string((const char*)value) + '"'
    });
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const std::string& value) noexcept {
    return std::vector<std::string>({"(std::string)\"" + value + '"'});
}

/// Convert std::wstring to std::string.
/// @param wstring the std::wstring
/// @return a converted std::string
inline std::string _to_string(const std::wstring& wstring) noexcept {
#ifdef _WIN32
    const auto wstringLen = (int)wstring.length();
    const auto stringLen = WideCharToMultiByte(_code_page, 0, wstring.c_str(), wstringLen, nullptr, 0, 0, 0);
    std::string string(stringLen, '\0');
    WideCharToMultiByte(_code_page, 0, wstring.c_str(), wstringLen, &string[0], stringLen, 0, 0);
    return string;
#else
    mbstate_t mbstate{};
    char char_buf[wstring.length() * sizeof(std::wstring::value_type) + 1];
    auto char_ptr = char_buf;
    for (const auto& wchar : wstring) {
        const auto converted_count = wcrtomb(char_ptr, wchar, &mbstate);
        if (converted_count == (size_t)-1)
            return "<Cannot convert the wstring to string>";
        char_ptr += converted_count;
    }
    *char_ptr = '\0';
    return char_buf;
#endif // _WIN32
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const std::wstring& value) noexcept {
    return std::vector<std::string>({"(std::wstring)\"" + _to_string(value)});
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(wchar_t* const& value) noexcept {
    return std::vector<std::string>({value == nullptr
        ? "(wchar_t*)nullptr"
        : "(wchar_t*)\"" + _to_string(std::wstring(value)) + '"'
    });
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const wchar_t* const& value) noexcept {
    return std::vector<std::string>({value == nullptr
        ? "(const wchar_t*)nullptr"
        : "(const wchar_t*)\"" + _to_string(std::wstring(value)) + '"'
    });
}

/// Convert std::u16string to std::string.
/// @param u16string the std::u16string
inline std::string _to_string(const std::u16string& u16string) noexcept {
#ifdef _WIN32
    const auto u16stringLen = (int)u16string.length();
    const auto stringLen = WideCharToMultiByte(_code_page, 0, (LPCWCH)u16string.c_str(), u16stringLen, nullptr, 0, 0, 0);
    std::string string(stringLen, '\0');
    WideCharToMultiByte(_code_page, 0, (LPCWCH)u16string.c_str(), u16stringLen, &string[0], stringLen, 0, 0);
    return string;
#else
    mbstate_t mbstate{};
    char char_buf[u16string.length() * sizeof(std::u16string::value_type) + 1];
    auto char_ptr = char_buf;
    for (const auto& char16 : u16string) {
        const auto converted_count = c16rtomb(char_ptr, char16, &mbstate);
        if (converted_count == (size_t)-1)
            return "<Cannot convert the u16string to string>";
        char_ptr += converted_count;
    }
    *char_ptr = '\0';
    return char_buf;
#endif // _WIN32
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const std::u16string& value) noexcept {
    return std::vector<std::string>({"(std::u16string)\"" + _to_string(value) + '"'});
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(char16_t* const& value) noexcept {
    return std::vector<std::string>({value == nullptr
        ? "(char16_t*)nullptr"
        : "(char16_t*)\"" + _to_string(std::u16string(value)) + '"'
    });
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const char16_t* const& value) noexcept {
    return std::vector<std::string>({value == nullptr
        ? "(const char16_t*)nullptr"
        : "(const char16_t*)\"" + _to_string(std::u16string(value)) + '"'
    });
}

/// Convert std::u32string to std::string.
/// @param u32string the std::u32string
inline std::string _to_string(const std::u32string& u32string) noexcept {
#ifdef _WIN32
    return "<Unimplemented(string <- u32string)>";
#else
    mbstate_t mbstate{};
    char char_buf[u32string.length() * sizeof(std::u32string::value_type) + 1];
    auto char_ptr = char_buf;
    for (const auto& char32 : u32string) {
        const auto converted_count = c32rtomb(char_ptr, char32, &mbstate);
        if (converted_count == (size_t)-1)
            return "<Cannot convert the u32string to string>";
        char_ptr += converted_count;
    }
    *char_ptr = '\0';
    return char_buf;
#endif // _WIN32
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const std::u32string& value) noexcept {
    return std::vector<std::string>({"(std::u32string)\"" + _to_string(value) + '"'});
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(char32_t* const& value) noexcept {
    return std::vector<std::string>({value == nullptr
        ? "(char32_t*)nullptr"
        : "(char32_t*)\"" + _to_string(std::u32string(value)) + '"'
    });
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const char32_t* const& value) noexcept {
    return std::vector<std::string>({value == nullptr
        ? "(const char32_t*)nullptr"
        : "(const char32_t*)\"" + _to_string(std::u32string(value)) + '"'
    });
}

#ifdef __cpp_char8_t
/// Convert std::u8string to std::string.
/// @param u8string the std::u8string
inline std::string _to_string(const std::u8string& u8string) noexcept {
#ifdef _WIN32
    if (_code_page == CP_UTF8)
        return std::string((const char *)u8string.c_str());

    const auto u8stringLen = (int)u8string.length();
    const auto wstringLen = MultiByteToWideChar(CP_UTF8, 0, (const char *)u8string.c_str(), u8stringLen, nullptr, 0);
    std::wstring wstring(wstringLen, '\0');
    MultiByteToWideChar(CP_UTF8, 0, (const char *)u8string.c_str(), u8stringLen, &wstring[0], wstringLen);

    const auto stringLen = WideCharToMultiByte(_code_page, 0, wstring.c_str(), wstringLen, nullptr, 0, 0, 0);
    std::string string(stringLen, '\0');
    WideCharToMultiByte(_code_page, 0, wstring.c_str(), wstringLen, &string[0], stringLen, 0, 0);
    return string;
#else
    return std::string((const char *)u8string.c_str());
#endif // _WIN32
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const std::u8string& value) noexcept {
    return std::vector<std::string>({"(std::u8string)\"" + _to_string(value) + '"'});
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(char8_t* const& value) noexcept {
    return std::vector<std::string>({value == nullptr
        ? "(char8_t*)nullptr"
        : "(char8_t*)\"" + _to_string((std::u8string(value))) + '"'
    });
}

/// Returns a string representation of the value.
/// @param value the value to output
inline std::vector<std::string> to_strings(const char8_t* const& value) noexcept {
    return std::vector<std::string>({value == nullptr
        ? "(const char8_t*)nullptr"
        : "(const char8_t*)\"" + _to_string((std::u8string(value))) + '"'
    });
}
#endif // __cpp_char8_t


template <typename T>
std::vector<std::string> to_strings(const T& value) noexcept;

template <typename T>
std::vector<std::string> to_strings(const T* pointer) noexcept;

template <typename T1, typename T2>
std::vector<std::string> to_strings(const std::pair<T1, T2>& value) noexcept;

template <typename T, size_t N>
std::vector<std::string> to_strings(const std::array<T, N>& container) noexcept;

template <typename T, class Allocator = std::allocator<T>>
std::vector<std::string> to_strings(const std::deque<T, Allocator>& container) noexcept;

template <typename T, class Allocator = std::allocator<T>>
std::vector<std::string> to_strings(const std::list<T, Allocator>& container) noexcept;

template <
    typename Key,
    typename T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<Key const, T>>
>
std::vector<std::string> to_strings(const std::map<Key, T, Compare, Allocator>& container) noexcept;

template <
    typename Key,
    typename T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<Key const, T>>
>
std::vector<std::string> to_strings(const std::multimap<Key, T, Compare, Allocator>& container) noexcept;

template <
    typename Key,
    typename T,
    class Hash = std::hash<Key>,
    class Pred = std::equal_to<Key>,
    class Allocator = std::allocator<std::pair<Key const, T>>
>
std::vector<std::string> to_strings(const std::unordered_map<Key, T, Hash, Pred, Allocator>& container) noexcept;

template <
    typename Key,
    typename T,
    class Hash = std::hash<Key>,
    class Pred = std::equal_to<Key>,
    class Allocator = std::allocator<std::pair<Key const, T>>
>
std::vector<std::string> to_strings(const std::unordered_multimap<Key, T, Hash, Pred, Allocator>& container) noexcept;

template <
    typename Key,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<Key>
>
std::vector<std::string> to_strings(const std::set<Key, Compare, Allocator>& container) noexcept;

template <
    typename Key,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<Key>
>
std::vector<std::string> to_strings(const std::multiset<Key, Compare, Allocator>& container) noexcept;

template <
    typename Key,
    class Hash = std::hash<Key>,
    class Pred = std::equal_to<Key>,
    class Allocator = std::allocator<Key>
>
std::vector<std::string> to_strings(const std::unordered_set<Key, Hash, Pred, Allocator>& container) noexcept;

template <
    typename Key,
    class Hash = std::hash<Key>,
    class Pred = std::equal_to<Key>,
    class Allocator = std::allocator<Key>
>
std::vector<std::string> to_strings(const std::unordered_multiset<Key, Hash, Pred, Allocator>& container) noexcept;

template <typename T, class Allocator = std::allocator<T>>
std::vector<std::string> to_strings(const std::vector<T, Allocator>& container) noexcept;

template <class C>
std::vector<std::string> _to_strings_container(const C& container) noexcept;


/// Returns a string representation of the value.
/// @param value the value to output
template <typename T>
std::vector<std::string> to_strings(const T& value) noexcept {
    return std::vector<std::string>({_get_type_string(value) + std::to_string(value)});
}

/// Returns a string representation of the value.
/// @param pointer the pointer of the value to output
template <typename T>
std::vector<std::string> to_strings(const T* pointer) noexcept {
    return std::vector<std::string>({pointer == nullptr
        ? _get_type_string(pointer) + "nullptr"
        : _get_type_string(pointer) + "&" + std::to_string(*pointer)
    });
}

/// Returns a string representation of the value.
/// @param value the value to output
template <typename T1, typename T2>
std::vector<std::string> to_strings(const std::pair<T1, T2>& value) noexcept {
    auto firstStrings = to_strings(value.first);
    auto secondStrings = to_strings(value.second);

    firstStrings.back() += pair_separator;

    auto index = 0;
    for (const auto& secondString : secondStrings) {
        if (index == 0) {
            if (firstStrings.back().size() + secondString.size() <= maximum_data_output_width)
                // one line
                firstStrings.back() += secondString;
            else
                firstStrings.push_back(_get_data_indent_string() + secondString);
        } else {
            firstStrings.push_back(secondString);
        }
        ++index;
    }

    return firstStrings;
}

/// Returns a string representation of the container object.
/// @param container the container object to output
template <typename T, size_t N>
std::vector<std::string> to_strings(const std::array<T, N>& container) noexcept {
    return _to_strings_container(container);
}

/// Returns a string representation of the container object.
/// @param container the container object to output
template <typename T, class Allocator>
std::vector<std::string> to_strings(const std::deque<T, Allocator>& container) noexcept {
    return _to_strings_container(container);
}

/// Returns a string representation of the container object.
/// @param container the container object to output
template <typename T, class Allocator>
std::vector<std::string> to_strings(const std::list<T, Allocator>& container) noexcept {
    return _to_strings_container(container);
}

/// Returns a string representation of the container object.
/// @param container the container object to output
template <typename Key, typename T, class Compare, class Allocator>
std::vector<std::string> to_strings(const std::map<Key, T, Compare, Allocator>& container) noexcept {
    return _to_strings_container(container);
}

/// Returns a string representation of the container object.
/// @param container the container object to output
template <typename Key, typename T, class Compare, class Allocator>
std::vector<std::string> to_strings(const std::multimap<Key, T, Compare, Allocator>& container) noexcept {
    return _to_strings_container(container);
}

/// Returns a string representation of the container object.
/// @param container the container object to output
template <typename Key, typename T, class Hash, class Pred, class Allocator>
std::vector<std::string> to_strings(const std::unordered_map<Key, T, Hash, Pred, Allocator>& container) noexcept {
    return _to_strings_container(container);
}

/// Returns a string representation of the container object.
/// @param container the container object to output
template <typename Key, typename T, class Hash, class Pred, class Allocator>
std::vector<std::string> to_strings(const std::unordered_multimap<Key, T, Hash, Pred, Allocator>& container) noexcept {
    return _to_strings_container(container);
}

/// Returns a string representation of the container object.
/// @param container the container object to output
template <typename Key, class Compare, class Allocator>
std::vector<std::string> to_strings(const std::set<Key, Compare, Allocator>& container) noexcept {
    return _to_strings_container(container);
}

/// Returns a string representation of the container object.
/// @param container the container object to output
template <typename Key, class Compare, class Allocator>
std::vector<std::string> to_strings(const std::multiset<Key, Compare, Allocator>& container) noexcept {
    return _to_strings_container(container);
}

/// Returns a string representation of the container object.
/// @param container the container object to output
template <typename Key, class Hash, class Pred, class Allocator>
std::vector<std::string> to_strings(const std::unordered_set<Key, Hash, Pred, Allocator>& container) noexcept {
    return _to_strings_container(container);
}

/// Returns a string representation of the container object.
/// @param container the container object to output
template <typename Key, class Hash, class Pred, class Allocator>
std::vector<std::string> to_strings(const std::unordered_multiset<Key, Hash, Pred, Allocator>& container) noexcept {
    return _to_strings_container(container);
}

/// Returns a string representation of the container object.
/// @param container the container object to output
template <typename T, class Allocator>
std::vector<std::string> to_strings(const std::vector<T, Allocator>& container) noexcept {
    return _to_strings_container(container);
}

/// Returns a string representation of the container object.
/// @param container the container object to output
template <class C>
std::vector<std::string> _to_strings_container(const C& container) noexcept {
    std::vector<std::string> strings;

    auto one_line = true;

    const auto type_str = _get_type_string(container, container.size());
    auto string = type_str;
    string += open_string;
    auto delimiter = "";
    auto count = (size_t)1;
    for (const auto& value : container) {
        string += delimiter;
        if (count > collection_limit) {
            string += limit_string;
            break;
        }

        const auto value_strings = to_strings(value);
        if (value_strings.size() > 1) {
            // the value string is not one line
            one_line = false;
            break;
        }
        string += value_strings.front();

        if (string.size() > maximum_data_output_width) {
            // multi lines
            one_line = false;
            break;
        }

        delimiter = ", ";
        count += 1;
    }

    if (one_line) {
        // strings is one line
        string += close_string;
        strings.push_back(string);

    } else {
        // strings is not one line
        strings.push_back(type_str + open_string);
        _data_nest_level += 1;
        const auto indent_string = _get_data_indent_string();
        count = 1;
        for (const auto& value : container) {
            if (count > collection_limit) {
                strings.push_back(indent_string + limit_string);
                break;
            }

            const auto value_strings = to_strings(value);
            auto is_first = true;
            for (const auto& value_string : value_strings) {
                if (is_first)
                    strings.push_back(indent_string + value_string);
                else
                    strings.push_back(value_string);
                is_first = false;
            }

            strings.back() += ',';
            count += 1;
        }

        _data_nest_level -= 1;
        strings.push_back(_get_data_indent_string() + close_string);
    }

    return strings;
}

inline void print_message(std::string message, const char file_name[] = "", int line_number = 0) noexcept {
    auto log_str = _get_log_datetime();
    log_str += ' ';
    log_str += _get_code_indent_string();
    log_str += message;

    if (file_name[0] != '\0') {
        auto file_name2 = std::strrchr(file_name, '/');
        if (file_name2 == nullptr) {
            file_name2 = std::strrchr(file_name, '\\');
            if (file_name2 == nullptr)
                file_name2 = const_cast<char*>(file_name);
            else
                ++file_name2;
        } else
            ++file_name2;

        log_str += " (";
        log_str += file_name2;
        if (line_number > 0) {
            log_str += pair_separator;
            log_str += std::to_string(line_number);
        }
        log_str += ')';
    }

    output_stream << log_str << std::endl;
}

template <typename T>
void print(const char* name, const T& value, const char file_name[] = "", int line_number = 0) noexcept {
    _data_nest_level = 0;
    const auto value_strings = to_strings(value);

    auto index = 0;
    for (const auto& value_string : value_strings) {
        print_message(index == 0
            ? std::string(name) + varname_value_separator + value_string
            : value_string);
        ++index;
    }
}

inline void _initialize() noexcept {
    if (!_initialized) {
        print_message(_start_message);
        print_message("");
        _initialized = true;
    }
}

/// A utility class for debugging.
/// Call _DebugTrace.enter and _DebugTrace.leave methods when enter and leave your methods,
/// then outputs execution trace of the program.
class _DebugTrace {
private:
    const char* _func_name = nullptr;
    const char* _file_name = nullptr;

public:
    _DebugTrace() = delete;
    _DebugTrace(_DebugTrace const&) = delete;

    /// Outputs a message when entering the function.
    /// @param func_name the function name
    /// @param file_name the source file name of the code that called this constructor
    /// @param line_number the line number of the code that called this function
    _DebugTrace(const char func_name[], const char file_name[], int line_number) noexcept {
        _initialize();
        _func_name = func_name;
        _file_name = file_name;

        if (_before_code_nest_level > _code_nest_level)
            print_message("");

        print_message(std::string(enter_string) + _func_name, _file_name, line_number);

        _before_code_nest_level = _code_nest_level;
        ++_code_nest_level;
    }

    /// Outputs a message when leaving the function
    ~_DebugTrace() noexcept {
        _before_code_nest_level = _code_nest_level;
        --_code_nest_level;

        print_message(std::string(leave_string) + _func_name, _file_name);
    }

    _DebugTrace& operator =(const _DebugTrace&) = delete;
};

} // namespace debugtrace
#endif // DEBUGTRACE_ENABLED
