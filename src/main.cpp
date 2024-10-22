/// @author Alex Ruffini
/// @author Alex Hiatt

#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "sw_framebuffer.hpp"

// GLFW only provides a callback for this, and the only way to communicate the
// new size back to the main program is via global variables. We use an atomic
// value in case the callback is triggered by another thread.
int gl_width = 1920;
int gl_height = 1080;
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    gl_width = width;
    gl_height = height;
    glViewport(0, 0, width, height);
}

/**
 * Starts GLFW & OpenGL, creates a new window
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
    glfwSwapInterval(1); // Enable VSync
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}

int main() {
    // Dimensions for the software renderer (might vary from window size)
    const int sw_width = gl_width;
    const int sw_height = gl_height;

    // Starting GLFW
    GLFWwindow* window = startUp(sw_width, sw_height);
    if (window == nullptr) {
        printf("Setup failed\n");
        return 1;
    }
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    gl_width = mode->width;
    gl_height = mode->height;
    glViewport(0, 0, gl_width, gl_height);

    // This scope forces the software framebuffer to be destroyed before GLFW
    // terminates & destroys the OpenGL context, so the resources can be
    // deleted correctly.
    {
        // Allocate framebuffer & set up for blitting
        std::vector<char> framebuffer(sw_width * sw_height * 4);
        sw_framebuffer fb = sw_framebuffer(framebuffer.data(), sw_width, sw_height);

        unsigned int frame_num = 0;
        while (!glfwWindowShouldClose(window)) {
            char title[256] = {0};
            sprintf(title, "Walrus [%ux%u]", gl_width, gl_height);
            glfwSetWindowTitle(window, title);

            frame_num++;
            // Copy new software-rendered frame to GPU to be rendered
            memset(framebuffer.data(), frame_num % 100, framebuffer.size());
            // Framebuffer blit needs viewport size to scale to window correctly
            fb.blit_and_display(framebuffer.data(), gl_width, gl_height);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
