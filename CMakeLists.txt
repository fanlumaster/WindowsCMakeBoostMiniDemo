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

# Notice: we need to use CONFIG option to find SQLite3, 
# otherwise it will use CMake built-in FindSQLite3.cmake
find_package(SQLite3 REQUIRED CONFIG)
message(STATUS "SQLite3 found: ${SQLite3_FOUND}")
message(STATUS "SQLite3 config: ${SQLite3_DIR}")
message(STATUS "SQLite3 include dirs: ${SQLite3_INCLUDE_DIRS}")
message(STATUS "SQLite3 libraries: ${SQLite3_LIBRARIES}")

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

target_link_libraries(${MY_EXECUTABLE_NAME} Boost::locale fmt::fmt spdlog::spdlog SQLite3::sqlite3)