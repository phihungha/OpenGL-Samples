#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <string>
#include <glad/glad.h>

#include "window.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


GLuint createTexture(const std::string& imagePath, bool hasAlpha = false) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	int width, height, channel;
	unsigned char* image = stbi_load(imagePath.c_str(), &width, &height, &channel, 0);
	if (!image) {
		errorExit("Failed to load image.");
	}

	GLenum imageType = hasAlpha ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, imageType, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}

#endif // !TEXTURE_H