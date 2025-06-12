#ifndef LOAD_TEXTURE_H
#define LOAD_TEXTURE_H

// Simple helper function to load an image into a OpenGL texture with common settings
bool LoadTextureFromMemory(const unsigned char* image_data, int image_data_len, GLuint* out_texture, int* out_width, int* out_height)
{
    // Load from file
    int image_width = 0;
    int image_height = 0;
    int channels = 0;
    unsigned char* image = stbi_load_from_memory(image_data, image_data_len, &image_width, &image_height, &channels, 4);
    if (image == nullptr)
        return false;
    
    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}

#endif