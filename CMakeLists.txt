cmake_minimum_required(VERSION 2.8.4)
project(memancpp)

add_library(
        memancpp

        Allocator.hpp
        Pool.hpp
        Pool.cpp
#        Provider.hpp
#        Provider.cpp
)
