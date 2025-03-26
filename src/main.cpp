#define SPDLOG_WCHAR_TO_UTF8_SUPPORT

#include "fmt/core.h"
#include "fmt/xchar.h"
#include "spdlog/spdlog.h"
#include <boost/locale.hpp>
#include <fcntl.h>
#include <filesystem>
#include <io.h>
#include <iostream>
#include <spdlog/sinks/basic_file_sink.h>
#include <string>

int main()
{
    // Set Windows console to use UTF-16 (required by wcout)
    _setmode(_fileno(stdout), _O_U16TEXT);

    std::string utf8_str = "你好，世界！"; // UTF-8 string
    // Convert string (UTF-8) -> wstring (UTF-16)
    std::wstring wide_str = boost::locale::conv::to_utf<wchar_t>(utf8_str, "UTF-8");

    std::wcout << L"转换后的 wstring: " << wide_str << std::endl;

    std::wcout << std::filesystem::current_path().wstring() << std::endl;

    std::wcout << fmt::format(L"Hello, {}!", L"world") << std::endl;

    // std::cout << "Hello, world!" << std::endl;

    // spdlog::info("what's up?");
    auto logger = spdlog::basic_logger_mt("file_logger", "log.txt");
    spdlog::set_default_logger(logger);
    spdlog::info("what's up?");
    return 0;
}