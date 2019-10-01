cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(emtest)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build.emscripten)
set(SDL_FLAGS "-s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"png\"]'")

# include_directories("lib/assimp/include")

# link_directories("lib/assimp/lib-js")
# link_libraries("assimp")

file(GLOB_RECURSE CORE_HDR src/*.h)
file(GLOB_RECURSE CORE_SRC src/*.cpp)

#
# Trying usual cmake project compiler execution
#

add_definitions("-std=c++11")
add_executable(client ${CORE_SRC} ${CORE_HDR})

set_target_properties(client PROPERTIES LINK_FLAGS "-s DEMANGLE_SUPPORT=1 --preload-file ${CMAKE_SOURCE_DIR}/assets --bind ${SDL_FLAGS}")
set_target_properties(client PROPERTIES COMPILE_FLAGS "-s WASM=1 -O3 ${SDL_FLAGS}")
