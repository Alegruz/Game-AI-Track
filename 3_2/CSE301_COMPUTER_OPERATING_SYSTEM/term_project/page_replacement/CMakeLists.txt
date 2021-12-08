cmake_minimum_required(VERSION 3.8)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

project(PageReplacement VERSION 0.0.1)

file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

message(STATUS ${HEADER_FILES})
message(STATUS ${SOURCE_FILES})

add_executable(PageReplacement main.c ${SOURCE_FILES} ${HEADER_FILES})

if(CMAKE_BUILD_TYPE MATCHES Debug)
	message(STATUS "BUILD TYPE: Debug")
	add_compile_definitions(DEBUG=1)
elseif (CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
	message(STATUS "BUILD TYPE: RelWithDebInfo")
	add_compile_definitions(DEVELOPMENT=1)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
	message(STATUS "BUILD TYPE: TEST")
	add_compile_definitions(TEST=1)
elseif (CMAKE_BUILD_TYPE MATCHES MinSizeRel)
	message(STATUS "BUILD TYPE: RELEASE")
	add_compile_definitions(RELEASE=1)
endif()

if(MSVC)
	target_compile_options(PageReplacement PRIVATE /W4 /WX)
else()
	target_compile_options(PageReplacement PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

if(WIN32)
	add_compile_definitions(WIN32=${WIN32})
else(UNIX)
	add_compile_definitions(UNIX=${UNIX})
endif()

if(MSVC)
	add_compile_definitions(MSVC=${MSVC})
	target_compile_options(PageReplacement PRIVATE /W4 /WX)
else()
	add_compile_definitions(CMAKE_COMPILER_IS_GNUCC=${CMAKE_COMPILER_IS_GNUCC})
	target_compile_options(PageReplacement PRIVATE -Wall -Wextra -pedantic -Werror)
endif()