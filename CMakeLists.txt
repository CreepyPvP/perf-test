cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)

project(perf-test)

# Clang deez nuts
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include debug information
set(CMAKE_BUILD_TYPE Debug)

# Add all Source Files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.cpp
)

# Add all Header Files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/include/*.h
	${CMAKE_SOURCE_DIR}/include/*.hpp
)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
