cmake_minimum_required(VERSION 3.16)
project(z LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

add_library(l1 SHARED a.cc)
add_executable(main main.cc)
target_link_libraries(main l1)
