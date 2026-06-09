/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EBOClass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 19:12:58 by rdinis            #+#    #+#             */
/*   Updated: 2026/06/08 19:12:59 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EBOClass.hpp"

EBO::EBO(GLuint * indices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}