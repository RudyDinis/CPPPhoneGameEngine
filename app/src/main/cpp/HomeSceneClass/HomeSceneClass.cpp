/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HomeSceneClass.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:15:16 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/10 15:18:43 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HomeSceneClass.hpp"

HomeScene::HomeScene(std::string name, AAssetManager *mgr, Screen *screen)
	: Scene(screen), name(name), mgr(mgr), screen(screen)
{
	Object *square = new Object("topleft", 0, 200, 0, 200, this->mgr, this->screen, "textures/coin.png");
	this->addObject(square);

	this->getText()->loadFont(mgr, "main", "fonts/arial.ttf", 48.0f);
	this->addText("Score: 42", {"main", 300.0f, 400.0f, 1.0f, 1.0f, 1.0f, 1.0f});
}

HomeScene::~HomeScene()
{
}