#ifndef TEXTCLASS_HPP
#define TEXTCLASS_HPP

#include <map>
#include <string>
#include <android/asset_manager.h>
#include <GLES3/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../libs/stb_truetype.h"

#define ATLAS_WIDTH  512
#define ATLAS_HEIGHT 512
#define FIRST_CHAR   32
#define NUM_CHARS    96

struct FontData
{
	stbtt_bakedchar cdata[NUM_CHARS];
	GLuint texture;
    GLuint          VAO;
    GLuint          VBO;
    GLuint          shaderProgram;
};

class Text
{
private:
	std::map<std::string, FontData*> fonts;

public:
	Text();
	bool loadFont(AAssetManager *mgr, std::string name, const char *path, float size);
	GLuint createShader();
	FontData* getFont(std::string name);
	void initBuffers(FontData *font);
	void drawText(std::string name, const char *text, float x, float y,
                    float r, float g, float b, float a, glm::mat4 projection);
	~Text();
};

#endif