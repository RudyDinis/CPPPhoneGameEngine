/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VAOClass.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 19:07:18 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/08 19:07:19 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <GLES3/gl3.h>
#include "../VBOClass/VBOClass.hpp"

class VAO
{
private:
	/* data */
public:
	GLuint ID;
	VAO();

	void LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

	void Bind();
	void Unbind();
	void Delete();
};

#endif