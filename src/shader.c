#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <glad/glad.h>

#include "shader.h"

// Only for the shader program (not the individual shader objects)
void program_print_log(unsigned int shader) {
    int log_size = 0;
    glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &log_size);
    
    char log_buf[0x2000] = {0};

    // If the log is really long, it won't fit in our stack array.
    if (log_size > sizeof(log_buf)) {
        printf("Abnormally large log (%d bytes) forced a heap allocation.\n", log_size);
        // Allocate enough space to store the log
        char* log_heap = calloc(1, log_size);
        if (log_heap == NULL) {
            printf("Couldn't allocate %d bytes needed to display the shader compiler's error log!\n", log_size);
            return;
        }

        glGetProgramInfoLog(shader, log_size, NULL, log_heap);
        printf("%s\n", log_heap);
        free(log_heap);
        return;
    }

    // Get the log and print it
    glGetProgramInfoLog(shader, sizeof(log_buf), NULL, log_buf);
    printf("%s\n", log_buf);
}

// Linker error checking
bool shader_link_check(unsigned int shader) {
    if (shader == 0) {
        return false;
    }
    int link_success = 0;
    glGetProgramiv(shader, GL_LINK_STATUS, &link_success);
    if (link_success) {
        return true;
    }
    printf("Failed to link shader program:\n");
    program_print_log(shader);

    return false;
}

unsigned int program_compile_src(const char* vert_src, const char* frag_src) {
    // Compile shaders
    const unsigned int vertex_shader = shader_compile_src(vert_src, GL_VERTEX_SHADER);
    const unsigned int fragment_shader = shader_compile_src(frag_src, GL_FRAGMENT_SHADER);
    if (vertex_shader == 0 || fragment_shader == 0) {
        printf("Failed to compile shaders\n");
        return 0;
    }
    const unsigned int program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    // Free the shader objects
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

unsigned int shader_compile_src(const char* src, GLenum shader_type) {
    // Create & compile shader code
    const unsigned int shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, (const GLchar* const *) &src, NULL);
    glCompileShader(shader);

    // Check for shader compile errors
    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[0x1000] = {0};
        glGetShaderInfoLog(shader, sizeof(log), NULL, log);
        printf("Failed to compile shader:\n%s\n", log);
    }
    return shader;
}
