#pragma once
#include <vector>
#include "definitions.h"

struct  VertexAttributes {
	const bool hasPosition;
	const bool hasNormal;
	const bool hasTexCoord;
};

class VBO {
private:
	unsigned int id;


public:
	VBO();
	VBO(std::vector<float> _vertices);

	unsigned int getId();
	void BufferData( std::vector<float> _vertices );

	void bind();
	static void unbind();
};