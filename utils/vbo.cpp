#include "vbo.h"



VBO::VBO() {
	glGenBuffers(1, &id);
}

VBO::VBO( std::vector<float> _vertices ) {
    glGenBuffers(1, &id);

    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _vertices.size(), &_vertices.at(0), GL_STATIC_DRAW);

	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void VBO::BufferData( std::vector<float> _vertices ) {
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _vertices.size(), &_vertices.at(0), GL_STATIC_DRAW);

	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void VBO::bind() {
	glBindBuffer( GL_ARRAY_BUFFER, id );
}

void VBO::unbind() {
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}
