#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <GLES3/gl3.h>

class VBO
{
private:
	/* data */
public:
	GLuint ID;
	VBO(GLfloat * verticales, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};



#endif