cmake_minimum_required(VERSION 3.2.0)

if (UNIX)
  find_package(PkgConfig)
endif(UNIX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Workspace name
project(NeuroSTR)



# This setting is useful for providing JSON file used by CodeLite for code completion
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)


set(CONFIGURATION_NAME ${CMAKE_BUILD_TYPE})

# Projects


# Top project
# Define some variables
set(PROJECT_PATH "${CMAKE_SOURCE_DIR}/")


# Set default locations
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Copy headers and stuff
file(COPY ./include DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY ./bundled/ DESTINATION ${CMAKE_BINARY_DIR}/include)

# Find boost
find_package(Boost 1.62.0 REQUIRED 
              filesystem
              program_options )

# Find eigen3
find_package( Eigen3 REQUIRED )

if(${EIGEN3_FOUND})
  message( STATUS "Eigen 3 found at ${EIGEN3_INCLUDE_DIR}")
endif()

include_directories(
    .
    ./include
    ./bundled
    ${Boost_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)

link_directories(
  ${Boost_LIBRARY_DIRS}
)


# Compiler options
add_definitions(
    -DBOOST_SYSTEM_NO_DEPRECATED
    -DEIGEN_MPL2_ONLY
)

if(WIN32)
    # Resource options
endif(WIN32)

# Library path
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS} -L. ")

# Define the library sources
set ( LIB_CXX_SRCS
    ${CMAKE_SOURCE_DIR}/src/core/branch.cpp
    ${CMAKE_SOURCE_DIR}/src/core/contour.cpp
    ${CMAKE_SOURCE_DIR}/src/core/geometry.cpp
    ${CMAKE_SOURCE_DIR}/src/core/log.cpp
    ${CMAKE_SOURCE_DIR}/src/core/neurite.cpp
    ${CMAKE_SOURCE_DIR}/src/core/neurite_type.cpp
    ${CMAKE_SOURCE_DIR}/src/core/neuron.cpp
    ${CMAKE_SOURCE_DIR}/src/core/node.cpp
    ${CMAKE_SOURCE_DIR}/src/core/property.cpp
    ${CMAKE_SOURCE_DIR}/src/io/ASCParser.cpp
    ${CMAKE_SOURCE_DIR}/src/io/DATParser.cpp
    ${CMAKE_SOURCE_DIR}/src/io/JSONParser.cpp
    ${CMAKE_SOURCE_DIR}/src/io/JSONWriter.cpp
    ${CMAKE_SOURCE_DIR}/src/io/nl_structure.cpp
    ${CMAKE_SOURCE_DIR}/src/io/parser_dispatcher.cpp
    ${CMAKE_SOURCE_DIR}/src/io/SWCParser.cpp
    ${CMAKE_SOURCE_DIR}/src/io/SWCWriter.cpp
    ${CMAKE_SOURCE_DIR}/src/methods/boxCutter.cpp
    ${CMAKE_SOURCE_DIR}/src/methods/branchComparison.cpp
    ${CMAKE_SOURCE_DIR}/src/methods/scholl.cpp
    ${CMAKE_SOURCE_DIR}/src/methods/triContour.cpp
    ${CMAKE_SOURCE_DIR}/src/validator/validator.cpp
)


# Define the library compile flags
if(${CONFIGURATION_NAME} STREQUAL "Release")
set_source_files_properties(
    ${LIB_CXX_SRCS} PROPERTIES COMPILE_FLAGS 
    " -O3 -std=c++14")
else()
set_source_files_properties(
    ${LIB_CXX_SRCS} PROPERTIES COMPILE_FLAGS 
    " -O0 -std=c++14 -Wall")
endif()


if(WIN32)
    enable_language(RC)
    set(CMAKE_RC_COMPILE_OBJECT
        "<CMAKE_RC_COMPILER> ${RC_OPTIONS} -O coff -i <SOURCE> -o <OBJECT>")
endif(WIN32)

# Add neurostr target
add_library(neurostr ${LIB_CXX_SRCS})
target_link_libraries(neurostr -lpthread -lboost_filesystem)
set_property(TARGET neurostr PROPERTY CXX_STANDARD 14)
set_property(TARGET neurostr PROPERTY CXX_STANDARD_REQUIRED ON)



# Tools

# Define the library sources
set (TOOL_SRC_DIR "${CMAKE_SOURCE_DIR}/tools")
set ( TOOLS_CXX_SRCS
    ${TOOL_SRC_DIR}/BoxCutter.cpp
    ${TOOL_SRC_DIR}/BranchFeatureExtractor.cpp
    ${TOOL_SRC_DIR}/NeuriteFeatureExtractor.cpp
    ${TOOL_SRC_DIR}/NeuroConverter.cpp
    ${TOOL_SRC_DIR}/Scholl.cpp
    ${TOOL_SRC_DIR}/Validator.cpp
)

# Define the Tools compile flags
if(${CONFIGURATION_NAME} STREQUAL "Release")
set_source_files_properties(
    ${TOOLS_CXX_SRCS} PROPERTIES COMPILE_FLAGS 
    " -O3 -std=c++14")
else()
set_source_files_properties(
    ${TOOLS_CXX_SRCS} PROPERTIES COMPILE_FLAGS 
    " -O0 -std=c++14 -Wall")
endif()

link_directories( ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY} )

add_executable(BoxCutter EXCLUDE_FROM_ALL ${CMAKE_SOURCE_DIR}/tools/BoxCutter.cpp)
target_link_libraries(BoxCutter -lneurostr -lpthread -lboost_filesystem -lboost_program_options)
add_dependencies(BoxCutter neurostr)

add_executable(BranchFeatureExtractor EXCLUDE_FROM_ALL ${CMAKE_SOURCE_DIR}/tools/BranchFeatureExtractor.cpp)
target_link_libraries(BranchFeatureExtractor -lneurostr -lpthread -lboost_filesystem -lboost_program_options)
add_dependencies(BranchFeatureExtractor neurostr)

add_executable(NeuriteFeatureExtractor EXCLUDE_FROM_ALL ${CMAKE_SOURCE_DIR}/tools/NeuriteFeatureExtractor.cpp)
target_link_libraries(NeuriteFeatureExtractor -lneurostr -lpthread -lboost_filesystem -lboost_program_options)
add_dependencies(NeuriteFeatureExtractor neurostr)

add_executable(NeuroConverter EXCLUDE_FROM_ALL ${CMAKE_SOURCE_DIR}/tools/NeuroConverter.cpp)
target_link_libraries(NeuroConverter -lneurostr -lpthread -lboost_filesystem -lboost_program_options)
add_dependencies(NeuroConverter neurostr)

add_executable(Scholl EXCLUDE_FROM_ALL ${CMAKE_SOURCE_DIR}/tools/Scholl.cpp)
target_link_libraries(Scholl -lneurostr -lpthread -lboost_filesystem -lboost_program_options)
add_dependencies(Scholl neurostr)

add_executable(Validator EXCLUDE_FROM_ALL ${CMAKE_SOURCE_DIR}/tools/Validator.cpp)
target_link_libraries(Validator -lneurostr -lpthread -lboost_filesystem -lboost_program_options)
add_dependencies(Validator neurostr)

add_custom_target(tools ALL DEPENDS make c
                    BoxCutter 
                    BranchFeatureExtractor
                    NeuriteFeatureExtractor
                    NeuroConverter
                    Scholl
                    Validator)

## TESTS
set( TEST_SRC_DIR ${CMAKE_SOURCE_DIR}/test/src)

# Define test sources
set ( TEST_CXX_SRCS
    ${TEST_SRC_DIR}/core/branch_test.cpp
    ${TEST_SRC_DIR}/core/contour_test.cpp
    ${TEST_SRC_DIR}/core/geometry_test.cpp
    ${TEST_SRC_DIR}/core/neurite_test.cpp
    ${TEST_SRC_DIR}/core/neuron_test.cpp
    ${TEST_SRC_DIR}/core/node_test.cpp
    ${TEST_SRC_DIR}/core/property_test.cpp
    ${TEST_SRC_DIR}/core/reconstruction_test.cpp
    ${TEST_SRC_DIR}/io/io_asc_parser.cpp
    ${TEST_SRC_DIR}/io/io_swc_parser.cpp
    ${TEST_SRC_DIR}/io/JSONParser_test.cpp
    ${CMAKE_SOURCE_DIR}/test/main.cpp
)




# Define the test compile flags
if(${CONFIGURATION_NAME} STREQUAL "Release")
set_source_files_properties(
    ${TEST_CXX_SRCS} PROPERTIES COMPILE_FLAGS 
    " -O3 -std=c++14")
else()
set_source_files_properties(
    ${TEST_CXX_SRCS} PROPERTIES COMPILE_FLAGS 
    " -O0 -std=c++14 -Wall")
endif()

## Find Unittest++
#find_package( FindUnitTestcpp REQUIRED )
include(FindUnitTest++)
if( NOT ${UNITTESTCPP_FOUND})
  message( WARNING "Unittest++ library not found - test cannot be compiled")
else()
    # Add unittest paths
    link_directories(
      ${Boost_LIBRARY_DIRS}
      ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
      ${UNITTEST++_LIBRARY}
    )
    
    # Includes..
    include_directories(
      .
      ./include
      ./bundled
      ${Boost_INCLUDE_DIRS}
      ${EIGEN3_INCLUDE_DIR}
      ${UNITTEST++_INCLUDE_DIR}
    )

    # Create test target exec
    add_executable(neurostr_test EXCLUDE_FROM_ALL ${TEST_CXX_SRCS} )
    target_link_libraries(neurostr_test -lneurostr -lpthread -lUnitTest++)
    set_target_properties( neurostr_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/test)
    
    
    # Create run test
    
    # Set test data var
    set(ENV{NSTR_TEST_DIR} ${CMAKE_SOURCE_DIR}/test/)
    add_custom_target( run_test 
                       COMMAND neurostr_test
                       DEPENDS neurostr_test
                       WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test )
  
endif()
