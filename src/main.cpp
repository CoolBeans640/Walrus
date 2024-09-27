#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


/**
 * Starts GLFW and creates a new window
 * @return Window pointer
 */
GLFWwindow* startUp() {
    if(!glfwInit()) {
        printf("Failed to initialize GLFW3");
        return NULL;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3.3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3.3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //Create a window
    GLFWwindow* window = glfwCreateWindow(640,480, "Walrus", NULL, NULL);
    //If window fails
    if(window == NULL){
        printf("Window or OpenGL context creation failed");
        return NULL;
    }
    //Make context current
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    return window;
}
/**
 * Main Function
 */
int main(){
    //Starting GLFW
    GLFWwindow* window = startUp();
    int width = 1000;
    int height = 1000;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    if(window == nullptr){
        printf("Window is NULL");
        return 1;
    }
    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwSwapInterval(1);
        glfwPollEvents();


    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

