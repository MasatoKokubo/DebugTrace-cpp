/// Example2.cpp 
/// (C) 2017 Masato Kokubo
#include <string>
#include "Example.hpp"
#include "../../../include/debugtrace.hpp"

/// ClassA::func2
void ClassA::func2() const noexcept {
#if defined CP_ACP
    // sets Windows code page to Japanese Shift-JIS
//  debugtrace::set_code_page(932); // for Debugging

    // sets Windows code page to Japanese EUC
//  debugtrace::set_code_page(20932); // for Debugging

    // sets Windows code page to Japanese JIS
//  debugtrace::set_code_page(50220); // for Debugging

    // sets Windows code page to UTF-8
    debugtrace::set_code_page(CP_UTF8); // for Debugging
#else
    const char* locale = setlocale(LC_CTYPE, nullptr);
    DEBUGTRACE_PRINT(locale) // for Debugging
    locale = setlocale(LC_CTYPE, "");
    DEBUGTRACE_PRINT(locale) // for Debugging
#endif
    DEBUGTRACE_ENTER // for Debugging

    // char*
    auto const char_p = (char *)"ABCDE abcde あいうえお アイウエオ 漢字 🙂";
    DEBUGTRACE_PRINT(char_p) // for Debugging

    // char* const
    auto const const_char_p = "ABCDE abcde あいうえお アイウエオ 漢字 🙂";
    DEBUGTRACE_PRINT(const_char_p) // for Debugging

    // signed char*
    auto const signed_char_p = (signed char*)"ABCDE abcde あいうえお アイウエオ 漢字 🙂";
    DEBUGTRACE_PRINT(signed_char_p) // for Debugging

    // signed char* const
    auto const const_signed_char_p = (const signed char*)"ABCDE abcde あいうえお アイウエオ 漢字 🙂";
    DEBUGTRACE_PRINT(const_signed_char_p) // for Debugging

    // unsigned char*
    auto const unsigned_char_p = (unsigned char*)"ABCDE abcde あいうえお アイウエオ 漢字 🙂";
    DEBUGTRACE_PRINT(unsigned_char_p) // for Debugging

    // unsigned char* const
    auto const const_unsigned_char_p = (const unsigned char*)"ABCDE abcde あいうえお アイウエオ 漢字 🙂";
    DEBUGTRACE_PRINT(const_unsigned_char_p) // for Debugging

    // char* nullptr
    auto const null_char_p = (char*)nullptr;
    DEBUGTRACE_PRINT(null_char_p) // for Debugging

    // signed char* nullptr
    auto const null_signed_char_p = (signed char*)nullptr;
    DEBUGTRACE_PRINT(null_signed_char_p) // for Debugging

    // unsigned char* nullptr
    auto const null_unsigned_char_p = (unsigned char*)nullptr;
    DEBUGTRACE_PRINT(null_unsigned_char_p) // for Debugging

    // wchar*
    auto const wchar_p = (wchar_t*)L"ABCDE abcde あいうえお アイウエオ 漢字 🙂";
    DEBUGTRACE_PRINT(wchar_p) // for Debugging

    // const wchar*
    auto const const_wchar_p =  L"ABCDE abcde あいうえお アイウエオ 漢字 🙂";
    DEBUGTRACE_PRINT(const_wchar_p) // for Debugging

    // char16_t*
    auto const char16_p = (char16_t*)u"ABCDE abcde あいうえお アイウエオ 漢字 🙂";
    DEBUGTRACE_PRINT(char16_p) // for Debugging

    // const char16_t*
    auto const const_char16_p =  u"ABCDE abcde あいうえお アイウエオ 漢字 🙂";
    DEBUGTRACE_PRINT(const_char16_p) // for Debugging

    // char32_t*
    auto const char32_p = (char32_t*)U"ABCDE abcde あいうえお アイウエオ 漢字 🙂";
    DEBUGTRACE_PRINT(char32_p) // for Debugging

    // const char32_t*
    auto const const_char32_p =  U"ABCDE abcde あいうえお アイウエオ 漢字 🙂";
    DEBUGTRACE_PRINT(const_char32_p) // for Debugging

#if defined __cpp_char8_t
    // char8_t*
    auto const char8_p = (char8_t*)u8"ABCDE abcde あいうえお アイウエオ 漢字 🙂";
    DEBUGTRACE_PRINT(char8_p) // for Debugging
#endif

    // const char8_t*
    auto const const_char8_p = u8"ABCDE abcde あいうえお アイウエオ 漢字 🙂";
    DEBUGTRACE_PRINT(const_char8_p) // for Debugging

    // std::string
    auto const string = std::string("ABCDE abcde あいうえお アイウエオ 漢字 🙂");
    DEBUGTRACE_PRINT(string) // for Debugging

    // std::wstring
    auto const wstring = std::wstring(L"ABCDE abcde あいうえお アイウエオ 漢字 🙂");
    DEBUGTRACE_PRINT(wstring) // for Debugging

    // std::u16string
    auto const u16string = std::u16string(u"ABCDE abcde あいうえお アイウエオ 漢字 🙂");
    DEBUGTRACE_PRINT(u16string) // for Debugging

    // std::u32string
    auto const u32string = std::u32string(U"ABCDE abcde あいうえお アイウエオ 漢字 🙂");
    DEBUGTRACE_PRINT(u32string) // for Debugging

#if defined __cpp_char8_t
    // std::u8string
    auto const u8string = std::u8string(u8"ABCDE abcde あいうえお アイウエオ 漢字 🙂");
    DEBUGTRACE_PRINT(u8string) // for Debugging
#endif
}
