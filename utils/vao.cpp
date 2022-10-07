#include "vao.h"

VAO::VAO() {
	glGenVertexArrays(1, &id);
}

VAO::VAO(  VBO _vbo, EBO _ebo, bool _hasNormals, bool _hasTexCoords, bool _hasTangentSpace ) {
	glGenVertexArrays(1, &id);
	glBindVertexArray(id);

	_vbo.bind();
	_ebo.bind();

	VAO::setVertexAttributes( _hasNormals, _hasTexCoords, _hasTangentSpace );

	// bones


	
	glBindVertexArray(0);
	_vbo.unbind();
	_ebo.unbind();

}

void VAO::bind() {
	glBindVertexArray(id);
}

void VAO::unbind() {
	glBindVertexArray(0);
}

void VAO::setVertexAttributes( bool _hasNormals, bool _hasTexCoords, bool _hasTangentSpace ) {

	unsigned long long floatsPerVertex = 3;
	if (_hasNormals) floatsPerVertex += 3;
	if (_hasTexCoords) floatsPerVertex += 2;
	if (_hasTangentSpace) floatsPerVertex += 6;

	// position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (void*)0);
	// normal attribute
	if (_hasNormals) {
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (void*)(3 * sizeof(float)));
	}
	// texCoord attribute
	if (_hasTexCoords) {
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (void*)(6 * sizeof(float)));
	}

	// tangent and bitangent attribute
	if (_hasTangentSpace) {
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (void*)(8 * sizeof(float)));

		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (void*)(11 * sizeof(float)));
	}
}

void VAO::enableInstancing() {
	std::size_t vec4Size = sizeof(glm::vec4);
    glEnableVertexAttribArray(6); 
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
    glEnableVertexAttribArray(7); 
    glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
    glEnableVertexAttribArray(8); 
    glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
    glEnableVertexAttribArray(9); 
    glVertexAttribPointer(9, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

    glVertexAttribDivisor(6, 1);
    glVertexAttribDivisor(7, 1);
    glVertexAttribDivisor(8, 1);
    glVertexAttribDivisor(9, 1);
}
