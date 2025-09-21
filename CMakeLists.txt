cmake_minimum_required(VERSION 3.16)
project(IsValidString VERSION 1.0.0 LANGUAGES CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Опции проекта
option(BUILD_TESTS "Build tests" ON)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(BUILD_TEST_COVERAGE "Build with code coverage" OFF)
option(BUILD_LIBRARY_TESTS "Build library tests" ON)
option(BUILD_MAIN_TESTS "Build main tests" ON)

# Включаем тестирование
if(BUILD_TESTS)
    enable_testing()
endif()

# Устанавливаем глобальные настройки
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Настройки для покрытия кода
if(BUILD_TEST_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# Подключаем Google Test
if(BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9fd7180a6f2653805e6440e.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

# Создаем библиотеку isvalidstring
add_library(isvalidstring 
    src/isvalidstring.cpp
)

# Устанавливаем include директории
target_include_directories(isvalidstring PUBLIC src)

# Устанавливаем свойства библиотеки
set_target_properties(isvalidstring PROPERTIES
    VERSION 1.0.0
    SOVERSION 1
    PUBLIC_HEADER src/isvalidstring.h
)

# Создаем исполняемый файл main
add_executable(main src/main.cpp)
target_link_libraries(main isvalidstring)
target_include_directories(main PRIVATE src)

# Создаем тесты библиотеки
if(BUILD_TESTS AND BUILD_LIBRARY_TESTS)
    add_executable(test_isvalidstring src/test_isvalidstring.cpp)
    target_link_libraries(test_isvalidstring isvalidstring gtest_main)
    target_include_directories(test_isvalidstring PRIVATE src)
    
    # Регистрируем тесты
    include(GoogleTest)
    gtest_discover_tests(test_isvalidstring)
endif()

# Создаем основные тесты
if(BUILD_TESTS AND BUILD_MAIN_TESTS)
    add_executable(test_checkstring test/test_checkstring.cpp)
    target_link_libraries(test_checkstring isvalidstring gtest_main)
    target_include_directories(test_checkstring PRIVATE src)
    
    # Регистрируем тесты
    include(GoogleTest)
    gtest_discover_tests(test_checkstring)
endif()

# Дополнительные цели для тестирования
if(BUILD_TESTS)
    add_custom_target(run_all_tests
        COMMAND test_isvalidstring
        COMMAND test_checkstring
        DEPENDS test_isvalidstring test_checkstring
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running all tests"
    )
    
    add_custom_target(test_verbose
        COMMAND test_isvalidstring --gtest_verbose
        COMMAND test_checkstring --gtest_verbose
        DEPENDS test_isvalidstring test_checkstring
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running tests with verbose output"
    )
    
    add_custom_target(test_list
        COMMAND test_isvalidstring --gtest_list_tests
        COMMAND test_checkstring --gtest_list_tests
        DEPENDS test_isvalidstring test_checkstring
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Listing all available tests"
    )
endif()

# Установка
install(TARGETS isvalidstring main
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

if(BUILD_TESTS)
    install(TARGETS test_isvalidstring test_checkstring
        RUNTIME DESTINATION bin
    )
endif()

install(FILES src/isvalidstring.h DESTINATION include)

# Создаем пакет
include(CPack)
