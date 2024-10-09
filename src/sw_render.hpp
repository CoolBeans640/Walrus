/// @brief Framebuffer handling for software rendering
///
/// This class lets you display a custom RGBA framebuffer to the screen using
/// OpenGL. No shaders are involved, because the data is copied directly (as
/// much as is possible in OpenGL) to the main framebuffer.
///
/// @author Alex Hiatt
class sw_framebuffer {
public:
    unsigned int width;
    unsigned int height;
    unsigned int texture_id;
    unsigned int fbo;

    /// @param width Software framebuffer width
    /// @param height Software framebuffer height
    sw_framebuffer(unsigned int width, unsigned int height);
    ~sw_framebuffer();

    /// Uploads framebuffer to GPU texture, then copies it to the main framebuffer.
    /// @param data RGBA framebuffer data, at least width * height * 4 bytes.
    /// @param width OpenGL viewport width
    /// @param height OpenGL viewport height
    void blit_and_display(char* data, unsigned int window_width, unsigned int window_height);
};
