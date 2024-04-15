#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>
#include <random>
#include "circle.h"
#include "shader.h"
#include "Audio_Driver.h"
#include "SpectrogramWindow.h"

static const unsigned int WIDTH = 1200;
static const unsigned int HEIGHT = 1200;
static const unsigned int BALL_AMOUNT = 1;
static const float BASE_VELOCITY[2] = { -0.001f, -0.005f };

int main()
{
    // Initialize GLFW and create the main window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* _WINDOW = glfwCreateWindow(WIDTH, HEIGHT, "Funny NoiserHeimer", NULL, NULL);

    if (!_WINDOW) {
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(_WINDOW);
    gladLoadGL();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Activate shader program and other OpenGL resources
    Shader shaderProg("default.vert", "default.frag");
    shaderProg.Activate();
    // Create the spectrogram window
    Spectrogram_Window _SPECTROGRAM(WIDTH/2, HEIGHT/2, _WINDOW);
    // Other initialization code...
    Audio_Driver _AUDIO(_SPECTROGRAM);
    Circle** circleBuffer = new Circle * [BALL_AMOUNT];

    // Local Stack
    {
        // Seed the random number generator with a random device
        std::random_device rd;
        std::mt19937 gen(rd());

        // Define a distribution (e.g., uniform distribution between 1 and 100)
        std::uniform_real_distribution<float> randomCoord(-0.25f, 0.25f);

        for (unsigned int i = 0; i < BALL_AMOUNT; i++) {
            circleBuffer[i] = new Circle(randomCoord(gen), randomCoord(gen), (BASE_VELOCITY[0] * (std::rand() % 20)) / BALL_AMOUNT, (BASE_VELOCITY[1] * (std::rand() % 20)) / BALL_AMOUNT, 0.015f);
        }
    }

    Circle boundaryCircle = Circle(0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 60, glm::vec3(0.1f, 0.73f, 0.32f));
    std::chrono::duration<double> frameDuration(1.0 / 120);

    // Rendering loop for main window
    while (!glfwWindowShouldClose(_WINDOW)) {
        glfwMakeContextCurrent(_WINDOW);
        auto start = std::chrono::high_resolution_clock::now();
        glClear(GL_COLOR_BUFFER_BIT);

        boundaryCircle.update();
        for (unsigned int i = 0; i < BALL_AMOUNT; i++) {
            circleBuffer[i]->tick(_AUDIO, boundaryCircle);
        }

        glfwSwapBuffers(_WINDOW);
        glfwPollEvents();

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

        // Sleep to maintain the desired frame rate
        std::this_thread::sleep_for(frameDuration - elapsed);
    }

    shaderProg.Delete();

    glfwDestroyWindow(_WINDOW);
    glfwTerminate();

    return 0;
}
