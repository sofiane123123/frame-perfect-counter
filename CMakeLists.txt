cmake_minimum_required(VERSION 3.24)

project(frame_perfect_counter)

find_package(Geode REQUIRED)

add_geode_mod(
    sofianegg.frame_perfect_counter
    src/main.cpp
)
