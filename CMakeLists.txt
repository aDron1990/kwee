cmake_minimum_required(VERSION 3.5)

project(kwee)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(3th_party/glfw)
add_subdirectory(3th_party/stb_image)
add_subdirectory(3th_party/glm)
add_subdirectory(3th_party/glad)
include_directories(include/)

file(GLOB_RECURSE sources "src/*.cpp" "src/*.c" "src/*.h" "include/*.hpp" "include/*.h")

add_compile_definitions(KWEE_BUILD)
add_library(${PROJECT_NAME} SHARED ${sources})
target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw stb_image glm glad)
target_include_directories(${PROJECT_NAME} PUBLIC include/)