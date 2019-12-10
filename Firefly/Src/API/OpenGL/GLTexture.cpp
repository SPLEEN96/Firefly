#define FFLY_API_OPENGL
#ifdef FFLY_API_OPENGL
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "Rendering/Texture.h"
namespace Firefly {
namespace Rendering {
void Texture::Bind(uint32 texture_no) {
    if (texture_no == 0) {
        glActiveTexture(GL_TEXTURE0);
    } else if (texture_no == 1) {
        glActiveTexture(GL_TEXTURE1);
    } else if (texture_no == 2) {
        glActiveTexture(GL_TEXTURE2);
    } else if (texture_no == 3) {
        glActiveTexture(GL_TEXTURE3);
    }
    glBindTexture(GL_TEXTURE_2D, m_handle);
}
} // namespace Rendering

/* === FACTORY === */
namespace Factory {
namespace Texture {
Rendering::Texture* Create(const char* filename, bool repeat) {
    int            width, height, nb_components;
    unsigned char* data = stbi_load(filename, &width, &height, &nb_components, 0);

    uint32 texture_handle;
    glGenTextures(1, &texture_handle);

    if (data) {
        GLenum format;
        if (nb_components == 1) {
            format = GL_RED;
        } else if (nb_components == 3) {
            format = GL_RGB;
        } else if (nb_components == 4) {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, texture_handle);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        if (repeat) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        } else {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }
    } else {
        FFLY_LOG_CORE_ERROR("Failed to load Texture at path: {0}", filename);
    }

    stbi_image_free(data);

    Rendering::Texture* texture = new Rendering::Texture();
    texture->SetHandleAPI(texture_handle);

    return texture;
}
} // namespace Texture
} // namespace Factory
} // namespace Firefly

#endif