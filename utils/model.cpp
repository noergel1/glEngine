#include "model.h"

Model::Model(bool _isInstanced) 
	:instancing_vbo(VBO())
	,isInstanced(_isInstanced)
{
}

void Model::finishModel() {
	
	if (isInstanced) {

		for (int i = 0; i < meshes.size(); i++) {
			VAO meshVao = meshes[i].getVao();
			meshVao.bind();
			instancing_vbo.bind();

			VAO::enableInstancing();

			meshVao.unbind();
			instancing_vbo.unbind();
		}
	}
}

const std::vector<Mesh>& Model::getMeshes() {
	return meshes;
}

void Model::addMesh( Mesh _mesh ) {
	meshes.push_back( _mesh );
}


void Model::setInstances( std::vector<glm::mat4> _instances ) {
	instancing_vbo.bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * _instances.size(), &_instances.at(0), GL_STATIC_DRAW);
	instancing_vbo.unbind();
	indexedArray = _instances;

	unsigned int entityCount = indexedArray.size();
	for (int i = 0; i < meshes.size(); i++) {
		meshes[i].entityCount = entityCount;
	}
}

unsigned int Model::getInstanceCount() {
	return indexedArray.size();
}


