#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <GLES3/gl3.h>

class EBO
{
private:
	/* data */
public:
	GLuint ID;
	EBO(GLuint * indices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};



#endif