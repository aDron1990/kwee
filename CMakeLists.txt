cmake_minimum_required(VERSION 3.20)

project(kwee VERSION 0.1.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(GLEW_USE_STATIC_LIBS, YES)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)

add_subdirectory(3th_party/stb_image)
add_subdirectory(3th_party/glm)

include_directories(include/)
include_directories(3th_party/imgui/)

file(GLOB_RECURSE sources "src/*.cpp" "src/*.c" "src/*.h" "include/*.hpp" "include/*.h" "3th_party/imgui/*.cpp")

add_compile_definitions(KWEE_BUILD)
add_library(${PROJECT_NAME} STATIC ${sources})
target_link_libraries(${PROJECT_NAME} glfw stb_image glm glad)
target_include_directories(${PROJECT_NAME} PUBLIC include/)
target_include_directories(${PROJECT_NAME} PUBLIC 3th_party/imgui/)
target_include_directories(${PROJECT_NAME} PUBLIC ${glad_INCLUDE_DIRS})