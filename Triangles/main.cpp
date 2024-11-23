#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <window.h>
#include <vao.h>
#include <shader.h>


int main() {
	GLFWwindow* window = initWindow(800, 600, "Triangles");

	ShaderProgram shader1 = ShaderProgram::fromFiles("vertex_shader_1.glsl", "fragment_shader_1.glsl");
	ShaderProgram shader2 = ShaderProgram::fromFiles("vertex_shader_2.glsl", "fragment_shader_2.glsl");
	ShaderProgram shader3 = ShaderProgram::fromFiles("vertex_shader_3.glsl", "fragment_shader_2.glsl");

	std::vector<float> vertices1{
		-0.75f, -0.25f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.25f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.25f, -0.25f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	};
	std::vector<float> vertices2{
		-0.25f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.25f, -0.25f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	};
	std::vector<float> vertices3{
		0.25f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.75f, -0.25f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	};
	std::vector<unsigned int> elements{ 0, 1, 2 };
	GLuint vao1 = createVao(vertices1, elements);
	GLuint vao2 = createVao(vertices2, elements);
	GLuint vao3 = createVao(vertices3, elements);

	while (!glfwWindowShouldClose(window)) {
		handleInputs(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(vao1);
		shader1.use();
		float time = (float)glfwGetTime();
		float greenValue = (sin(3 * time) / 2.0f) + 0.5f;
		shader1.setUni3f("uniformColor", 0.0f, greenValue, 0.0f);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glBindVertexArray(vao2);
		shader2.use();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glBindVertexArray(vao3);
		shader3.use();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
