//
// Created by loulfy on 25/03/18.
//

#ifndef TILEMAP_TEXTURE_HPP
#define TILEMAP_TEXTURE_HPP

#include <glad/glad.h>
#include <plog/Log.h>
#include <stdexcept>
#include <string>

namespace tx
{
    class Texture
    {
    public:

        explicit Texture(std::string filename);
        ~Texture() { glDeleteTextures(1, &m_texture); }

        void active(GLint location, GLint texture_unit);

    private:

        GLuint m_texture;
    };
}

#endif //TILEMAP_TEXTURE_HPP
