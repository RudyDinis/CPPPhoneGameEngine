#ifndef TILEMAPCLASS_HPP
#define TILEMAPCLASS_HPP

#include <map>
#include <vector>
#include <GLES3/gl3.h>
#include <android/asset_manager.h>
#include <android/log.h>

#include "../EBOClass/EBOClass.hpp"
#include "../Shader/ShaderClass.hpp"
#include "../VAOClass/VAOClass.hpp"
#include "../VBOClass/VBOClass.hpp"
#include "../ScreenClass/ScreenClass.hpp"
#include "../ResourceManagerClass/ResourceManager.hpp"

struct UVRect
{
	float u0, v0, u1, v1;
};

struct TileInstance
{
	float x, y;
	float w, h;
	float u0, v0, u1, v1;
};

class TileMap
{
private:
	ResourceManager *resourceManager;
	GLuint atlasTexture;

	Shader *shaderProgram;
	VAO *_VAO;
	VBO *_VBO;
	EBO *_EBO;
	GLuint instanceVBO;

	std::vector<TileInstance> instances;
	std::map<char, UVRect> tileUV;

    GLint offsetLoc;
    GLint zoomLoc;
    GLint screenSizeLoc;
    GLint tex0Loc;

public:
	TileMap(ResourceManager *, AAssetManager *mgr);
	void setupBuffer();
	void generate(const char map[][30], int rows, int cols, Screen *screen);
	void render(Screen *screen, float offset_x, float offset_y, float zoom);
	~TileMap();
};

#endif