#include <cstring>
#include <cstdio>
#include <glad/glad.h>

#include "sw_render.hpp"

sw_framebuffer::sw_framebuffer(unsigned int width, unsigned int height, char* data) {
    // Setup as a texture for OpenGL
    unsigned int texture_id = 0;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    // glBindTexture(GL_TEXTURE_2D, 0);

    // Attach texture to framebuffer
    glGenFramebuffers(1, &this->fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

    // Sanity check
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        printf("Failed to setup framebuffer\n");
    }
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Setup for blitting later
    glBindFramebuffer(GL_READ_FRAMEBUFFER, this->fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    this->texture_id = texture_id;
    this->width = width;
    this->height = height;
}

void sw_framebuffer::draw(char* data) {
    // Update texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    // Copy software-rendered frame to screen
    glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT, GL_NEAREST);
}
