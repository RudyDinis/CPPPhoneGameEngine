/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TileMapClass.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 18:23:21 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/17 18:45:28 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TileMapClass.hpp"

TileMap::TileMap(ResourceManager *resourceManager, AAssetManager *mgr)
	: resourceManager(resourceManager), _VAO(nullptr), _VBO(nullptr), _EBO(nullptr), instanceVBO(0)
{
	this->shaderProgram = this->resourceManager->getShader("tileMap");

	this->tileUV['g'] = {0.0f / 3.0f, 0.0f, 1.0f / 3.0f, 1.0f};
	this->tileUV['s'] = {1.0f / 3.0f, 0.0f, 2.0f / 3.0f, 1.0f};
	this->tileUV['w'] = {2.0f / 3.0f, 0.0f, 3.0f / 3.0f, 1.0f};

	this->atlasTexture = this->resourceManager->getTexture("groundAtlas");

	this->offsetLoc = glGetUniformLocation(this->shaderProgram->ID, "uOffset");
	this->zoomLoc = glGetUniformLocation(this->shaderProgram->ID, "uZoom");
	this->screenSizeLoc = glGetUniformLocation(this->shaderProgram->ID, "uScreenSize");
	this->tex0Loc = glGetUniformLocation(this->shaderProgram->ID, "tex0");
}

void TileMap::setupBuffer()
{
	GLfloat quadVertices[] = {
		// pos      // uv locale
		0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f};

	GLuint indices[] = {0, 1, 2, 0, 2, 3};

	this->_VAO = new VAO();
	this->_VAO->Bind();

	this->_VBO = new VBO(quadVertices, sizeof(quadVertices));
	this->_EBO = new EBO(indices, sizeof(indices));

	this->_VAO->LinkAttrib(*this->_VBO, 0, 2, GL_FLOAT, 4 * sizeof(float), (void *)0);
	this->_VAO->LinkAttrib(*this->_VBO, 1, 2, GL_FLOAT, 4 * sizeof(float), (void *)(2 * sizeof(float)));

	glGenBuffers(1, &this->instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->instanceVBO);

	__android_log_print(
		ANDROID_LOG_INFO,
		"MYAPP MAP",
		"Uploading %d instances",
		(int)this->instances.size());
	glBufferData(GL_ARRAY_BUFFER, this->instances.size() * sizeof(TileInstance), this->instances.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(TileInstance), (void *)0);
	glVertexAttribDivisor(2, 1);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(TileInstance),
						  (void *)(4 * sizeof(float)));
	glVertexAttribDivisor(3, 1);

	this->_VAO->Unbind();
}

void TileMap::generate(const char map[][30], int rows, int cols, Screen *screen)
{
	__android_log_print(ANDROID_LOG_INFO, "MYAPP MAP", "instances = %d",
						(int)this->instances.size());
	float tileW = 200.0f;
	float tileH = tileW * (1023.0f / 1024.0f);
	float roofH = tileW * (593.0f / 1024.0f);

	float stepX = tileW / 2.38f;
	float stepY = roofH / 2.38f;

	float originX = 200.0f;
	float originY = 200.0f;

	this->instances.clear();
	this->instances.reserve(rows * cols);

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			char c = map[row][col];

			auto it = this->tileUV.find(c);

			if (it == this->tileUV.end())
				continue;

			float sx = originX + (col - row) * stepX;
			float sy = originY + (col + row) * stepY;

			TileInstance inst;
			inst.x = sx;
			inst.y = sy;
			inst.w = tileW;
			inst.h = tileH;
			inst.u0 = it->second.u0;
			inst.v0 = it->second.v0;
			inst.u1 = it->second.u1;
			inst.v1 = it->second.v1;

			this->instances.push_back(inst);
		}
	}

	this->setupBuffer();
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		__android_log_print(
			ANDROID_LOG_ERROR,
			"MYAPP GL",
			"error=%x",
			err);
	}
}

void TileMap::render(Screen *screen, float offset_x, float offset_y, float zoom)
{
	this->shaderProgram->Activate();

	glUniform2f(this->screenSizeLoc, (float)screen->width(), (float)screen->height());
	glUniform2f(this->offsetLoc, offset_x, -offset_y);
	glUniform1f(this->zoomLoc, zoom);
	glUniform1i(this->tex0Loc, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->atlasTexture);

	this->_VAO->Bind();
	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, (GLsizei)this->instances.size());
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		__android_log_print(
			ANDROID_LOG_ERROR,
			"MYAPP GL",
			"error=%x",
			err);
	}

	this->_VAO->Unbind();
}
TileMap::~TileMap()
{
	if (this->_VAO)
	{
		this->_VAO->Delete();
		delete this->_VAO;
	}

	if (this->_VBO)
	{
		this->_VBO->Delete();
		delete this->_VBO;
	}

	if (this->_EBO)
	{
		this->_EBO->Delete();
		delete this->_EBO;
	}

	if (this->instanceVBO)
	{
		glDeleteBuffers(1, &this->instanceVBO);
	}
}