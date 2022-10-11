#include "ebo.h"

EBO::EBO() {
	glGenBuffers( 1, &id );
}

EBO::EBO( std::vector<unsigned int> _indices ) {
	glGenBuffers(1, &id);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * _indices.size(), &_indices.at(0), GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int EBO::getId() {
	return id;
}

void EBO::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void EBO::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
