cmake_minimum_required(VERSION 3.10)
project(Mergesort)

# Setting compiler flags

option(PGO_INSTALL "Build using profile guided optimization (use -fprofile-use if ON, -fprofile-generate if OFF)" OFF)

if(PGO_INSTALL)
  message(STATUS "Building with -fprofile-use=../profile")
  set(PGO_FLAGS "-fprofile-use=../profile")
else()
  message(STATUS "Building with -fprofile-generate=./profile")
  set(PGO_FLAGS "-fprofile-generate=profile")
endif()

add_compile_options(-Wall -Wextra -Wpedantic -lto -O2 -g)

# Generate utils library
add_library(utils SHARED src/utils.cpp)

# Generate Mergesort libraries
add_library(mergesort_default SHARED src/mergesort_default.cpp)
add_library(mergesort_one_malloc SHARED src/mergesort_one_malloc.cpp)
add_library(mergesort_frag SHARED src/mergesort_frag.cpp)

target_link_libraries(mergesort_default PUBLIC utils)
target_link_libraries(mergesort_one_malloc PUBLIC utils)
target_link_libraries(mergesort_frag PUBLIC utils)

target_link_libraries(mergesort_default PRIVATE gcov)
target_link_libraries(mergesort_one_malloc PRIVATE gcov)
target_link_libraries(mergesort_frag PRIVATE gcov)

target_compile_options(mergesort_default PRIVATE ${PGO_FLAGS})
target_compile_options(mergesort_one_malloc PRIVATE ${PGO_FLAGS})
target_compile_options(mergesort_frag PRIVATE ${PGO_FLAGS})

# Generate std comparison libraries
add_library(stdsort SHARED src/stdsort.cpp)
add_library(stdstablesort SHARED src/stdstablesort.cpp)
target_link_libraries(stdsort PRIVATE gcov)
target_link_libraries(stdstablesort PRIVATE gcov)
target_compile_options(stdsort PRIVATE ${PGO_FLAGS})
target_compile_options(stdstablesort PRIVATE ${PGO_FLAGS})
 
# Generate Benchmark
add_executable(benchmark src/benchmark.cpp)
target_link_libraries(benchmark PUBLIC mergesort_default)
# target_link_libraries(benchmark PRIVATE gcov)
# target_compile_options(benchmark PRIVATE ${PGO_FLAGS})

# Generate Test suite
find_package(Catch2 3 REQUIRED)
add_executable(test src/tests.cpp)
target_link_libraries(test PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test PUBLIC mergesort_default)
target_link_libraries(test PUBLIC utils)

