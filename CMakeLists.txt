cmake_minimum_required(VERSION 3.1.0)

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

add_executable(BoxCutter ${CMAKE_SOURCE_DIR}/tools/BoxCutter.cpp)
target_link_libraries(BoxCutter -lneurostr -lpthread -lboost_filesystem -lboost_program_options)
add_dependencies(BoxCutter neurostr)

add_executable(BranchFeatureExtractor ${CMAKE_SOURCE_DIR}/tools/BranchFeatureExtractor.cpp)
target_link_libraries(BranchFeatureExtractor -lneurostr -lpthread -lboost_filesystem -lboost_program_options)
add_dependencies(BranchFeatureExtractor neurostr)

add_executable(NeuriteFeatureExtractor ${CMAKE_SOURCE_DIR}/tools/NeuriteFeatureExtractor.cpp)
target_link_libraries(NeuriteFeatureExtractor -lneurostr -lpthread -lboost_filesystem -lboost_program_options)
add_dependencies(NeuriteFeatureExtractor neurostr)

add_executable(NeuroConverter ${CMAKE_SOURCE_DIR}/tools/NeuroConverter.cpp)
target_link_libraries(NeuroConverter -lneurostr -lpthread -lboost_filesystem -lboost_program_options)
add_dependencies(NeuroConverter neurostr)

add_executable(Scholl ${CMAKE_SOURCE_DIR}/tools/Scholl.cpp)
target_link_libraries(Scholl -lneurostr -lpthread -lboost_filesystem -lboost_program_options)
add_dependencies(Scholl neurostr)

add_executable(Validator ${CMAKE_SOURCE_DIR}/tools/Validator.cpp)
target_link_libraries(Validator -lneurostr -lpthread -lboost_filesystem -lboost_program_options)

add_custom_target(tools DEPENDS 
                    BoxCutter 
                    BranchFeatureExtractor
                    NeuriteFeatureExtractor
                    NeuroConverter
                    Scholl
                    Validator)
