cmake_minimum_required(VERSION 3.25.0)
project(WinCMakeBoostMiniDemo VERSION 1.0 LANGUAGES CXX)

cmake_policy(SET CMP0167 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(Boost_ROOT "C:/Users/SonnyCalcr/scoop/apps/boost/1.87.0")
set (Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS locale)

set(CMAKE_PREFIX_PATH "C:/Users/SonnyCalcr/EDisk/CppCodes/Libraries/AllLibs")
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_definitions(
    /D_UNICODE=1
    /DUNICODE=1
)

include_directories("./includes/")

set(MY_EXECUTABLE_NAME "WinCMakeBoostMiniDemo")
set(
  SOURCE_FILES
  "./src/main.cpp"
)

add_executable(${MY_EXECUTABLE_NAME} ${SOURCE_FILES})

target_link_libraries(${MY_EXECUTABLE_NAME} Boost::locale fmt::fmt spdlog::spdlog)