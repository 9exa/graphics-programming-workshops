cmake_minimum_required(VERSION 4.0)
project(GPIntro)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SRC_FILES src/**.cpp)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.4 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

add_executable(hello_GP ${SRC_FILES})

target_link_libraries(hello_GP PRIVATE OpenGL::GL)
target_link_libraries(hello_GP PRIVATE glfw)
target_link_libraries(hello_GP PRIVATE GLEW::glew)
target_link_libraries(hello_GP PRIVATE glm::glm)

target_include_directories(hello_GP PRIVATE "src")
