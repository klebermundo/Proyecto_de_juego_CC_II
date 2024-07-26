cmake_minimum_required(VERSION 3.20)

project(SFML-Test VERSION 1.0.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}>)
set(CMAKE_CXX_STANDARD 17)

add_executable(Game_proyect R.E.Defense.cpp)
target_include_directories(Game_proyect PRIVATE "C:/SFML-2.6.1/include")
target_link_directories(Game_proyect PRIVATE "C:/SFML-2.6.1/lib")
target_link_libraries(Game_proyect LINK_PUBLIC openal32 sfml-audio sfml-network sfml-graphics sfml-window sfml-system)