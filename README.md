# C++ Project - IsValidString

Объединенный проект для проверки валидности скобок с единой системой сборки, тестирования и разработки.

## Структура проекта

```
├── .devcontainer/          # Единая конфигурация devcontainer
│   ├── devcontainer.json   # Настройки контейнера
│   └── Dockerfile         # Образ для разработки
├── .vscode/               # Настройки VS Code
│   ├── tasks.json         # Задачи сборки и тестирования
│   ├── launch.json        # Конфигурации отладки
│   ├── settings.json      # Настройки редактора
│   ├── extensions.json    # Рекомендуемые расширения
│   └── cmake-kits.json    # Настройки CMake
├── src/                   # Исходный код библиотеки
│   ├── isvalidstring.h    # Заголовочный файл
│   ├── isvalidstring.cpp  # Реализация
│   ├── main.cpp          # Главная программа
│   └── test_isvalidstring.cpp # Тесты библиотеки
├── test/                  # Основные тесты
│   └── test_checkstring.cpp # Тесты Google Test
├── build/                 # Папка сборки
├── CMakeLists.txt         # Единый CMake файл
├── Makefile              # Единый Makefile
└── README.md             # Этот файл
```

## Возможности проекта

- **Единая система сборки** - один Makefile и CMakeLists.txt для всего проекта
- **Комплексное тестирование** - Google Test с 100+ тестами
- **DevContainer** - изолированная среда разработки
- **Автоматическая сборка** - проект собирается автоматически при открытии
- **Отладка** - интегрированная отладка с GDB
- **Покрытие кода** - анализ покрытия тестами

## Быстрый старт

### Использование DevContainer (Рекомендуется)

1. **Установите предварительные требования:**
   - [Docker Desktop](https://www.docker.com/products/docker-desktop)
   - [Visual Studio Code](https://code.visualstudio.com/)
   - [Dev Containers extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)

2. **Откройте проект:**
   - Откройте корневую папку проекта в VS Code
   - Нажмите `Ctrl+Shift+P` (или `Cmd+Shift+P` на Mac)
   - Выберите "Dev Containers: Reopen in Container"
   - Дождитесь сборки контейнера (первый раз может занять несколько минут)

3. **Начните разработку:**
   - Проект автоматически соберется при открытии
   - Все инструменты уже настроены и готовы к использованию

### Локальная сборка

#### Через Make
```bash
# Сборка всего проекта
make all

# Запуск программы
make run

# Запуск всех тестов
make test

# Отладочная сборка
make debug

# Релизная сборка
make release
```

#### Через CMake
```bash
# Создание папки сборки
mkdir build
cd build

# Настройка CMake
cmake ..

# Сборка
make

# Запуск тестов
ctest --output-on-failure
```

## Команды и задачи

### Make команды

| Команда | Описание |
|---------|----------|
| `make all` | Сборка всего проекта (по умолчанию) |
| `make debug` | Отладочная сборка с символами отладки |
| `make release` | Релизная сборка с оптимизацией |
| `make run` | Запуск основной программы |
| `make test` | Запуск всех тестов |
| `make test-lib` | Запуск тестов библиотеки |
| `make test-main` | Запуск основных тестов |
| `make test-verbose` | Запуск тестов с подробным выводом |
| `make test-debug` | Запуск тестов с отладчиком |
| `make test-valgrind` | Запуск тестов с проверкой памяти |
| `make test-coverage` | Запуск тестов с анализом покрытия |
| `make list-tests` | Показать список всех тестов |
| `make shared` | Сборка shared библиотеки |
| `make cmake-build` | Сборка через CMake |
| `make cmake-test` | Запуск тестов через CMake |
| `make clean` | Очистка папки сборки |
| `make info` | Показать информацию о проекте |
| `make help` | Показать справку |

### CMake команды

| Команда | Описание |
|---------|----------|
| `cmake ..` | Настройка проекта |
| `make` | Сборка проекта |
| `ctest` | Запуск тестов |
| `ctest --output-on-failure` | Запуск тестов с выводом ошибок |
| `make test_verbose` | Запуск тестов с подробным выводом |
| `make test_list` | Показать список тестов |

### VS Code задачи

После открытия в devcontainer доступны следующие задачи (`Ctrl+Shift+P` → "Tasks: Run Task"):

- **Configure CMake** - Настройка CMake
- **Build Project** - Сборка основного проекта
- **Build Tests** - Сборка тестов
- **Run Tests** - Запуск тестов
- **Run Main Program** - Запуск основной программы
- **Run CTest** - Запуск тестов через CTest
- **Clean Build** - Очистка папки сборки

## API библиотеки

### `bool isValidParentheses(std::string s)`

Проверяет, является ли строка валидной последовательностью скобок.

**Параметры:**
- `s` - строка для проверки (только символы '(' и ')')

**Возвращает:**
- `true` если строка валидна (все скобки правильно закрыты)
- `false` если строка невалидна

**Примеры использования:**
```cpp
#include "isvalidstring.h"
#include <iostream>

int main() {
    std::cout << isValidParentheses("()") << std::endl;     // true
    std::cout << isValidParentheses("()()") << std::endl;   // true
    std::cout << isValidParentheses("(())") << std::endl;   // true
    std::cout << isValidParentheses("(") << std::endl;      // false
    std::cout << isValidParentheses(")") << std::endl;      // false
    std::cout << isValidParentheses(")(") << std::endl;     // false
    return 0;
}
```

## Тестирование

### Категории тестов

1. **Базовые тесты** - простые случаи и граничные условия
2. **Тесты библиотеки** - тестирование функций библиотеки
3. **Основные тесты** - комплексные тесты с 100+ тестовыми случаями
4. **Стресс-тесты** - тесты производительности и граничных условий

### Запуск конкретных тестов

```bash
# Запуск тестов по паттерну
make test-specific PATTERN='EmptyString'

# Запуск тестов библиотеки
make test-lib

# Запуск основных тестов
make test-main

# Запуск с подробным выводом
make test-verbose
```

### Анализ покрытия кода

```bash
# Сборка с покрытием
make test-coverage

# Просмотр результатов
ls *.gcov
```

## Отладка

### Отладка основной программы
```bash
# Сборка с отладкой
make debug

# Запуск с gdb
gdb ./build/main
```

### Отладка тестов
```bash
# Запуск тестов с отладчиком
make test-debug

# Отладка конкретного теста
gdb ./build/test_checkstring
(gdb) run --gtest_filter="*TestName*"
```

## Требования

- **C++17** или выше
- **GCC/G++** или совместимый компилятор
- **CMake 3.16+** (для CMake сборки)
- **Google Test** (автоматически загружается)
- **Docker** (для devcontainer)
- **VS Code** с расширением Dev Containers (для devcontainer)

## Устранение неполадок

### Проблемы с Docker
1. Убедитесь, что Docker Desktop запущен
2. Проверьте, что у вас достаточно места на диске
3. Перезапустите Docker Desktop

### Проблемы со сборкой
1. Выполните `make clean`
2. Пересоберите проект
3. Проверьте логи в терминале

### Проблемы с тестами
1. Убедитесь, что проект собрался успешно
2. Проверьте, что Google Test загрузился корректно
3. Запустите тесты через терминал для диагностики
