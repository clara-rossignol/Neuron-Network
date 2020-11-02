cmake_minimum_required ( VERSION 2.6)
project(NeuronNetwork)

if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
endif(NOT CMAKE_BUILD_TYPE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -W -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
option(test "Build tests." ON)


include_directories("team_12/include" ${CMAKE_SOURCE_DIR}/include) 
link_directories(${CMAKE_SOURCE_DIR}/lib)
add_executable()

if (test)
    enable_testing()
    find_package(GTest)
    if (NOT GTEST_FOUND)
        set(GTEST_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include)
        set(GTEST_BOTH_LIBRARIES libgtest.a libgtest_main.a)
    endif(NOT GTEST_FOUND)
    add_executable(testNTW )
    target_link_libraries(testNTW ${GTEST_BOTH_LIBRARIES} pthread)
    add_test(NeuronNetwork testNTW)
endif(test)


find_package(Doxygen)
if (DOXYGEN_FOUND)
add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)

