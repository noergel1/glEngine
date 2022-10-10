#include "terrain.h"

Terrain::Terrain() 
	:computeDensityShader(RessourceManager::GetShader("compute/density"))
	,generateMeshShader(RessourceManager::GetShader("compute/cubesFromDensity"))
{
}

void Terrain::generateChunkDensity( unsigned int _x, unsigned int _y, unsigned int _z ) {
	//Texture_3D newChunk( _x+1, _y+1, _z+1);
	Texture_3D newChunk = Texture_3D(_x+1, _y+1, _z+1, GL_RED);

	Shader::useShader( computeDensityShader );
	glBindImageTexture( 0, newChunk.getID(), 0, true, 0, GL_WRITE_ONLY, GL_R32F );
	glDispatchCompute( _x + 1, _y + 1, _z + 1 );

	// make sure writing to image has finished before read
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

Mesh Terrain::generateChunkMesh() {
	Shader::useShader( generateMeshShader );
	unsigned int vertexBuffer = 0;
	glGenBuffers( 1, &vertexBuffer );
	glBindBuffer( GL_SHADER_STORAGE_BUFFER, vertexBuffer );

	// maybe change GL_DYNAMIC_DRAW if data won't be written to multiple times
	unsigned int cubeFloatCount = 36 * (3 + 3 + 2);
	unsigned int bytesPerChunk = cubeFloatCount * 32 * 32 * 4;
	glBufferData( GL_SHADER_STORAGE_BUFFER, bytesPerChunk, NULL, GL_DYNAMIC_DRAW );
	glBindBuffer( GL_SHADER_STORAGE_BUFFER, 0 );


	unsigned int indiceBuffer = 0;
	glGenBuffers( 1, &indiceBuffer );
	glBindBuffer( GL_SHADER_STORAGE_BUFFER, indiceBuffer );

	// maybe change GL_DYNAMIC_DRAW if data won't be written to multiple times
	unsigned int cubeFloatCount = 36 * (3 + 3 + 2);
	unsigned int bytesPerChunk = cubeFloatCount * 32 * 32 * 4;
	glBufferData( GL_SHADER_STORAGE_BUFFER, bytesPerChunk, NULL, GL_DYNAMIC_DRAW );
	glBindBuffer( GL_SHADER_STORAGE_BUFFER, 0 );

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, vertexBuffer);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, indiceBuffer);

	glDispatchCompute( 1,1,1 );
	glMemoryBarrier( GL_ALL_BARRIER_BITS );

	VBO vbo( vertexBuffer );
	EBO ebo( indiceBuffer );

}
