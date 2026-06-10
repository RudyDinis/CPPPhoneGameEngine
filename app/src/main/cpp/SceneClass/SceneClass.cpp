/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SceneClass.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:06:44 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/10 15:11:22 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SceneClass.hpp"

Scene::Scene(Screen *screen)
	: screen(screen), text(new Text())
{
	
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
	for (auto &object : this->Objects)
	{
		object->Show();
	}

	glm::mat4 proj = glm::ortho(0.0f, (float)this->screen->width(),
								(float)this->screen->height(), 0.0f,
								-1.0f, 1.0f);

	for (auto &textData : this->TextData)
	{
		this->text->drawText(textData.second.font, textData.first.c_str(), textData.second.x, textData.second.y,
							 textData.second.r, textData.second.g, textData.second.b, textData.second.a,
							 proj);
	}
}

Scene::~Scene()
{
	for (auto &object : this->Objects)
	{
		delete object;
	}

	delete text;
}