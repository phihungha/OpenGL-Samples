#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glad/glad.h>

GLuint createShader(GLenum type, const std::string& source) {
	GLuint shader = glCreateShader(type);
	const char* sourceArr = source.data();
	glShaderSource(shader, 1, &sourceArr, nullptr);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char log[512];
		glGetShaderInfoLog(shader, 512, nullptr, log);

		std::string typeName;
		switch (type) {
		case GL_VERTEX_SHADER: {
			typeName = "vertex";
		} break;
		case GL_FRAGMENT_SHADER: {
			typeName = "fragment";
		} break;
		}

		std::cout << "Failed to compile " << typeName << " shader:\n"
			<< log << std::endl;
	}

	return shader;
}

void getProgramLinkStatus(GLuint program) {
	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		char log[512];
		glGetProgramInfoLog(program, 512, nullptr, log);
		std::cout << "Failed to link program:\n" << log << std::endl;
	}
}

std::string loadTextFromFile(const std::string& path) {
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		file.open(path);
		std::stringstream textStream;
		textStream << file.rdbuf();
		file.close();
		return textStream.str();
	}
	catch (std::ifstream::failure err) {
		std::cout << "Failed to read file " << path << std::endl;
		throw;
	}
}

class ShaderProgram {
private:
	GLuint programId;
public:
	ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource) {
		GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexSource);
		GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentSource);

		programId = glCreateProgram();
		glAttachShader(programId, vertexShader);
		glAttachShader(programId, fragmentShader);
		glLinkProgram(programId);
		getProgramLinkStatus(programId);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	static ShaderProgram fromFiles(
		const std::string& vertexSourcePath,
		const std::string& fragmentSourcePath
	) {
		std::string vertexSource = loadTextFromFile(vertexSourcePath);
		std::string fragmentSource = loadTextFromFile(fragmentSourcePath);
		return ShaderProgram(vertexSource, fragmentSource);
	}

	void use() {
		glUseProgram(programId);
	}

	void setUni1f(const std::string& name, float value) {
		int location = glGetUniformLocation(programId, name.c_str());
		glUniform1f(location, value);
	}

	void setUni2f(const std::string& name, float value1, float value2) {
		int location = glGetUniformLocation(programId, name.c_str());
		glUniform2f(location, value1, value2);
	}

	void setUni3f(
		const std::string& name,
		float value1,
		float value2,
		float value3
	) {
		int location = glGetUniformLocation(programId, name.c_str());
		glUniform3f(location, value1, value2, value3);
	}

	void setUni4f(
		const std::string& name,
		float value1,
		float value2,
		float value3,
		float value4
	) {
		int location = glGetUniformLocation(programId, name.c_str());
		glUniform4f(location, value1, value2, value3, value4);
	}
};