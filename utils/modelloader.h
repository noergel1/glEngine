#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <string>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "model.h"
#include "../core/ressourcemanager.h"
#include "benchmark.h"

class ModelLoader {

public:
	ModelLoader( const ModelLoader& ) = delete;
	ModelLoader& operator=(ModelLoader& other) = delete;

private:
	ModelLoader() {};


public:
	static ModelLoader& Get() {
		static ModelLoader m_Instance;
		return m_Instance;
	}

	static Model LoadModel( std::string _filepath, bool _isInstanced ) {
		return Get().ILoadModel(_filepath, _isInstanced);
	}

private:
	Model ILoadModel( std::string _filepath, bool _isInstanced );

private:
	std::string directory;
	bool modelIsInstanced = true;

private:
	void processNode( aiNode* _node, const aiScene* _scene, Model* _model);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	void loadMaterialTexturesAndGetShader(aiMaterial *mat, Mesh* _mesh, unsigned int _vertexFormat);
	void loadTextureIntoMesh( Mesh* _mesh, aiMaterial* _mat, aiTextureType _textureType, unsigned int _whichTexture, unsigned int _curTextureSlot );
};