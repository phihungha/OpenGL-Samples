#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


void onFramebufferResize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void handleInputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void errorExit(const std::string& message) {
	std::cout << message << std::endl;
	glfwTerminate();
	exit(-1);
}

GLFWwindow* initWindow(int width, int height, const std::string& title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (window == nullptr) {
		errorExit("Failed to create window.");
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		errorExit("Failed to load GLAD.");
	}

	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, onFramebufferResize);

	return window;
}

#endif // !WINDOW_H
