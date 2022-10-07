#pragma once
#include "vbo.h"
#include "ebo.h"

class VAO {

private:
	unsigned int id;


public:
	VAO();
	VAO( VBO _vbo, EBO _ebo, bool _hasNormals, bool _hasTexCoords, bool _hasTangentSpace );

	void bind();
	static void unbind();

	static void setVertexAttributes( bool _hasNormals, bool _hasTexCoords, bool _hasTangentSpace );
	static void enableInstancing();
};