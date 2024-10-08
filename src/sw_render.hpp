class sw_framebuffer {
public:
    unsigned int texture_id;
    unsigned int width;
    unsigned int height;
    unsigned int fbo;

    sw_framebuffer(unsigned int width, unsigned int height, char* data);

    void draw(char* data);
};
