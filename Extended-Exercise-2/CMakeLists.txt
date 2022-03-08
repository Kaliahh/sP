cmake_minimum_required(VERSION 3.15)
project(calculator)

set(CMAKE_CXX_STANDARD 20)

option(ASAN "Address Sanitizer" OFF)

# turn on the warnings:
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wpedantic -Wall -Wextra)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4)
endif()

if (ASAN)
    if (UNIX)
        # Linux/Mac: GCC/Clang/Apple_Clang have the same options
        add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
        add_link_options(-fsanitize=address)
    elseif(WIN32)
        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
            add_link_options(-fsanitize=address)
            message(STATUS "Address sanitizer is probably not supported by GCC/Clang on Windows")
        elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
            add_compile_options(/fsanitize=address)
            add_link_options(/fsanitize=address)
        endif()
    endif()
endif()

file(DOWNLOAD https://raw.githubusercontent.com/onqtam/doctest/v2.4.8/doctest/doctest.h ${CMAKE_CURRENT_BINARY_DIR}/doctest.h)
add_library(doctest INTERFACE doctest.h)
target_include_directories(doctest INTERFACE ${CMAKE_CURRENT_BINARY_DIR})

add_executable(test_calculator test_calculator.cpp)
target_link_libraries(test_calculator PRIVATE doctest)

enable_testing()
add_test(NAME test_calculator COMMAND test_calculator)
