/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SquareClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 13:18:23 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/10 16:17:16 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SquareClass.hpp"
#include "../libs/stb_image.h"

Square::Square(float x1, float x2, float y1, float y2, s_rgba rgba, AAssetManager *mgr, Screen *screen, const char* texture)
{

	float left = (x1 / (float)screen->width()) * 2.0f - 1.0f;
	float right = (x2 / (float)screen->width()) * 2.0f - 1.0f;
	float bottom = 1.0f - (y2 / (float)screen->height()) * 2.0f;
	float top = 1.0f - (y1 / (float)screen->height()) * 2.0f;

	float r = rgba.r / 255.0f;
	float g = rgba.g / 255.0f;
	float b = rgba.b / 255.0f;
	float a = rgba.a / 255.0f;

	GLfloat vertices[] = {
		left, bottom, 0.0f, r, g, b, a, 0.0f, 0.0f,
		right, bottom, 0.0f, r, g, b, a, 0.0f, 1.0f,
		right, top, 0.0f, r, g, b, a, 1.0f, 1.0f,
		left, top, 0.0f, r, g, b, a, 1.0f, 0.0f};

	GLuint indices[] = {
		0, 1, 2, // triangle 1
		0, 2, 3	 // triangle 2
	};

	this->shaderProgram = new Shader(mgr, "shaders/default.vert", "shaders/default.frag");
	this->VAO1 = new VAO();
	this->VAO1->Bind();
	this->VBO1 = new VBO(vertices, sizeof(vertices));
	this->EBO1 = new EBO(indices, sizeof(indices));
	this->VAO1->LinkAttrib(*this->VBO1, 0, 3, GL_FLOAT, 9 * sizeof(float), (void *)0);
	this->VAO1->LinkAttrib(*this->VBO1, 1, 4, GL_FLOAT, 9 * sizeof(float), (void *)(3 * sizeof(float)));
	this->VAO1->LinkAttrib(*this->VBO1, 2, 2, GL_FLOAT, 9 * sizeof(float), (void *)(7 * sizeof(float)));

	this->VAO1->Unbind();

	AAsset *asset = AAssetManager_open(mgr, texture, AASSET_MODE_BUFFER);
	size_t size = AAsset_getLength(asset);
	unsigned char *buffer = new unsigned char[size];
	AAsset_read(asset, buffer, size);

	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *bytes = stbi_load_from_memory(
		buffer, size, &widthImg, &heightImg, &numColCh, 0);

	glGenTextures(1, &this->_texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	GLenum format;

	if (numColCh == 4)
		format = GL_RGBA;
	else if (numColCh == 3)
		format = GL_RGB;
	else
		format = GL_RED;

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		format,
		widthImg,
		heightImg,
		0,
		format,
		GL_UNSIGNED_BYTE,
		bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	AAsset_close(asset);
	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint tex0Uni = glGetUniformLocation(this->shaderProgram->ID, "tex0");
	shaderProgram->Activate();
	glUniform1i(tex0Uni, 0);

	delete[] buffer;
}

Shader *Square::getShader()
{
	return (this->shaderProgram);
}

VAO *Square::getVAO()
{
	return (this->VAO1);
}

VBO *Square::getVBO()
{
	return (this->VBO1);
}

EBO *Square::getEBO()
{
	return (this->EBO1);
}

GLuint Square::getTexture()
{
	return (this->_texture);
}

Square::~Square()
{
	VAO1->Delete();
	VBO1->Delete();
	EBO1->Delete();
	shaderProgram->Delete();
	glDeleteTextures(1, &this->_texture);

	delete VAO1;
	delete VBO1;
	delete EBO1;
	delete shaderProgram;
}