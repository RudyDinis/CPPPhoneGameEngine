#ifndef MAPCLASS_HPP
#define MAPCLASS_HPP

#include "../SceneClass/SceneClass.hpp"
#include "../ScreenClass/ScreenClass.hpp"
#include "../ResourceManagerClass/ResourceManager.hpp"

#include <chrono>
#include <android/asset_manager.h>
#include <cmath>	

struct vec2
{
	float x;
	float y;
};

class Map
{
private:
	float _gradient[16][16][2];
	unsigned int seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	int map[30][30];
public:
	Map();
	vec2 randomGradient(int ix, int iy);
	float dotGridGradient(int ix, int iy, float x, float y);
	float perlin(float x, float y);
	void generateMap(Scene*,  AAssetManager *, Screen *, ResourceManager *resourceManager);
	~Map();
};

#endif