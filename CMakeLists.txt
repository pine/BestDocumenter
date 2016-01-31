cmake_minimum_required(VERSION 2.8)

include_directories("lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")
add_definitions("-std=c++11")
add_definitions("-DPICOJSON_USE_INT64")

file(GLOB_RECURSE src_files "src/*.cpp")
add_executable(best_documenter ${src_files})
target_link_libraries(best_documenter curl)
