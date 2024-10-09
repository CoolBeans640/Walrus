#include <cstring>
#include <cstdio>
#include <glad/glad.h>

#include "sw_framebuffer.hpp"

sw_framebuffer::sw_framebuffer(unsigned int width, unsigned int height) {
    // Setup as a texture for OpenGL
    unsigned int texture_id = 0;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    // Set appropriate texture settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // We skip on uploading texture data, since that happens before drawing.
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind, to be polite :)

    // Attach texture to framebuffer, so that our texture is used as the color
    glGenFramebuffers(1, &this->fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

    // Sanity check
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        // I don't know of a way to communicate failure from a constructor...
        printf("Failed to setup framebuffer\n");
    }
    // Unbind for politeness, even though we're the only ones touching OpenGL
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    this->texture_id = texture_id;
    this->width = width;
    this->height = height;
}

sw_framebuffer::~sw_framebuffer() {
    // Framebuffer must not be bound to anything when we delete it
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    glDeleteFramebuffers(1, &this->fbo);
    glDeleteTextures(1, &this->texture_id);
}

void sw_framebuffer::blit_and_display(char* data, unsigned int window_width, unsigned int window_height) {
    // To be safe, we set all the relevant OpenGL objects active every time.
    // This probably has a very slight (imperceptible) performance impact.
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo); // Source is custom framebuffer
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // Target is default framebuffer

    // Upload current framebuffer texture to GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    // Copy our custom framebuffer to the main one to be displayed
    glBlitFramebuffer(0, 0, width, height, 0, 0, window_width, window_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}
