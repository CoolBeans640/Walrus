#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "sw_render.hpp"

/**
 * Starts GLFW and creates a new window
 * @return Window pointer
 */
GLFWwindow* startUp(int width, int height) {
    if(!glfwInit()) {
        printf("Failed to initialize GLFW3\n");
        return NULL;
    }
    // We want an OpenGL 3.3 Core context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window
    GLFWwindow* window = glfwCreateWindow(width, height, "Walrus", NULL, NULL);
    if(window == NULL) {
        printf("Window or OpenGL context creation failed\n");
        return NULL;
    }

    // Load OpenGL context
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glViewport(0, 0, width, height);
    glfwSwapInterval(1); // VSync

    return window;
}

/**
 * Main Function
 */
int main() {
    // Starting GLFW
    const int width = 1920;
    const int height = 1080;
    GLFWwindow* window = startUp(width, height);
    if (window == nullptr) {
        printf("Setup failed\n");
        return 1;
    }

    // Allocate framebuffer
    std::vector<char> framebuffer(width * height * 4);
    sw_framebuffer fb = sw_framebuffer(width, height, framebuffer.data());
    memset(framebuffer.data(), 0x7F, framebuffer.size());

    unsigned int frame_num = 0;
    while (!glfwWindowShouldClose(window)) {
        frame_num++;
        // Copy new software-rendered frame to screen
        fb.draw(framebuffer.data());
        memset(framebuffer.data(), frame_num % 100, framebuffer.size());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
