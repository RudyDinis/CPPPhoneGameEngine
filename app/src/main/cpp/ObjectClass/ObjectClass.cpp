/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ObjectClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:59:04 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/12 17:52:28 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ObjectClass.hpp"

Object::Object(std::string name, float x1, float x2, float y1, float y2, AAssetManager *mgr, Screen *screen, const char *texture, const char *shader, bool mobile, ResourceManager *resourceManager)
{
	this->square = new Square(x1, x2, y1, y2, {255, 0, 0, 255}, mgr, screen, resourceManager, texture, shader);
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
	this->visible = true;
	this->name = name;
	this->mobile = mobile;
	this->screen = screen;
}

void Object::Show(float offset_x, float offset_y, float x, float y, float zoom)
{
	this->square->getShader()->Activate();

	GLint offsetLoc = glGetUniformLocation(this->square->getShader()->ID, "uOffset");
	GLint zoomLoc = glGetUniformLocation(this->square->getShader()->ID, "uZoom");

	if (!this->mobile)
		glUniform1f(zoomLoc, 1.0);
	else
		glUniform1f(zoomLoc, zoom);

	if (this->mobile)
	{
		glUniform2f(offsetLoc, offset_x, offset_y);
		float ndcX1 = (this->x1 / (float)screen->width()) * 2.0f - 1.0f;
		float ndcX2 = (this->x2 / (float)screen->width()) * 2.0f - 1.0f;
		float ndcY1 = 1.0f - (this->y1 / (float)screen->height()) * 2.0f;
		float ndcY2 = 1.0f - (this->y2 / (float)screen->height()) * 2.0f;

		float finalX1 = (ndcX1 * zoom + offset_x + 1.0f) * 0.5f * screen->width();
		float finalX2 = (ndcX2 * zoom + offset_x + 1.0f) * 0.5f * screen->width();
		float finalY1 = (1.0f - (ndcY1 * zoom + offset_y)) * 0.5f * screen->height();
		float finalY2 = (1.0f - (ndcY2 * zoom + offset_y)) * 0.5f * screen->height();

		this->x1f = finalX1;
		this->x2f = finalX2;
		this->y1f = finalY1;
		this->y2f = finalY2;
	}
	else
	{
		glUniform2f(offsetLoc, 0.0f, 0.0f);
		this->x1f = this->x1 + 0.0;
		this->x2f = this->x2 + 0.0;
		this->y1f = this->y1 + 0.0;
		this->y2f = this->y2 + 0.0;
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->square->getTexture());
	this->square->getVAO()->Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int Object::isTouched(float x, float y)
{
	if (!this->visible)
		return 0;
	__android_log_print(ANDROID_LOG_INFO, "DEBUG", "touch %f %f,x1f %d, x2f %d, y1f %d y2f %d", x, y, this->x1f, this->x2f, this->y1f, this->y2f);
	if ((x > this->x1f && x < this->x2f) && (y > this->y1f && y < this->y2f))
	{
		__android_log_print(ANDROID_LOG_INFO, "DEBUG", "TOUCH x=%f y=%f %s", x, y, this->name.c_str());
		return 1;
	}
	return 0;
}

std::string Object::getName()
{
	return (this->name);
}

bool Object::getVisibility()
{
	return (this->visible);
}

void Object::setVisible(bool status)
{
	this->visible = status;
}

Object::~Object()
{
	delete this->square;
}
