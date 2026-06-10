/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ObjectClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:59:04 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/10 16:56:14 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ObjectClass.hpp"

Object::Object(std::string name, float x1, float x2, float y1, float y2, AAssetManager *mgr, Screen *screen, const char *texture, bool mobile)
{
	this->square = new Square(x1, x2, y1, y2, {255, 0, 0, 255}, mgr, screen, texture);
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
	this->visible = true;
	this->name = name;
	this->mobile = mobile;
}

void Object::Show(float offset_x, float offset_y)
{
	this->square->getShader()->Activate();
	
	GLint offsetLoc = glGetUniformLocation(this->square->getShader()->ID, "uOffset");

	if (this->mobile)
		glUniform2f(offsetLoc, offset_x, offset_y);
	else
		glUniform2f(offsetLoc, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, this->square->getTexture());
	this->square->getVAO()->Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int Object::isTouched(float x, float y)
{
	if (!this->visible)
		return 0;
	if ((x > this->x1 && x < this->x2) && (y > this->y1 && y < this->y2))
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
