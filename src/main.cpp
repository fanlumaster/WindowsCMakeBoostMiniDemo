#include <boost/locale.hpp>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <string>

int main()
{
    // Set Windows console to use UTF-16 (required by wcout)
    _setmode(_fileno(stdout), _O_U16TEXT);

    std::string utf8_str = "你好，世界！"; // UTF-8 string
    // Convert string (UTF-8) -> wstring (UTF-16)
    std::wstring wide_str = boost::locale::conv::to_utf<wchar_t>(utf8_str, "UTF-8");

    std::wcout << L"转换后的 wstring: " << wide_str << std::endl;

    return 0;
}