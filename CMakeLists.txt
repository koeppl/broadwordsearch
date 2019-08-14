cmake_minimum_required(VERSION 3.0.2)
project (broadwordsearch)


if(NOT CMAKE_BUILD_TYPE)
    #set(CMAKE_BUILD_TYPE "Release")
    set(CMAKE_BUILD_TYPE "Debug")
endif(NOT CMAKE_BUILD_TYPE)

set(CXX_STANDARD gnu++17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -march=native -std=${CXX_STANDARD} ")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -ggdb -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC")
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG -mtune=native")

include_directories(include)
add_subdirectory(external/bit_span)
include_directories(external/bit_span/include)


##########
# library
##########

install(FILES broadword.hpp DESTINATION include)


##########
# TESTS
##########

FIND_LIBRARY(GLOG_LIBRARY glog)
FIND_PATH(GLOG_INCLUDE_DIR "glog/logging.h")

find_package(GTest)
include_directories(${GTEST_INCLUDE_DIR})

add_executable  (broadtest test.cpp)

target_link_libraries(broadtest gtest pthread ${GLOG_LIBRARY})

enable_testing()
add_test(NAME broadtest COMMAND broadtest)

##########
# celero benchmarks
##########

set(NO_CELERO 0)
find_path(CELERO_INCLUDE_DIR celero/Celero.h)
find_library(CELERO_LIB libcelero.so)
if(CELERO_INCLUDE_DIR STREQUAL "CELERO_INCLUDE_DIR-NOTFOUND" OR CELERO_LIB_DIR STREQUAL "CELERO_LIB-NOTFOUND")
	set(NO_CELERO 1)
	add_definitions(-DNO_CELERO=1)
else()
	include_directories(${CELERO_INCLUDE_DIR})
endif()

if(NO_CELERO EQUAL 0)
    add_executable(bench bench.cpp)
    target_link_libraries(bench ${CELERO_LIB} glog)
endif()


MESSAGE( STATUS "With Celero?: " ${CELERO_INCLUDE_DIR} ${CELERO_LIB_DIR} )
MESSAGE( STATUS "With Gtest?: " ${GTEST_INCLUDE_DIR} )
MESSAGE( STATUS "Built Type: " ${CMAKE_BUILD_TYPE} )
MESSAGE( STATUS "CXX Flags: " ${CMAKE_CXX_FLAGS} )
