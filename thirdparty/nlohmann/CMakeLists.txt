cmake_minimum_required(VERSION 3.12)
project(nlohmann VERSION 1.0 LANGUAGES CXX)
add_library(nlohmann INTERFACE)
target_include_directories(nlohmann INTERFACE .)

