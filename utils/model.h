#pragma once
#include <vector>

#include <glm/glm.hpp>


#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "../core/ressourcemanager.h"

#include "mesh.h"

class Model {
public:
	Model() 
	:isInstanced(true) {

	};
	Model(bool _isInstanced);

public:
	const bool isInstanced;

	// adds the instancing VBO to all mesh VAOs
	void finishModel();

	const std::vector<Mesh>& getMeshes();
	void addMesh( Mesh _mesh );

	void setInstances( std::vector<glm::mat4> _instances );
	unsigned int getInstanceCount();

private:
	std::vector<Mesh> meshes;

private:
	VBO instancing_vbo;
	std::vector<glm::mat4> indexedArray;
};