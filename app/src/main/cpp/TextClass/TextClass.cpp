/*CODE MADE BY CLAUDE*/

#include "TextClass.hpp"

GLuint Text::createShader()
{
	const char *vertSrc = R"(
        attribute vec2 aPos;
        attribute vec2 aTexCoord;
        uniform mat4 uProjection;
        varying vec2 vTexCoord;
        void main()
        {
            gl_Position = uProjection * vec4(aPos, 0.0, 1.0);
            vTexCoord = aTexCoord;
        }
    )";

	const char *fragSrc = R"(
        precision mediump float;
        uniform sampler2D uTexture;
        uniform vec4 uColor;
        varying vec2 vTexCoord;
        void main()
        {
            float alpha = texture2D(uTexture, vTexCoord).a;
            gl_FragColor = vec4(uColor.rgb, uColor.a * alpha);
        }
    )";

    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vertSrc, nullptr);
    glCompileShader(vert);

    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fragSrc, nullptr);
    glCompileShader(frag);

    GLuint program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);

    glDeleteShader(vert);
    glDeleteShader(frag);

    return program;
}

bool Text::loadFont(AAssetManager *mgr, std::string name, const char *path, float size)
{
	AAsset *asset = AAssetManager_open(mgr, path, AASSET_MODE_BUFFER);
	if (!asset)
		return false;

	int fileSize = AAsset_getLength(asset);
	unsigned char *ttfbuffer = new unsigned char[fileSize];
	AAsset_read(asset, ttfbuffer, fileSize);
	AAsset_close(asset);

	FontData *font = new FontData();
	unsigned char bitmap[ATLAS_WIDTH * ATLAS_HEIGHT];

	stbtt_BakeFontBitmap(ttfbuffer, 0, size, bitmap, ATLAS_WIDTH, ATLAS_HEIGHT, FIRST_CHAR, NUM_CHARS, font->cdata);

	glGenTextures(1, &font->texture);
	glBindTexture(GL_TEXTURE_2D, font->texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, ATLAS_WIDTH, ATLAS_HEIGHT, 0, GL_ALPHA, GL_UNSIGNED_BYTE, bitmap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	font->shaderProgram = this->createShader();
	this->initBuffers(font);
	this->fonts.insert({name, font});
	
	delete[] ttfbuffer;
	return true;
}

FontData *Text::getFont(std::string name)
{
	auto it = this->fonts.find(name);
	if (it == this->fonts.end())
		return nullptr;
	return it->second;
}

void Text::initBuffers(FontData *font)
{
	glGenVertexArrays(1, &font->VAO); // si OpenGL ES 3.0
	glGenBuffers(1, &font->VBO);

	glBindVertexArray(font->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, font->VBO);

	// 4 vertices par quad, chaque vertex = vec2 pos + vec2 uv = 4 floats
	// on alloue pour 256 caractères max par draw call
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 4 * 256, nullptr, GL_DYNAMIC_DRAW);

	// attribut 0 : position (x, y)
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// attribut 1 : texcoord (u, v)
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Text::drawText(std::string name, const char *text, float x, float y,
                    float r, float g, float b, float a, glm::mat4 projection)
{
	FontData *font = this->getFont(name);
	if (!font)
		return;

	glUseProgram(font->shaderProgram);

	// passer la couleur et la projection au shader
	GLint colorLoc = glGetUniformLocation(font->shaderProgram, "uColor");
	GLint projLoc = glGetUniformLocation(font->shaderProgram, "uProjection");
	glUniform4f(colorLoc, r, g, b, a);
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, font->texture);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindVertexArray(font->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, font->VBO);

	float startX = x;
	const char *ptr = text;

	while (*ptr)
	{
		if (*ptr >= FIRST_CHAR && *ptr < FIRST_CHAR + NUM_CHARS)
		{
			stbtt_aligned_quad q;
			stbtt_GetBakedQuad(font->cdata,
							   ATLAS_WIDTH, ATLAS_HEIGHT,
							   *ptr - FIRST_CHAR,
							   &x, &y, &q, 1);

			// un quad = 6 vertices (2 triangles)
			float vertices[6][4] = {
				{q.x0, q.y0, q.s0, q.t0}, // triangle 1
				{q.x1, q.y0, q.s1, q.t0},
				{q.x0, q.y1, q.s0, q.t1},

				{q.x1, q.y0, q.s1, q.t0}, // triangle 2
				{q.x1, q.y1, q.s1, q.t1},
				{q.x0, q.y1, q.s0, q.t1},
			};

			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		ptr++;
	}

	glBindVertexArray(0);
	glDisable(GL_BLEND);
}

Text::Text()
{
}

Text::~Text()
{
	for (auto &pair : this->fonts)
	{
		glDeleteTextures(1, &pair.second->texture);
		delete pair.second;
	}
}