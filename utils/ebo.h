#pragma once
#include <vector>
#include <glad/gl.h>
#include <glm/glm.hpp>

class EBO {
private:
	unsigned int id;


public:
	//EBO();														// standard constructor for index arrays
	EBO(std::vector<unsigned int> _indices);

	void bind();
	static void unbind();
};