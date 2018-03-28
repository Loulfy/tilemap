//
// Created by loulfy on 25/03/18.
//

#include "context.hpp"
#include "shader.hpp"
#include "texture.hpp"

namespace tx
{
    Context::Context() : Context(1344, 1088)
    {

    }

    Context::Context(int width, int height)
    {
        // Initialize GLFW 3
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Initialize Logger
        static plog::ColorConsoleAppender<plog::TxtFormatter> console;
        plog::init(plog::verbose, &console);

        // SET the window no re-sizable
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        // SET anti-aliasing
        glfwWindowHint(GLFW_SAMPLES, 8);

        // Create a windowed window and it is OpenGL context
        m_window = glfwCreateWindow(width, height, "TILEMAP GPU", nullptr, nullptr);
        if(m_window == nullptr)
        {
            glfwTerminate();
            throw std::runtime_error("TX::ERROR::Failed to create GLFW window");
        }

        // Make the window context current
        glfwMakeContextCurrent(m_window);


        // Initialize GLAD
        if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            glfwTerminate();
            throw std::runtime_error("TX::ERROR::Failed to initialize OpenGL context");
        }

        Shader shader;
        shader.attach("tilemap.vert");
        shader.attach("tilemap.frag");
        shader.link();

        Texture tileset("spelunky-tiles.png");
        Texture tilemap("spelunky0.png");

        int tex;
        shader.use();

        glm::vec2 viewport(width/2, height/2);
        glm::vec2 inverseTileset(1.0/128.0, 1.0/128.0);
        glm::vec2 inverseTilemap(1.0/42.0, 1.0/34.0);

        glm::vec2 camera(0,0);
        shader.bind("viewOffset", camera);


        shader.bind("viewportSize", viewport);
        shader.bind("inverseSpriteTextureSize", inverseTileset);
        shader.bind("inverseTileTextureSize", inverseTilemap);
        shader.bind("tileSize", 16.0);
        shader.bind("inverseTileSize", 1.0/16.0);

        float vertices[] = {
                //x  y  u  v
                -1, -1, 0, 1,
                1, -1, 1, 1,
                1, 1, 1, 0,

                -1, -1, 0, 1,
                1, 1, 1, 0,
                -1, 1, 0, 0
        };

        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        GLuint buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2*sizeof(float)));

        tex = shader.location("sprites");
        glActiveTexture(GL_TEXTURE0);
        tileset.active(tex, 0);

        tex = shader.location("tiles");
        glActiveTexture(GL_TEXTURE1);
        tilemap.active(tex, 1);


        // SET the user pointer in the window
        glfwSetWindowUserPointer(m_window, this);

        while(!glfwWindowShouldClose(m_window))
        {
            glfwPollEvents();

            glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glDrawArrays(GL_TRIANGLES, 0, 6);

            camera.x = static_cast<float>(glfwGetTime()*100);
            //camera.y = static_cast<float>(glfwGetTime()*100);
            shader.bind("viewOffset", camera);

            glfwSwapBuffers(m_window);
        }

        glDeleteBuffers(1, &buffer);
        glDeleteVertexArrays(1, &vao);
    }

    Context::~Context()
    {
        glfwTerminate();
    }
}