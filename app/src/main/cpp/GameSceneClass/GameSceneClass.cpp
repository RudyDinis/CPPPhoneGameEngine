/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameSceneClass.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:15:16 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/16 12:23:48 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameSceneClass.hpp"

GameScene::GameScene(std::string name, AAssetManager *mgr, Screen *screen, ResourceManager *resourceManager)
	: Scene(screen), name(name), mgr(mgr), screen(screen), map(new Map()), resourceManager(resourceManager)
{
	
}

void GameScene::load()
{
	this->map->generateMap(this, this->mgr, this->screen, this->resourceManager);
}

GameScene::~GameScene()
{
	delete map;
}