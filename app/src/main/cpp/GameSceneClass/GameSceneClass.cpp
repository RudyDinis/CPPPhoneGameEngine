/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameSceneClass.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:15:16 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/17 18:28:26 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameSceneClass.hpp"

GameScene::GameScene(std::string name, AAssetManager *mgr, Screen *screen, ResourceManager *resourceManager)
	: Scene(screen, resourceManager), name(name), mgr(mgr), screen(screen), map(new Map(resourceManager, mgr)), resourceManager(resourceManager)
{
}

void GameScene::load()
{
	__android_log_print(ANDROID_LOG_INFO, "MYAPP MAP", "LOAD CALLED");
	this->map->generateMap(this->screen);
}

void GameScene::render()
{
	this->map->getTileMap()->render(this->screen, *this->getCamera()->getOffset_x(), *this->getCamera()->getOffset_y(), *this->getCamera()->getZoom());
}

GameScene::~GameScene()
{
	delete map;
}