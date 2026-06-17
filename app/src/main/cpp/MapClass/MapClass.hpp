/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapClass.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:58:12 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/17 18:06:25 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPCLASS_HPP
#define MAPCLASS_HPP

#include "../SceneClass/SceneClass.hpp"
#include "../ScreenClass/ScreenClass.hpp"
#include "../ResourceManagerClass/ResourceManager.hpp"
#include "../TileMapClass/TileMapClass.hpp"

#include <chrono>
#include <android/asset_manager.h>
#include <cmath>
#include <vector>
#include <algorithm>

struct vec2
{
	float x;
	float y;
};

struct GreedyData {
	int id;
	char type;
	int x, y, w, h;
};

class Map
{
private:
	float _gradient[16][16][2];
	unsigned int seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	int size = 30;
	char map[30][30];
	std::vector<GreedyData> greedy;
	TileMap *tilemap;
public:
	Map(ResourceManager *resourceManager, AAssetManager *mgr);
	vec2 randomGradient(int ix, int iy);
	float dotGridGradient(int ix, int iy, float x, float y);
	float perlin(float x, float y);
	void generateMap(Screen *screen);
	TileMap *getTileMap();
	void greedyMeshing();
	void printGreedy();
	void printMap();
	~Map();
};

#endif