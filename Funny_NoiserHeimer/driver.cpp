#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>
#include "circle.h"
#include "shader.h"
#include "Audio_Driver.h"

static const unsigned int WIDTH = 1200;

static const unsigned int BALL_AMOUNT = 2;


int main()
{
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* _WINDOW = glfwCreateWindow(WIDTH, WIDTH, "Funny NoiserHeimer", NULL, NULL);

	Audio_Driver _AUDIO = Audio_Driver();
	

	if (!_WINDOW) {

		glfwTerminate();
		return 0;

	}

	glfwMakeContextCurrent(_WINDOW);


	gladLoadGL();

	glViewport(0, 0, WIDTH, WIDTH);


	Shader shaderProg("default.vert", "default.frag");

	//Circle permcle(-0.3f, 0.25f);

	Circle** circleBuffer = new Circle * [BALL_AMOUNT];

	{

		// Seed the random number generator with a random device
		std::random_device rd;
		std::mt19937 gen(rd());

		// Define a distribution (e.g., uniform distribution between 1 and 100)
		std::uniform_real_distribution<float> randomCoord(-0.85f, 0.85f);

		for (unsigned int i = 0; i < BALL_AMOUNT; i++) {

			circleBuffer[i] = new Circle(randomCoord(gen), randomCoord(gen),  -0.001 * (std::rand() % 10), -0.002f * (std::rand() % 10));

		}
	}
	
	shaderProg.Activate();

	std::chrono::duration<double> frameDuration(1.0 / 120);

	while (!glfwWindowShouldClose(_WINDOW)) {

		auto start = std::chrono::high_resolution_clock::now();


		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		
	
		for (unsigned int i = 0; i < BALL_AMOUNT; i++) {

			circleBuffer[i]->tick(_AUDIO);

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



};