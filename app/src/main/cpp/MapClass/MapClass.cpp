/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapClass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:52:11 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/16 12:50:43 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MapClass.hpp"

Map::Map(/* args */)
{
}

vec2 Map::randomGradient(int ix, int iy)
{
	unsigned int seed = ix * 1836311903 ^ iy * 2971215073 ^ this->seed;
	seed = (seed ^ (seed >> 16)) * 0x45d9f3b;
	seed = (seed ^ (seed >> 16)) * 0x45d9f3b;
	seed = seed ^ (seed >> 16);

	float angle = (float)seed / (float)4294967295 * 2.0f * M_PI;
	return {std::cos(angle), std::sin(angle)};
}

float smoothstep(float w)
{
	if (w <= 0.0)
		return 0.0;
	if (w >= 1.0)
		return 1.0;
	return w * w * (3.0 - 2.0 * w);
}

float interpolation(float a0, float a1, float w)
{
	return (a0 + (a1 - a0) * smoothstep(w));
}

float Map::dotGridGradient(int ix, int iy, float x, float y)
{
	vec2 g = this->randomGradient(ix, iy);
	float dx = x - (float)ix;
	float dy = y - (float)iy;

	return (dx * g.x + dy * g.y);
}

float Map::perlin(float x, float y)
{
	int x0 = std::floor(x);
	int x1 = x0 + 1;
	int y0 = std::floor(y);
	int y1 = y0 + 1;

	float sx = x - (float)x0;
	float sy = y - (float)y0;

	float n0, n1, ix0, ix1, value;

	n0 = this->dotGridGradient(x0, y0, x, y);
	n1 = this->dotGridGradient(x1, y0, x, y);
	ix0 = interpolation(n0, n1, sx);
	n0 = this->dotGridGradient(x0, y1, x, y);
	n1 = this->dotGridGradient(x1, y1, x, y);
	ix1 = interpolation(n0, n1, sy);
	value = interpolation(ix0, ix1, sy);

	return value;
}

void Map::generateMap(Scene *scene, AAssetManager *mgr, Screen *screen, ResourceManager *resourceManager)
{
	resourceManager->loadTextures(mgr, "grass", "textures/ground/grass.png");
	resourceManager->loadTextures(mgr, "sand", "textures/ground/sand.png");
	resourceManager->loadTextures(mgr, "water", "textures/ground/water.png");

	float tileW = 200.0f;
	float tileH = tileW * (1023.0f / 1024.0f);
	float roofH = tileW * (593.0f / 1024.0f);

	float stepX = tileW / 2.38f;
	float stepY = roofH / 2.38f;

	float originX = 1000.0f;
	float originY = 160.0f;

	float scale = 0.15f;

	for (int row = 0; row < 30; row++)
	{
		for (int col = 0; col < 30; col++)
		{
			float sx = originX + (col - row) * (stepX);
			float sy = originY + (col + row) * (stepY);

			std::string id = std::to_string(col) + ":" + std::to_string(row);
			float v = perlin(row * scale, col * scale);
			int c = (int)((v + 1.0f) * 4.5f + 0.5f);
			Object *square;
			
			if (c < 3)
				square = new Object(id, sx, sx + tileW, sy, sy + tileH, mgr, screen, "water", "default", true, resourceManager);
			else if (c == 3)
				square = new Object(id, sx, sx + tileW, sy, sy + tileH, mgr, screen, "sand", "default", true, resourceManager);
			else
				square = new Object(id, sx, sx + tileW, sy, sy + tileH, mgr, screen, "grass", "default", true, resourceManager);

			scene->addObject(square);
		}
	}
}

Map::~Map()
{
}