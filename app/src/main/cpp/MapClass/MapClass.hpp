/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapClass.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 13:58:12 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/16 14:37:34 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPCLASS_HPP
#define MAPCLASS_HPP

#include "../SceneClass/SceneClass.hpp"
#include "../ScreenClass/ScreenClass.hpp"
#include "../ResourceManagerClass/ResourceManager.hpp"

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
public:
	Map();
	vec2 randomGradient(int ix, int iy);
	float dotGridGradient(int ix, int iy, float x, float y);
	float perlin(float x, float y);
	void generateMap();
	void greedyMeshing();
	void printGreedy();
	void printMap();
	void drawMap(Scene*,  AAssetManager *, Screen *, ResourceManager *resourceManager);
	~Map();
};

#endif