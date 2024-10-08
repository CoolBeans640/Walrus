cmake_minimum_required(VERSION 3.16)
project(Walrus)

set(CMAKE_CXX_STANDARD 17)
include_directories("ext/glfw/include" "ext/glm" "ext/glad/include")
add_subdirectory(ext/glfw)
add_subdirectory(ext/glm)


add_executable(Walrus
    "src/main.cpp"
    "src/file.cpp"
    "src/shader.c"
    "ext/glad/src/glad.c"
)

target_link_libraries(Walrus PRIVATE glm glfw)

