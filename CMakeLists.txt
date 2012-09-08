cmake_minimum_required (VERSION 2.6.4)

project (testQueues CXX)

set (CMAKE_CXX_FLAGS "-std=c++0x -Wall -Werror -Wno-variadic-macros -pedantic")

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g -ggdb3")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")

include_directories (. )

set (Boost_USE_STATIC_LIBS ON)
find_package (Boost COMPONENTS system thread date_time REQUIRED)

set (BASE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set (CMAKE_BUILD_TYPE DEBUG)
set (CMAKE_MODULE_PATH ${BASE_PATH}/cmake)

set (TEST_SOURCES  main.cpp  StandardQueue.cpp )

add_executable (test ${TEST_SOURCES})
target_link_libraries (test
    ${Boost_LIBRARIES} 
    pthread)
