/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SquareClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 13:18:16 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/16 18:27:31 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUARE_CLASS_HPP
#define SQUARE_CLASS_HPP

#include <GLES3/gl3.h>
#include <android/asset_manager.h>
#include <android/log.h>

#include "../EBOClass/EBOClass.hpp"
#include "../Shader/ShaderClass.hpp"
#include "../VAOClass/VAOClass.hpp"
#include "../VBOClass/VBOClass.hpp"
#include "../ScreenClass/ScreenClass.hpp"
#include "../ResourceManagerClass/ResourceManager.hpp"

typedef struct t_rgba
{
	int r;
	int g;
	int b;
	int a;
} s_rgba;


class Square
{
private:
	Shader *shaderProgram = nullptr;
	VAO *VAO1 = nullptr;
	VBO *VBO1 = nullptr;
	EBO *EBO1 = nullptr;
	GLuint _texture;
public:
	Square(float, float, float, float, s_rgba, AAssetManager*, Screen *, ResourceManager *resourceManager, const char*, const char*, float uRepeatX = 1.0f, float uRepeatY = 1.0f);
	Shader *getShader();
	VAO *getVAO();
	VBO *getVBO();
	EBO *getEBO();
	GLuint getTexture();
	~Square();
};


#endif
