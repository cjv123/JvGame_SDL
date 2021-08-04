cmake_minimum_required(VERSION 3.20)
project(JvGame_SDL)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wno-c++11-narrowing")

include_directories(/usr/local/include/ /usr/local/include/SDL2)
link_directories(/usr/local/lib/)
file(GLOB_RECURSE SRC_LIST ./JvGame/*.cpp)

add_executable(JvGame_SDL ${SRC_LIST})
target_link_libraries(JvGame_SDL SDL2 SDL2_image SDL2_ttf SDL2_mixer)
