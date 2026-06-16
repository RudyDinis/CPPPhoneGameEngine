/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameSceneClass.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:15:16 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/16 16:50:20 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameSceneClass.hpp"

GameScene::GameScene(std::string name, AAssetManager *mgr, Screen *screen, ResourceManager *resourceManager)
	: Scene(screen), name(name), mgr(mgr), screen(screen), map(new Map()), resourceManager(resourceManager)
{
	
}

void GameScene::load()
{
	this->map->generateMap();
	this->map->greedyMeshing();
	this->map->printGreedy();
	this->map->drawMap(this, this->mgr, this->screen, this->resourceManager);
}

GameScene::~GameScene()
{
	delete map;
}