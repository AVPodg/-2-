# Объединенный Makefile для всего проекта IsValidString
# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -fPIC
DEBUG_FLAGS = -g -DDEBUG
RELEASE_FLAGS = -O3 -DNDEBUG

# Директории
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build
GTEST_DIR = $(BUILD_DIR)/googletest

# Исходные файлы
LIB_SOURCES = $(SRC_DIR)/isvalidstring.cpp
MAIN_SOURCES = $(SRC_DIR)/main.cpp
TEST_SOURCES = $(TEST_DIR)/test_checkstring.cpp
LIB_TEST_SOURCES = $(SRC_DIR)/test_isvalidstring.cpp

# Объектные файлы
LIB_OBJECTS = $(LIB_SOURCES:%.cpp=$(BUILD_DIR)/%.o)
MAIN_OBJECTS = $(MAIN_SOURCES:%.cpp=$(BUILD_DIR)/%.o)
TEST_OBJECTS = $(TEST_SOURCES:%.cpp=$(BUILD_DIR)/%.o)
LIB_TEST_OBJECTS = $(LIB_TEST_SOURCES:%.cpp=$(BUILD_DIR)/%.o)

# Цели
LIBRARY = $(BUILD_DIR)/libisvalidstring.a
SHARED_LIB = $(BUILD_DIR)/libisvalidstring.so
MAIN_EXEC = $(BUILD_DIR)/main
TEST_EXEC = $(BUILD_DIR)/test_checkstring
LIB_TEST_EXEC = $(BUILD_DIR)/test_isvalidstring
GTEST_LIB = $(GTEST_DIR)/lib/libgtest.a
GTEST_MAIN_LIB = $(GTEST_DIR)/lib/libgtest_main.a

# Основные цели
.PHONY: all clean debug release test test-lib test-main run run-main test-verbose test-debug test-valgrind test-coverage list-tests cmake-build cmake-test install help

# По умолчанию собираем все
all: $(LIBRARY) $(MAIN_EXEC) $(TEST_EXEC) $(LIB_TEST_EXEC)

# Создаем директорию сборки
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Настройка Google Test
setup-gtest: $(BUILD_DIR)
	@if [ ! -d "$(GTEST_DIR)" ]; then \
		echo "Downloading and building Google Test..."; \
		cd $(BUILD_DIR) && \
		git clone https://github.com/google/googletest.git && \
		cd googletest && \
		mkdir build && cd build && \
		cmake .. && make -j$(nproc); \
	fi

# Google Test библиотеки
$(GTEST_LIB): setup-gtest
$(GTEST_MAIN_LIB): setup-gtest

# Объектные файлы библиотеки
$(BUILD_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -c $< -o $@

# Объектные файлы тестов
$(BUILD_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -I$(GTEST_DIR)/googletest/include -c $< -o $@

# Статическая библиотека
$(LIBRARY): $(LIB_OBJECTS) | $(BUILD_DIR)
	ar rcs $@ $^

# Исполняемый файл main
$(MAIN_EXEC): $(MAIN_OBJECTS) $(LIBRARY) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Исполняемый файл тестов
$(TEST_EXEC): $(TEST_OBJECTS) $(LIB_OBJECTS) $(GTEST_LIB) $(GTEST_MAIN_LIB) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ -pthread

# Исполняемый файл тестов библиотеки
$(LIB_TEST_EXEC): $(LIB_TEST_OBJECTS) $(LIB_OBJECTS) $(GTEST_LIB) $(GTEST_MAIN_LIB) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ -pthread

# Отладочная сборка
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: clean all

# Релизная сборка
release: CXXFLAGS += $(RELEASE_FLAGS)
release: clean all

# Запуск основной программы
run: $(MAIN_EXEC)
	./$(MAIN_EXEC)

# Запуск тестов библиотеки
test-lib: $(LIB_TEST_EXEC)
	./$(LIB_TEST_EXEC)

# Запуск основных тестов
test-main: $(TEST_EXEC)
	./$(TEST_EXEC)

# Запуск всех тестов
test: test-lib test-main

# Запуск тестов с подробным выводом
test-verbose: $(TEST_EXEC) $(LIB_TEST_EXEC)
	@echo "Running library tests with verbose output..."
	./$(LIB_TEST_EXEC) --gtest_verbose
	@echo "Running main tests with verbose output..."
	./$(TEST_EXEC) --gtest_verbose

# Запуск конкретного теста
test-specific: $(TEST_EXEC) $(LIB_TEST_EXEC)
	@echo "Available test patterns:"
	@echo "Library tests:"
	@./$(LIB_TEST_EXEC) --gtest_list_tests
	@echo "Main tests:"
	@./$(TEST_EXEC) --gtest_list_tests
	@echo ""
	@echo "Usage: make test-specific PATTERN='TestName'"
	@if [ -n "$(PATTERN)" ]; then \
		echo "Running library tests matching '$(PATTERN)':"; \
		./$(LIB_TEST_EXEC) --gtest_filter="*$(PATTERN)*"; \
		echo "Running main tests matching '$(PATTERN)':"; \
		./$(TEST_EXEC) --gtest_filter="*$(PATTERN)*"; \
	fi

# Запуск тестов с отладкой
test-debug: debug
	gdb ./$(TEST_EXEC)

# Запуск тестов с valgrind
test-valgrind: $(TEST_EXEC) $(LIB_TEST_EXEC)
	@echo "Running library tests with valgrind..."
	valgrind --leak-check=full --show-leak-kinds=all ./$(LIB_TEST_EXEC)
	@echo "Running main tests with valgrind..."
	valgrind --leak-check=full --show-leak-kinds=all ./$(TEST_EXEC)

# Запуск тестов с покрытием кода
test-coverage: CXXFLAGS += --coverage
test-coverage: LDFLAGS += --coverage
test-coverage: clean all
	@echo "Running tests with coverage..."
	./$(LIB_TEST_EXEC)
	./$(TEST_EXEC)
	@echo "Generating coverage report..."
	gcov $(LIB_OBJECTS) $(TEST_OBJECTS) $(LIB_TEST_OBJECTS)

# Показать список тестов
list-tests: $(TEST_EXEC) $(LIB_TEST_EXEC)
	@echo "Library tests:"
	./$(LIB_TEST_EXEC) --gtest_list_tests
	@echo ""
	@echo "Main tests:"
	./$(TEST_EXEC) --gtest_list_tests

# Сборка через CMake
cmake-build:
	@echo "Building with CMake..."
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake ..
	@cd $(BUILD_DIR) && make

# Запуск тестов через CMake
cmake-test: cmake-build
	@cd $(BUILD_DIR) && ctest --output-on-failure

# Сборка shared библиотеки
shared: $(LIB_OBJECTS) | $(BUILD_DIR)
	$(CXX) -shared -fPIC $^ -o $(SHARED_LIB)

# Очистка
clean:
	rm -rf $(BUILD_DIR)

# Полная очистка
clean-all: clean

# Установка
install: all
	@echo "Installing project..."
	@echo "Library: $(LIBRARY)"
	@echo "Main executable: $(MAIN_EXEC)"
	@echo "Test executables: $(TEST_EXEC), $(LIB_TEST_EXEC)"
	@echo "Run with sudo for system-wide installation"

# Показать информацию о проекте
info:
	@echo "=== IsValidString Project ==="
	@echo "Library Sources: $(LIB_SOURCES)"
	@echo "Main Sources: $(MAIN_SOURCES)"
	@echo "Test Sources: $(TEST_SOURCES)"
	@echo "Library Test Sources: $(LIB_TEST_SOURCES)"
	@echo "Library: $(LIBRARY)"
	@echo "Main Executable: $(MAIN_EXEC)"
	@echo "Test Executables: $(TEST_EXEC), $(LIB_TEST_EXEC)"
	@echo "Compiler: $(CXX)"
	@echo "Flags: $(CXXFLAGS)"
	@echo "Build Directory: $(BUILD_DIR)"

# Помощь
help:
	@echo "Available targets:"
	@echo "  all            - Build everything (default)"
	@echo "  debug          - Build with debug flags"
	@echo "  release        - Build with release flags"
	@echo "  run            - Build and run main program"
	@echo "  test           - Run all tests"
	@echo "  test-lib       - Run library tests only"
	@echo "  test-main      - Run main tests only"
	@echo "  test-verbose   - Run tests with verbose output"
	@echo "  test-specific  - Run specific test (use PATTERN='TestName')"
	@echo "  test-debug     - Run tests with gdb debugger"
	@echo "  test-valgrind  - Run tests with valgrind memory checker"
	@echo "  test-coverage  - Run tests with code coverage"
	@echo "  list-tests     - List all available tests"
	@echo "  shared         - Build shared library"
	@echo "  cmake-build    - Build with CMake"
	@echo "  cmake-test     - Run tests with CMake"
	@echo "  clean          - Remove build directory"
	@echo "  clean-all      - Full clean"
	@echo "  install        - Show installation instructions"
	@echo "  info           - Show project information"
	@echo "  help           - Show this help message"
