cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(Douglas-Peucher_exapmle)

add_executable(Douglas-Peucher Douglas-Peucher.cpp)
target_link_libraries(Douglas-Peucher visualization ${GMP_LIBRARIES})

