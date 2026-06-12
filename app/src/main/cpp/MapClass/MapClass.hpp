#ifndef MAPCLASS_HPP
#define MAPCLASS_HPP

#include "../SceneClass/SceneClass.hpp"
#include "../ScreenClass/ScreenClass.hpp"
#include "../ResourceManagerClass/ResourceManager.hpp"

#include <android/asset_manager.h>

class Map
{
private:
public:
	Map();
	void generateMap(Scene*,  AAssetManager *, Screen *, ResourceManager *resourceManager);
	~Map();
};

#endif