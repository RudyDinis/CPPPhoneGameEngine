#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include "../Shader/ShaderClass.hpp"
#include <android/asset_manager.h>
#include <map>
#include <string>

class ResourceManager
{
private:
	std::map<std::string, Shader*> shaders;
	std::map<std::string, GLuint> textures;
public:
	ResourceManager(/* args */);
	void loadShader(AAssetManager *mgr, const std::string &name, const char *vert, const char *frag);
	void loadTextures(AAssetManager* mgr, const std::string &name, const char* texture);
	GLuint getTexture(const std::string &name);
	Shader *getShader(const std::string &name);
	~ResourceManager();
};

#endif