//
// Created by loulfy on 25/03/18.
//

#ifndef TILEMAP_SHADER_HPP
#define TILEMAP_SHADER_HPP

// SOURCE : https://github.com/Polytonic/Glitter/blob/master/Samples/shader.hpp

#include <glad/glad.h>
#include <plog/Log.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <fstream>
#include <memory>
#include <string>

namespace tx
{
    class Shader
    {
    public:

        // Implement Custom Constructor and Destructor
        Shader() { m_program = glCreateProgram(); }
        ~Shader() { glDeleteProgram(m_program); }

        // Public Member Functions
        Shader & use();
        Shader & attach(std::string const & filename);
        GLuint   create(std::string const & filename);
        GLuint   get() { return m_program; }
        Shader & link();

        // Wrap Calls to glUniform
        void bind(unsigned int location, float value);
        void bind(unsigned int location, glm::vec2 const & vector);
        void bind(unsigned int location, glm::mat4 const & matrix);
        template<typename T> Shader & bind(std::string const & name, T&& value)
        {
            int location = glGetUniformLocation(m_program, name.c_str());
            if (location == -1) fprintf(stderr, "Missing Uniform: %s\n", name.c_str());
            else bind(location, std::forward<T>(value));
            return *this;
        }

        int location(std::string name) { return glGetUniformLocation(m_program, name.c_str());}

    private:

        // Disable Copying and Assignment
        Shader(Shader const &) = delete;
        Shader & operator=(Shader const &) = delete;

        // Private Member Variables
        GLuint m_program;
        GLint  m_status;
        GLint m_length;
    };
}


#endif //TILEMAP_SHADER_HPP
