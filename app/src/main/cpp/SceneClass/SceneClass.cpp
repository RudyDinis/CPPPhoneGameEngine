/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SceneClass.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:06:44 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/16 21:04:58 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SceneClass.hpp"

Scene::Scene(Screen *screen, ResourceManager *resourceManager)
	: screen(screen), text(new Text()), camera(new Camera()), resourceManager(resourceManager)
{
	this->tex0Loc = glGetUniformLocation(this->resourceManager->getShader("default")->ID, "tex0");
}

void Scene::addObject(Object *obj)
{
	this->Objects.push_back(obj);
}

Text *Scene::getText()
{
	return (this->text);
}

void Scene::addText(std::string name, s_text_value value)
{
	this->TextData.insert({name, value});
}

std::vector<Object *> Scene::getObject()
{
	return (this->Objects);
}

bool Scene::getCanMoove()
{
	return (this->canMoove);
}

void Scene::setCanMoove(bool status)
{
	this->canMoove = status;
}

void Scene::render()
{
	float ox = *this->camera->getOffset_x() / this->screen->width() * 2.0f;
	float oy = *this->camera->getOffset_y() / this->screen->height() * 2.0f;

	this->resourceManager->getShader("default")->Activate();
	glUniform1i(this->tex0Loc, 0);
	
	for (auto &object : this->Objects)
	{
		object->Show(ox, oy, *this->camera->getOffset_x(), *this->camera->getOffset_y(), *this->camera->getZoom());
	}

	glm::mat4 proj = glm::ortho(0.0f, (float)this->screen->width(),
								(float)this->screen->height(), 0.0f,
								-1.0f, 1.0f);

	for (auto &textData : this->TextData)
	{
		if (textData.second.movable)
			this->text->drawText(textData.second.font, textData.first.c_str(), textData.second.x + *this->camera->getOffset_x(), textData.second.y + -(*this->camera->getOffset_y()),
								 textData.second.r, textData.second.g, textData.second.b, textData.second.a,
								 proj);
		else
			this->text->drawText(textData.second.font, textData.first.c_str(), textData.second.x, textData.second.y,
								 textData.second.r, textData.second.g, textData.second.b, textData.second.a,
								 proj);
	}
}

Camera *Scene::getCamera()
{
	return (this->camera);
}

Scene::~Scene()
{
	for (auto &object : this->Objects)
	{
		delete object;
	}

	delete text;
	delete camera;
}