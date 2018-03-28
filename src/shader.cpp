//
// Created by loulfy on 25/03/18.
//

#include "shader.hpp"

namespace tx
{
    Shader & Shader::use()
    {
        glUseProgram(m_program);
        return *this;
    }

    Shader & Shader::attach(std::string const & filename)
    {
        // Load GLSL Shader Source from File
        std::string path = ASSETS"/shaders/";
        LOGI << path << filename;

        std::stringstream src;

        std::ifstream file;
        file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
        try
        {
            file.open(path + filename);

            src << file.rdbuf();

            file.close();
        }
        catch(const std::ifstream::failure& e)
        {
            throw std::runtime_error("TX::ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
        }

        // Create a Shader Object
        auto code = src.str();
        const char* source = code.c_str();
        auto shader = create(filename);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &m_status);

        // Display the Build Log on Error
        if(m_status != GL_TRUE)
        {
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &m_length);
            std::unique_ptr<char[]> buffer(new char[m_length]);
            glGetShaderInfoLog(shader, m_length, nullptr, buffer.get());
            LOGE << filename << " : " << buffer.get();
        }

        // Attach the Shader and Free Allocated Memory
        glAttachShader(m_program, shader);
        glDeleteShader(shader);
        return *this;
    }

    GLuint Shader::create(std::string const & filename)
    {
        auto index = filename.rfind('.');
        auto ext = filename.substr(index + 1);
        if (ext == "comp") return glCreateShader(GL_COMPUTE_SHADER);
        else if (ext == "frag") return glCreateShader(GL_FRAGMENT_SHADER);
        else if (ext == "geom") return glCreateShader(GL_GEOMETRY_SHADER);
        else if (ext == "vert") return glCreateShader(GL_VERTEX_SHADER);
        else                    return static_cast<GLuint>(false);
    }

    Shader & Shader::link()
    {
        glLinkProgram(m_program);
        glGetProgramiv(m_program, GL_LINK_STATUS, &m_status);
        if(m_status != GL_TRUE)
        {
            glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, & m_length);
            std::unique_ptr<char[]> buffer(new char[m_length]);
            glGetProgramInfoLog(m_program, m_length, nullptr, buffer.get());
            LOGE << buffer.get();
        }
        //static_assert(m_status != 0);
        return *this;
    }

    void Shader::bind(unsigned int location, float value) { glUniform1f(location, value); }

    void Shader::bind(unsigned int location, glm::vec2 const &vector) { glUniform2f(location, vector.x, vector.y); }

    void Shader::bind(unsigned int location, glm::mat4 const & matrix)
    { glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)); }
}
