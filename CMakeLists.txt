cmake_minimum_required(VERSION 3.16)
project(Walrus)

set(CMAKE_CXX_STANDARD 17)
# Emit a compile_commands.json for use with clangd in LSPs
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
include_directories("ext/glfw/include" "ext/glm" "ext/glad/include")
add_subdirectory(ext/glfw)
add_subdirectory(ext/glm)


add_executable(Walrus
    "src/main.cpp"
    "src/sw_framebuffer.cpp"
    "ext/glad/src/glad.c"
)

target_link_libraries(Walrus PRIVATE glm glfw)

