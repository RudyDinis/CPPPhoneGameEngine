/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VAOClass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 19:12:37 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/08 19:14:18 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VAOClass.hpp"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();

	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);

	VBO.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}