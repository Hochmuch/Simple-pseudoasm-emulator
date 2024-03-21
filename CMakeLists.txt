cmake_minimum_required(VERSION 3.25)
project(emulator2)

set(CMAKE_CXX_STANDARD 17)

add_executable(emulator2 main.cpp)

add_subdirectory(stack)
add_subdirectory(emulator)
add_subdirectory(parser)
add_subdirectory(preprocessor)
add_subdirectory(commands)
add_subdirectory(memory)
add_subdirectory(exceptions)

target_link_libraries(emulator2 PRIVATE preprocessor stack emulator commands memory exceptions)
