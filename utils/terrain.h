#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>

#include "../core/ressourcemanager.h"
#include "texture_3d.h"
#include "mesh.h"

class Terrain {
#define CHUNK_WIDTH 32
#define CHUNK_HEIGHT 32


public:
	Terrain();

private:
	void generateChunkDensity( unsigned int _x, unsigned int _y, unsigned int _z );
	Mesh generateChunkMesh();

private:
	// 2D Array of density values at pos [x][y]
	Texture_3D m_chunkDensities[19][19];

	const unsigned int computeDensityShader;
	const unsigned int generateMeshShader;

};