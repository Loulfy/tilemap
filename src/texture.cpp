//
// Created by loulfy on 25/03/18.
//

#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace tx
{
    Texture::Texture(std::string filename)
    {
        int w;
        int h;
        int c;

        std::string path = ASSETS"/textures/" + filename;
        unsigned char* image = stbi_load(path.c_str(), &w, &h, &c, STBI_rgb_alpha);

        if(image == nullptr) throw(std::runtime_error("Failed to load texture"));
        LOGI << filename << " : " << w << "x" << h << " c=" << c;

        glGenTextures(1, &m_texture);

        glBindTexture(GL_TEXTURE_2D, m_texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        if(c == 3) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        else if(c == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(image);
    }

    void Texture::active(GLint location, GLint texture_unit)
    {
        glUniform1i(location, texture_unit);
        glBindTexture(GL_TEXTURE_2D, m_texture);
    }
}