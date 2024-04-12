cmake_minimum_required(VERSION 3.8)

project(Scanner)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra-semi -O3 -g -fsanitize=address -fno-omit-frame-pointer")

add_executable(main main.cpp address_port.hpp validation.hpp)
