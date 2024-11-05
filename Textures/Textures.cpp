#include <iostream>
#include <vector>

#include <shader.h>
#include <texture.h>
#include <vao.h>
#include <window.h>

int main()
{
	GLFWwindow* window = initWindow(800, 600, "Textures");

	ShaderProgram shader = ShaderProgram::fromFiles("vertex_shader.glsl", "fragment_shader.glsl");
	GLuint texture1 = createTexture("container.jpg");
	GLuint texture2 = createTexture("awesomeFace.png", true);

	std::vector<float> vertices{
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // top left 
	};
	std::vector<unsigned int> elements{
		0, 1, 3,
		1, 2, 3,
	};
	GLuint vao = createVao(vertices, elements);

	float mixAmount = 0.5f;

	while (!glfwWindowShouldClose(window)) {
		handleInputs(window);

		if (mixAmount < 1.0f && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			mixAmount += 0.0005f;
		}
		else if (mixAmount > 0.0f && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			mixAmount -= 0.0005f;
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		shader.use();
		shader.setUni1i("tex1", 0);
		shader.setUni1i("tex2", 1);
		shader.setUni1f("mixAmount", mixAmount);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
