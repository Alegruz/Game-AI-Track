cmake_minimum_required(VERSION 3.8)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

project(Scheduler VERSION 0.0.1)

file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

add_executable(Scheduler main.c ${SOURCE_FILES} ${HEADER_FILES})

message(STATUS "BUILD TYPE: ${CMAKE_C_FLAGS_DEBUG}")

if(WIN32)
	add_compile_definitions(WIN32=${WIN32})
else(UNIX)
	add_compile_definitions(UNIX=${UNIX})
endif()

if(MSVC)
	add_compile_definitions(MSVC=${MSVC})
	target_compile_options(Scheduler PRIVATE /W4 /WX)
else()
	add_compile_definitions(CMAKE_COMPILER_IS_GNUCC=${CMAKE_COMPILER_IS_GNUCC})
	target_compile_options(Scheduler PRIVATE -Wall -Wextra -pedantic -Werror)
endif()