cmake_minimum_required(VERSION 3.9)
project(tilemap)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(libs/glfw)

set(CMAKE_CXX_STANDARD 17)

include_directories(libs/glfw/include libs/plog/include libs/glm libs/glad/include libs/stb)

add_definitions(-DASSETS=\"${PROJECT_SOURCE_DIR}/assets\")

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS src/*.hpp)

add_executable(tilemap ${SOURCES} ${HEADERS} libs/glad/src/glad.c)
target_link_libraries(tilemap glfw)