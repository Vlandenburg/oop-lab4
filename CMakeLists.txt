# CMakeLists.txt

cmake_minimum_required(VERSION 3.16)
project(lab4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main src/main.cpp)

target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(run_tests tests/test.cpp)

target_include_directories(run_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# ---> НАЧАЛО ИЗМЕНЕНИЙ (Добавьте этот блок) <---

# 1. Включаем систему тестирования CTest
enable_testing()

# 2. Объявляем, что наша программа run_tests является тестом
add_test(NAME MyCoolTests COMMAND run_tests)

# ---> КОНЕЦ ИЗМЕНЕНИЙ <---