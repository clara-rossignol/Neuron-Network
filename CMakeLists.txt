cmake_minimum_required(VERSION 2.6)
project(NeuronNetwork)
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
endif(NOT CMAKE_BUILD_TYPE)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -W -Wall -Wextra")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
option(test "Build tests." ON)
link_directories(${CMAKE_SOURCE_DIR}/lib)

set(SOURCE_FILES src/Random.cpp src/Neuron.cpp src/Simulation.cpp src/Network.cpp)
set(PROG_NAME "NeuronNetwork")

add_executable(${PROG_NAME} src/main.cpp ${SOURCE_FILES})

if (test)
enable_testing()
find_package(GTest)
if (NOT GTEST_FOUND)
SET(GTEST_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include)
SET(GTEST_BOTH_LIBRARIES libgtest.a libgtest_main.a)
endif(NOT GTEST_FOUND)
add_executable(testNeuronNet test/test_random test/main.cpp ${SOURCE_FILES})
target_link_libraries(testNeuronNet ${GTEST_BOTH_LIBRARIES} pthread)
add_test(NeuronNetwork testNeuronNet)
endif(test)

find_package(Doxygen)
if (DOXYGEN_FOUND)
add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)

