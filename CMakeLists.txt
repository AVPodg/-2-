cmake_minimum_required(VERSION 3.12)
project(StringChecker)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Скачиваем GTest вручную в подпапку
if(NOT EXISTS ${CMAKE_SOURCE_DIR}/googletest/CMakeLists.txt)
    message(STATUS "Downloading GTest...")
    execute_process(COMMAND git clone https://github.com/google/googletest.git
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif()

# Добавляем GTest как подпроект
add_subdirectory(${CMAKE_SOURCE_DIR}/googletest)

# Основная программа
add_executable(string_checker
    src/main.cpp
    src/isvalidstring.cpp
)

target_include_directories(string_checker PRIVATE src)

# Тестовая программа
add_executable(test_checkstring
    test/test_checkstring.cpp
    src/isvalidstring.cpp
)

target_include_directories(test_checkstring PRIVATE src)
target_link_libraries(test_checkstring gtest gtest_main)

# Добавляем тесты
include(GoogleTest)
gtest_discover_tests(test_checkstring)