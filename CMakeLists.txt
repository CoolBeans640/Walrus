cmake_minimum_required(VERSION 3.16)
project(Walrus)

set(CMAKE_CXX_STANDARD 17)
include_directories("ext/glfw/include" "ext/glm")

add_subdirectory(ext/glm)
add_subdirectory(ext/glfw)

add_executable(Walrus
    "src/main.cpp"
)

target_link_libraries(Walrus PRIVATE glm glfw)

