/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VBOClass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 19:12:50 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/08 19:12:51 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VBOClass.hpp"

VBO::VBO(GLfloat * verticales, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, verticales, GL_STATIC_DRAW);

}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}