cmake_minimum_required(VERSION 3.11)

project(pong)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

# Add SFML library
add_subdirectory("lib/SFML")
set(SFML_INCS "lib/SFML/include")
link_directories("${CMAKE_BINARY_DIR}/lib/SFML/lib")

# Custom target to copy resources (this should copy the res/ directory)
add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/res"
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res"
)

# Add the executable for Pong game
add_executable(pong main.cpp)

add_dependencies(pong copy_resources)

# Include the SFML headers
target_include_directories(pong PRIVATE ${SFML_INCS})

# Link SFML libraries
target_link_libraries(pong sfml-graphics)
