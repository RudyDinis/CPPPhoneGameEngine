/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameSceneClass.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:07:03 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/17 18:38:58 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMESCENECLASS_HPP
#define GAMESCENECLASS_HPP

#include <GLES3/gl3.h>
#include <android/asset_manager.h>
#include <android/log.h>

#include "../SceneClass/SceneClass.hpp"
#include "../ObjectClass/ObjectClass.hpp"
#include "../MapClass/MapClass.hpp"
#include "../ResourceManagerClass/ResourceManager.hpp"

class GameScene : public Scene
{
private:
	std::string name;
	AAssetManager *mgr;
	Screen *screen;
	Map *map;
	ResourceManager *resourceManager;
public:
	GameScene(std::string, AAssetManager*, Screen *, ResourceManager *resourceManager);
	void render() override;
	void load();
	~GameScene();
};

#endif