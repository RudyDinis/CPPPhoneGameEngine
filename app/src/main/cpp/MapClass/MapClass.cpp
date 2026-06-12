/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapClass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:52:11 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/12 17:58:43 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MapClass.hpp"

Map::Map(/* args */)
{
}

void Map::generateMap(Scene* scene, AAssetManager *mgr, Screen *screen, ResourceManager *resourceManager)
{
	float tileW = 200.0f;
	float tileH = tileW * (1023.0f / 1024.0f);
	float roofH = tileW * (593.0f / 1024.0f);

	float stepX = tileW / 2.38f;
	float stepY = roofH / 2.38f;

	float originX = 1000.0f;
	float originY = 160.0f;

	for (int row = 0; row < 30; row++)
	{
		for (int col = 0; col < 30; col++)
		{
			float sx = originX + (col - row) * (stepX);
			float sy = originY + (col + row) * (stepY);

			std::string id = std::to_string(col) + ":" + std::to_string(row);
			Object *square = new Object(id, sx, sx + tileW, sy, sy + tileH, mgr, screen, "grass", "default", true, resourceManager);
			scene->addObject(square);
		}
	}
}

Map::~Map()
{
}