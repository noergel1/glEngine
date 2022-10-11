#pragma once
#include <vector>
#include <glad/gl.h>
#include <glm/glm.hpp>

class EBO {
private:
	unsigned int id;


public:
	EBO(std::vector<unsigned int> _indices);
	EBO();														// standard constructor for index arrays

	unsigned int getId();

	void bind();
	static void unbind();
};