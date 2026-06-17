/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HomeSceneClass.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:15:16 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/17 16:46:13 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HomeSceneClass.hpp"

HomeScene::HomeScene(std::string name, AAssetManager *mgr, Screen *screen, ResourceManager *resourceManager)
	: Scene(screen, resourceManager), name(name), mgr(mgr), screen(screen)
{
	try
	{
		resourceManager->loadTextures(mgr, "coin", "textures/coin.png");
		Object *square0 = new Object("idk", 400.0f, 600.0f, 400.0f, 600.0f, this->mgr, this->screen, "coin", "default", false, resourceManager);
		this->addObject(square0);
	}
	catch (const std::exception &e)
	{
		__android_log_print(ANDROID_LOG_INFO, "MYAPP ERROR", "%s", e.what());
	}

	this->getText()->loadFont(mgr, "main", "fonts/arial.ttf", 48.0f);
	this->addText(name, {"main", 300.0f, 400.0f, 1.0f, 1.0f, 1.0f, 1.0f, true});
}

HomeScene::~HomeScene()
{
}