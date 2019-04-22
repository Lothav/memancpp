cmake_minimum_required(VERSION 2.8.4)
set (CMAKE_CXX_STANDARD 14)

project(memancpp)

add_library(memancpp Allocator.hpp Pool.hpp)
set_target_properties(memancpp PROPERTIES LINKER_LANGUAGE CXX)
