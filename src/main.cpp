#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
int main(){
    // Starting GLFW
    const int width = 1000;
    const int height = 1000;
    GLFWwindow* window = startUp(width, height);
    if(window == nullptr) {
        printf("Setup failed\n");
        return 1;
    }

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

