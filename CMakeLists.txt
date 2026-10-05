cmake_minimum_required(VERSION 3.24)

project(frame-perfect-counter)

find_package(Geode REQUIRED)

add_geode_mod(
    sofianegg.frame_counter
    src/main.cpp
)
