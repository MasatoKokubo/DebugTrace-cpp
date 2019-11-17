/// Example2.cpp 
/// (C) 2017 Masato Kokubo
#include <string>
#include "Example.hpp"
#include "DebugTrace.hpp"

/// ClassA::func2
void ClassA::func2() const noexcept {
    // sets Windows code page to Japanese Shift-JIS
//  debugtrace::DebugTrace::setCodePage(932); // for Debugging

    // sets Windows code page to Japanese EUC
//  debugtrace::DebugTrace::setCodePage(20932); // for Debugging

    // sets Windows code page to Japanese JIS
//  debugtrace::DebugTrace::setCodePage(50220); // for Debugging

    // sets Windows code page to UTF-8
    debugtrace::DebugTrace::setCodePage(CP_UTF8); // for Debugging

    DEBUG_TRACE // for Debugging

    // char*
    auto const char_p = (char *)"ABCDE abcde";
    DEBUG_PRINT(char_p) // for Debugging

    // char* const
    auto const const_char_p = "ABCDE abcde";
    DEBUG_PRINT(const_char_p) // for Debugging

    // signed char*
    auto const signed_char_p = (signed char*)"ABCDE abcde";
    DEBUG_PRINT(signed_char_p) // for Debugging

    // signed char* const
    auto const const_signed_char_p = (const signed char*)"ABCDE abcde";
    DEBUG_PRINT(const_signed_char_p) // for Debugging

    // unsigned char*
    auto const unsigned_char_p = (unsigned char*)"ABCDE abcde";
    DEBUG_PRINT(unsigned_char_p) // for Debugging

    // unsigned char* const
    auto const const_unsigned_char_p = (const unsigned char*)"ABCDE abcde";
    DEBUG_PRINT(const_unsigned_char_p) // for Debugging

    // char* nullptr
    auto const null_char_p = (char*)nullptr;
    DEBUG_PRINT(null_char_p) // for Debugging

    // signed char* nullptr
    auto const null_signed_char_p = (signed char*)nullptr;
    DEBUG_PRINT(null_signed_char_p) // for Debugging

    // unsigned char* nullptr
    auto const null_unsigned_char_p = (unsigned char*)nullptr;
    DEBUG_PRINT(null_unsigned_char_p) // for Debugging

    // wchar*
    auto const wchar_p = (wchar_t*)L"あいうえお アイウエオ 漢字 🙂";
    DEBUG_PRINT(wchar_p) // for Debugging

    // const wchar*
    auto const const_wchar_p =  (const wchar_t*)L"あいうえお アイウエオ 漢字 🙂";
    DEBUG_PRINT(const_wchar_p) // for Debugging

    // char16_t*
    auto const char16_p = (char16_t*)u"あいうえお アイウエオ 漢字 🙂";
    DEBUG_PRINT(char16_p) // for Debugging

    // const char16_t*
    auto const const_char16_p =  (const char16_t*)u"あいうえお アイウエオ 漢字 🙂";
    DEBUG_PRINT(const_char16_p) // for Debugging

#if _HAS_CHAR8_T == 1
    // char8_t*
    auto const char8_p = (char8_t*)u8"あいうえお アイウエオ 漢字 🙂";
    DEBUG_PRINT(char8_p) // for Debugging

    // const char8_t*
    auto const const_char8_p =  (const char8_t*)u8"あいうえお アイウエオ 漢字 🙂";
    DEBUG_PRINT(const_char8_p) // for Debugging
#endif

    // std::string
    const std::string string("ABCDE abcde");
    DEBUG_PRINT(string) // for Debugging

    // std::wstring
    const std::wstring wstring(L"あいうえお アイウエオ 漢字 🙂");
    DEBUG_PRINT(wstring) // for Debugging

    // std::u16string
    const std::u16string u16string(u"あいうえお アイウエオ 漢字 🙂");
    DEBUG_PRINT(u16string) // for Debugging

#if _HAS_CHAR8_T == 1
    // std::u8string
    const std::u8string u8string(u8"あいうえお アイウエオ 漢字 🙂");
    DEBUG_PRINT(u8string) // for Debugging
#endif
}
