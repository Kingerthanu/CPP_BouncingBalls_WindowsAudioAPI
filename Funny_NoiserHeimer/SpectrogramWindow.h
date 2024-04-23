#ifndef SPECTROGRAM_WINDOW_H
#define SPECTROGRAM_WINDOW_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <mutex> // Include mutex header
#include "Vertex_Buffer.h"
#include "shader.h"
#include "Vertex_Array.h"

class Spectrogram_Window
{
private:
    VAO vertexArray;
    VBO vertexBuffer;
    GLFWwindow* _WINDOW;
    GLFWwindow* _PARENT;
    Shader contextShader;

    std::mutex contextMutex; // Mutex for synchronizing OpenGL context access

public:
    Spectrogram_Window(const unsigned int& newWidth, const unsigned int& newHeight, GLFWwindow*& PARENT)
    {
        // Initialize GLFW and create the main window
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        this->_WINDOW = glfwCreateWindow(newWidth, newHeight, "Funny NoiserHeimer Waves", NULL, NULL);

        if (!this->_WINDOW) {
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(this->_WINDOW);
        gladLoadGL();

        this->contextShader = Shader("default.vert", "default.frag");
        this->contextShader.Activate();

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(this->_WINDOW);

        // Set up OpenGL resources (VAO, VBO)
        this->vertexArray = VAO();
        this->vertexArray.Bind();
        this->vertexBuffer = VBO();
        vertexBuffer.genBuffer();

        // Set the parent window
        this->_PARENT = PARENT;

        // Link vertex buffer with VAO
        this->vertexArray.LinkAttrib(this->vertexBuffer, 0, 2, GL_FLOAT, sizeof(Vertex), (void*)0);
        this->vertexArray.LinkAttrib(this->vertexBuffer, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(sizeof(float) * 2));


        // Make the parent window's OpenGL context current again
        glfwMakeContextCurrent(this->_PARENT);
    }

    void RenderDiscrete(const std::vector<short>& sampleBuffer)
    {
        // Lock the mutex to synchronize access to OpenGL context
        std::lock_guard<std::mutex> lock(contextMutex);

        // Make the window's OpenGL context current
        glfwMakeContextCurrent(this->_WINDOW);

        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Normalize the data
        std::vector<Vertex> normalizedBuffer;
        normalizedBuffer.reserve(sampleBuffer.size());

        float stprIncrement = 2.0f / sampleBuffer.size(); // Adjust this value as needed
        float stpr = -1.0f;

        for (unsigned int i = 0, bufferSize = sampleBuffer.size(); i < bufferSize; ++i, stpr += stprIncrement) {
            normalizedBuffer.push_back(Vertex({ glm::vec2({ stpr, (((float)(sampleBuffer[i])) / SHRT_MAX * 2.0f) }), glm::vec3({0.8f, 0.4f, 0.95f}) }));
        }

        // Bind VAO and VBO
        vertexArray.Bind();
        vertexBuffer.Bind();

        // Update buffer data using glBufferData with GL_DYNAMIC_DRAW
        glBufferData(GL_ARRAY_BUFFER, normalizedBuffer.size() * sizeof(Vertex), normalizedBuffer.data(), GL_DYNAMIC_DRAW);

        // Draw all lines
        glDrawArrays(GL_LINE_STRIP, 0, normalizedBuffer.size());

        // Swap the front and back buffers
        glfwSwapBuffers(this->_WINDOW);
    }

    // Destructor
    ~Spectrogram_Window()
    {
        glfwDestroyWindow(this->_WINDOW);
    }
};


#endif