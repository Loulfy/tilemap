//
// Created by loulfy on 25/03/18.
//

#ifndef TILEMAP_CONTEXT_HPP
#define TILEMAP_CONTEXT_HPP

#include <plog/Log.h>
#include <plog/Appenders/ColorConsoleAppender.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace tx
{
    class Context
    {
        public:

            Context();
            Context(int width, int height);
            ~Context();

        private:

            GLFWwindow* m_window;
    };
}

#endif //TILEMAP_CONTEXT_HPP
