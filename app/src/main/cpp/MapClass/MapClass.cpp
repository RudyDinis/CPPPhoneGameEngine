/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapClass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:52:11 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/17 19:45:06 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MapClass.hpp"

Map::Map(ResourceManager *resourceManager, AAssetManager *mgr)
	: tilemap(new TileMap(resourceManager, mgr))
{
}

TileMap *Map::getTileMap()
{
	return this->tilemap;
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

void Map::generateMap(Screen *screen)
{
	float scale = 0.15f;

	for (int row = 0; row < 30; row++)
	{
		for (int col = 0; col < 30; col++)
		{
			float v = perlin(row * scale, col * scale);
			int c = (int)((v + 1.0f) * 4.5f + 0.5f);

			if (c < 3)
				this->map[row][col] = 'w';
			else if (c == 3)
				this->map[row][col] = 's';
			else
				this->map[row][col] = 'g';
		}
	}
	this->tilemap->generate(this->map, this->size, this->size, screen);
}

void Map::printMap()
{
	__android_log_print(ANDROID_LOG_INFO, "DEBUG MAP", "------------------------------");

	for (int row = 0; row < 30; row++)
	{
		std::string line = "";
		for (int col = 0; col < 30; col++)
		{
			line += this->map[row][col];
		}
		__android_log_print(ANDROID_LOG_INFO, "DEBUG MAP", "%s", line.c_str());
	}
}

Map::~Map()
{
	delete tilemap;
}