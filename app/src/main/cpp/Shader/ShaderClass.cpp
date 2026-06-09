/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 19:07:26 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/08 19:07:27 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShaderClass.hpp"

std::string get_file_contents(AAssetManager *mgr, const char *filename)
{
	AAsset *asset = AAssetManager_open(mgr, filename, AASSET_MODE_BUFFER);
	if (!asset)
		throw std::runtime_error(std::string("Cannot open asset: ") + filename);

	size_t size = AAsset_getLength(asset);
	std::string contents(size, '\0');
	AAsset_read(asset, &contents[0], size);
	AAsset_close(asset);
	return contents;
}

Shader::Shader(AAssetManager* mgr, const char *vertexFile, const char *fragmentFile)
{
	std::string vertexCode = get_file_contents(mgr, vertexFile);
	std::string fragmentCode = get_file_contents(mgr, fragmentFile);

	const char *vertexSource = vertexCode.c_str();
	const char *fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	ID = glCreateProgram();

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}
