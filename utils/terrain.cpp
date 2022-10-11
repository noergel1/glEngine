#include "terrain.h"

Terrain::Terrain() 
	:computeDensityShader(RessourceManager::GetShader("compute/density"))
	,generateMeshShader(RessourceManager::GetShader("compute/cubesFromDensity"))
{
	m_meshes.push_back( generateChunkMesh() );
}

Texture_3D Terrain::generateChunkDensity( ) {
	//Texture_3D newChunk( _x+1, _y+1, _z+1);
	Texture_3D newChunk = Texture_3D(CHUNK_WIDTH+1, CHUNK_HEIGHT+1, CHUNK_DEPTH+1, GL_RED);

	Shader::useShader( computeDensityShader );
	//glBindImageTexture( 0, newChunk.getID(), 0, true, 0, GL_WRITE_ONLY, GL_R32F );
	//glDispatchCompute( CHUNK_WIDTH + 1, CHUNK_HEIGHT + 1, CHUNK_DEPTH + 1 );

	//// make sure writing to image has finished before read
	//glMemoryBarrier(GL_ALL_BARRIER_BITS);

	return newChunk;
}

Mesh Terrain::generateChunkMesh() {
	Texture_3D newChunk = generateChunkDensity();
	Shader::useShader( generateMeshShader );

	//glBindImageTexture( 0, newChunk.getID(), 0, true, 0, GL_READ_ONLY, GL_R32F );

	unsigned int cubesPerChunk = (CHUNK_WIDTH + 1) * (CHUNK_HEIGHT + 1) * (CHUNK_DEPTH + 1);

	VBO vertexBuffer = VBO();
	//unsigned int vertexBuffer = 0;
	//glGenBuffers( 1, &vertexBuffer );
	glBindBuffer( GL_SHADER_STORAGE_BUFFER, vertexBuffer.getId() );

	// maybe change GL_DYNAMIC_DRAW if data won't be written to multiple times
	unsigned int cubeFloatCount = 192;
	unsigned int bytesPerChunkVert = cubeFloatCount * cubesPerChunk * sizeof(float);
	glBufferData( GL_SHADER_STORAGE_BUFFER, cubeFloatCount * sizeof(float), NULL, GL_DYNAMIC_DRAW);
	glBindBuffer( GL_SHADER_STORAGE_BUFFER, 0 );


	EBO indiceBuffer = EBO();
	glBindBuffer( GL_SHADER_STORAGE_BUFFER, indiceBuffer.getId() );

	// maybe change GL_DYNAMIC_DRAW if data won't be written to multiple times
	unsigned int cubeUIntCount = 36;
	unsigned int bytesPerChunkInd = cubeUIntCount * cubesPerChunk * sizeof(unsigned int);
	glBufferData( GL_SHADER_STORAGE_BUFFER, cubeUIntCount * sizeof(unsigned int), NULL, GL_DYNAMIC_DRAW);
	glBindBuffer( GL_SHADER_STORAGE_BUFFER, 0 );

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, vertexBuffer.getId());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, indiceBuffer.getId());

	glDispatchCompute( 1,1,1 );
	glMemoryBarrier( GL_SHADER_STORAGE_BARRIER_BIT );

	Mesh chunkMesh = Mesh( vertexBuffer, indiceBuffer, cubesPerChunk * 36, true, true, false );
	chunkMesh.setShader( RessourceManager::GetShader( "terrain" ) );
	return chunkMesh;
}

std::vector<Mesh> Terrain::getMeshes() {
	return m_meshes;
}
