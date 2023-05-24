#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN

#endif
#ifndef MYHELPER_H
#define MYHELPER_H
#include <Windows.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <cwchar>
#include <locale>
#include <codecvt>

class MyHelper
{
public:
    static std::wstring strToWstr(const std::string &str)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
        return myconv.from_bytes(str);
    }
    static std::wstring wstring_to_utf8_wstring(const std::wstring &wstr)
    {
        int utf8Size = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
        std::string utf8Str(utf8Size, 0);
        WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &utf8Str[0], utf8Size, nullptr, nullptr);

        int wstrSize = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, nullptr, 0);
        std::wstring result(wstrSize, 0);
        MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, &result[0], wstrSize);

        return result;
    }

    static std::string convertWStringtoStr(const std::wstring &wstr)
    {
        std::string str;

        const wchar_t *wc = wstr.c_str();
        char *mb = new char[wstr.size() + 1];

        wcstombs(mb, wc, wstr.size());

        str = mb;

        delete[] mb;
        return str;
    }

    static std::wstring utf8_to_unicode_escape_sequences(const std::wstring &wstr)
    {
        // Convert the UTF-8 string to a wide-character string

        // Convert each wide-character to a Unicode escape sequence
        std::wstringstream ss;
        ss << std::hex << std::uppercase << std::setfill(L'0');
        for (wchar_t c : wstr)
        {
            if (c <= 0xFF)
            {
                // Characters in the range 0x00-0xFF are represented as \xXX
                // ss << L"\\x" << std::setw(2) << static_cast<int>(c);
                ss << c;
            }
            else
            {
                // Characters outside the range 0x00-0xFF are represented as \uXXXX
                ss << L"\\u" << std::setw(4) << static_cast<int>(c);
            }
        }

        return ss.str();
    }
    static std::string ptr_wcharToString(const WCHAR *s)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<WCHAR>> converter; // Create a converter that can convert between wide and narrow character sets
        std::string str = converter.to_bytes(s);                        // Convert the WCHAR* string to a std::string
        return str;
    }
};

#endif