/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceManager.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:53:25 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/17 18:12:04 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ResourceManager.hpp"

#include <android/asset_manager.h>

#include "../libs/stb_image.h"

ResourceManager::ResourceManager(/* args */)
{
}

void ResourceManager::loadTextures(AAssetManager *mgr, const std::string &name, const char *texture)
{
	AAsset *asset = AAssetManager_open(mgr, texture, AASSET_MODE_BUFFER);
	if (!asset)
		throw std::runtime_error("Cannot found texture file");
	size_t size = AAsset_getLength(asset);
	unsigned char *buffer = new unsigned char[size];
	AAsset_read(asset, buffer, size);

	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *bytes = stbi_load_from_memory(
		buffer, size, &widthImg, &heightImg, &numColCh, 0);

	if (!bytes)
	{
		AAsset_close(asset);
		stbi_image_free(bytes);
		delete[] buffer;
		throw std::runtime_error("Je sais pas quoi print");
	}

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLenum format;

	if (numColCh == 4)
		format = GL_RGBA;
	else if (numColCh == 3)
		format = GL_RGB;
	else
		format = GL_RED;

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		format,
		widthImg,
		heightImg,
		0,
		format,
		GL_UNSIGNED_BYTE,
		bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	AAsset_close(asset);
	stbi_image_free(bytes);
	delete[] buffer;

	this->textures.insert({name, textureID});
}

void ResourceManager::loadShader(AAssetManager *mgr, const std::string &name, const char *vert, const char *frag)
{
	this->shaders.insert({name, new Shader(mgr, vert, frag)});
}

GLuint ResourceManager::getTexture(const std::string &name)
{
	return this->textures.find(name)->second;
}

Shader *ResourceManager::getShader(const std::string &name)
{
	return this->shaders.find(name)->second;
}

ResourceManager::~ResourceManager()
{
	for (auto &texture : this->textures)
	{
		glDeleteTextures(1, &texture.second);
	}
}