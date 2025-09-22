cmake_minimum_required(VERSION 3.12)
project(StringChecker)

# Установка стандарта C++
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск GTest
find_package(GTest REQUIRED)
include(GoogleTest)

# Добавление исполняемого файла основной программы
add_executable(string_checker
    src/main.cpp
    src/isvalidstring.cpp
    src/isvalidstring.h
)

# Добавление тестового исполняемого файла
add_executable(test_checker
    test/test_checkstring.cpp
    src/isvalidstring.cpp
    src/isvalidstring.h
)

# Указание include директорий
target_include_directories(string_checker PRIVATE src)
target_include_directories(test_checker PRIVATE src)

# Связывание тестов с Google Test
target_link_libraries(test_checker PRIVATE GTest::GTest GTest::Main)

# Добавление тестов в CTest
gtest_discover_tests(test_checker)

# Настройка компилятора
target_compile_features(string_checker PRIVATE cxx_std_14)
target_compile_options(string_checker PRIVATE -Wall -Wextra -Wpedantic)
target_compile_features(test_checker PRIVATE cxx_std_14)
target_compile_options(test_checker PRIVATE -Wall -Wextra -Wpedantic)