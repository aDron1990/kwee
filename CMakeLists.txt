cmake_minimum_required(VERSION 3.5)

project(kwee VERSION 0.1)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(3th_party/glfw)
add_subdirectory(3th_party/stb_image)
add_subdirectory(3th_party/glm)
add_subdirectory(3th_party/glad)

include_directories(include/)
include_directories(3th_party/imgui/)

file(GLOB_RECURSE sources "src/*.cpp" "src/*.c" "src/*.h" "include/*.hpp" "include/*.h" "3th_party/imgui/*.cpp")

add_compile_definitions(KWEE_BUILD)
add_library(${PROJECT_NAME} STATIC ${sources})
target_link_libraries(${PROJECT_NAME} glfw stb_image glm glad)
target_include_directories(${PROJECT_NAME} PUBLIC include/)
target_include_directories(${PROJECT_NAME} PUBLIC 3th_party/imgui/)
