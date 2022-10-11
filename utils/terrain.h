#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>

#include "../core/ressourcemanager.h"
#include "texture_3d.h"
#include "mesh.h"
#include "ebo.h"

class Terrain {
#define CHUNK_WIDTH 32
#define CHUNK_HEIGHT 32
#define CHUNK_DEPTH 32


public:
	Terrain();
	std::vector<Mesh> getMeshes();

private:
	Texture_3D generateChunkDensity();
	Mesh generateChunkMesh();


private:
	std::vector<Mesh> m_meshes;

	// 2D Array of density values at pos [x][y]
	Texture_3D m_chunkDensities[19][19];

	const unsigned int computeDensityShader;
	const unsigned int generateMeshShader;

};