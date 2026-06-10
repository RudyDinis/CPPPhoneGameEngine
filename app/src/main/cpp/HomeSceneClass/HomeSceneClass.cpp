/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HomeSceneClass.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:15:16 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/10 16:55:13 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HomeSceneClass.hpp"

HomeScene::HomeScene(std::string name, AAssetManager *mgr, Screen *screen)
	: Scene(screen), name(name), mgr(mgr), screen(screen)
{
	Object *square = new Object("topleft", 0.0f, 200.0f, 0.0f, 200.0f, this->mgr, this->screen, "textures/coin.png", true);
	this->addObject(square);

	Object *square0 = new Object("idk", 400.0f, 600.0f, 400.0f, 600.0f, this->mgr, this->screen, "textures/coin.png", false);
	this->addObject(square0);

	this->getText()->loadFont(mgr, "main", "fonts/arial.ttf", 48.0f);
	this->addText(name, {"main", 300.0f, 400.0f, 1.0f, 1.0f, 1.0f, 1.0f});
}

HomeScene::~HomeScene()
{
}