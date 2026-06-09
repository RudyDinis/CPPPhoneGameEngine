#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <GLES3/gl3.h>

#include <android/asset_manager.h>
#include <stdexcept>

std::string get_file_contents(AAssetManager *mgr, const char *filename);

class Shader
{
private:
	/* data */
public:
	GLuint ID;
	Shader(AAssetManager *mgr, const char *vertexFile, const char *fragmentFile);
	void Activate();
	void Delete();
};

#endif