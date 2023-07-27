project(demo)
cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message("CMAKE_C_COMPILER: " ${CMAKE_C_COMPILER})
message("CMAKE_CXX_COMPILER: " ${CMAKE_CXX_COMPILER})

#Find PkgConfig
find_package(PkgConfig REQUIRED)
#Search Moudle
pkg_search_module(SDL REQUIRED SDL2)

aux_source_directory(./src SRC_DIR)

include_directories(${SDL_INCLUDE_DIRS} ./include /Library/Devp/Logger/include)
link_directories(${SDL_LIBRARY_DIRS} /Library/Devp/Logger/lib)

message("SRC_DIR" ${SRC_DIR})
message("SDL_INCLUDE_DIRS: " ${SDL_INCLUDE_DIRS})

add_executable(demo main.cpp ${SRC_DIR})
# add_executable(demo main.cpp ${SRC_DIR})

target_link_libraries(demo ${SDL_LIBRARIES} liblogger.a)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
