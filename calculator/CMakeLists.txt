cmake_minimum_required(VERSION 3.15)
project(calculator)

set(CMAKE_CXX_STANDARD 20)

if (UNIX)
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address)
endif()

file(DOWNLOAD https://raw.githubusercontent.com/onqtam/doctest/v2.4.8/doctest/doctest.h doctest.h)
add_library(doctest INTERFACE doctest.h)
target_include_directories(doctest INTERFACE ${CMAKE_CURRENT_BINARY_DIR})

add_executable(test_calculator test_calculator.cpp Expression.cpp Expression.h)
target_link_libraries(test_calculator PRIVATE doctest)

enable_testing()
add_test(NAME test_calculator COMMAND test_calculator)
