cmake_minimum_required(VERSION 3.8)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

project(SchedulingQueue VERSION 0.0.1)

file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

add_executable(SchedulingQueue main.c ${SOURCE_FILES} ${HEADER_FILES})

if(MSVC)
	target_compile_options(SchedulingQueue PRIVATE /W4 /WX)
else()
	target_compile_options(SchedulingQueue PRIVATE -Wall -Wextra -pedantic -Werror)
endif()