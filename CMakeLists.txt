cmake_minimum_required(VERSION 2.8)

include_directories("lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")
add_definitions("-std=c++11")
add_definitions("-DPICOJSON_USE_INT64")

find_package(PkgConfig)
pkg_check_modules(PC_gflags QUIET libgflags)

set(gflags_SHARED    FALSE)
set(gflags_NOTHREADS FALSE)

file(GLOB_RECURSE src_files "src/*.cpp")
add_executable(best_documenter ${src_files})
target_link_libraries(best_documenter curl gflags)

file(GLOB_RECURSE test_files "src/*/*.cpp" "test/*.cpp")
add_executable(best_documenter_test ${test_files})
target_link_libraries(best_documenter_test curl gflags)
