/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SquareClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 13:18:23 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/12 18:06:18 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SquareClass.hpp"
#include "../libs/stb_image.h"

Square::Square(float x1, float x2, float y1, float y2, s_rgba rgba, AAssetManager *mgr, Screen *screen, ResourceManager *resourceManager, const char *texture, const char *shader)
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
		right, bottom, 0.0f, r, g, b, a, 1.0f, 0.0f,
		right, top, 0.0f, r, g, b, a, 1.0f, 1.0f,
		left, top, 0.0f, r, g, b, a, 0.0f, 1.0f};

	GLuint indices[] = {
		0, 1, 2, // triangle 1
		0, 2, 3	 // triangle 2
	};

	this->shaderProgram = resourceManager->getShader(shader);
	this->VAO1 = new VAO();
	this->VAO1->Bind();
	this->VBO1 = new VBO(vertices, sizeof(vertices));
	this->EBO1 = new EBO(indices, sizeof(indices));
	this->VAO1->LinkAttrib(*this->VBO1, 0, 3, GL_FLOAT, 9 * sizeof(float), (void *)0);
	this->VAO1->LinkAttrib(*this->VBO1, 1, 4, GL_FLOAT, 9 * sizeof(float), (void *)(3 * sizeof(float)));
	this->VAO1->LinkAttrib(*this->VBO1, 2, 2, GL_FLOAT, 9 * sizeof(float), (void *)(7 * sizeof(float)));

	this->VAO1->Unbind();
	this->_texture = resourceManager->getTexture(texture);
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

	delete VAO1;
	delete VBO1;
	delete EBO1;
}