file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/1_basics/*.h")
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/1_basics/*.cpp")

add_executable(Ex1 ex1.cpp)

target_compile_options(Ex1 PRIVATE /W4 /WX)