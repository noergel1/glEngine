#include "modelloader.h"

Model ModelLoader::ILoadModel( std::string _filepath, bool _isInstanced ) {
    using namespace Assimp;

    directory = _filepath.substr(0, _filepath.find_last_of('/')) + "/";
    modelIsInstanced = _isInstanced;

	Model model = Model(modelIsInstanced);

	Importer importer;

    Benchmark benchmark( "loading scene " + _filepath );
    const aiScene* scene = importer.ReadFile( _filepath,
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices );
    benchmark.endBenchmark();

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << "\n";
    }

    processNode( scene->mRootNode, scene, &model);

    // adds the models instancing vbo to all meshes
    model.finishModel();

	return model;
}

void ModelLoader::processNode( aiNode* _node, const aiScene* _scene, Model* _model ) {
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < _node->mNumMeshes; i++)
    {
        aiMesh *mesh = _scene->mMeshes[_node->mMeshes[i]]; 
        Mesh newMesh = processMesh( mesh, _scene );
        if (newMesh.m_shader != 0) {
            _model->addMesh(newMesh);
        }
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < _node->mNumChildren; i++)
    {
        processNode(_node->mChildren[i], _scene, _model);
    }

}

Mesh ModelLoader::processMesh( aiMesh* mesh, const aiScene* scene ) {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    bool hasNormals = false;
    bool hasTexCoords = false;
    bool hasTangentSpace = false;
    
    // reserve memory in vertices and indices vector for performance
    unsigned int totalIndexCount = mesh->mNumFaces * 3;

    unsigned int totalVertexFloatsCount = 3; // pos as given
    if (mesh->HasNormals()) totalVertexFloatsCount += 3;
    if (mesh->mTextureCoords[0]) totalVertexFloatsCount += 2;
    if (mesh->HasTangentsAndBitangents()) totalVertexFloatsCount += 6;
    totalVertexFloatsCount *= mesh->mNumVertices;

    vertices.reserve( totalVertexFloatsCount );
    indices.reserve( totalIndexCount );

    // get vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {

        if (!mesh->HasPositions()) {
            std::cout << "wtf mesh doesn't have positions?? \n";
            throw("error in processMesh\n");
        }
        vertices.push_back( mesh->mVertices[i].x );
        vertices.push_back( mesh->mVertices[i].y );
        vertices.push_back( mesh->mVertices[i].z );

        if (mesh->HasNormals()) {
            hasNormals = true;
            vertices.push_back( mesh->mNormals[i].x );
            vertices.push_back( mesh->mNormals[i].y );
            vertices.push_back( mesh->mNormals[i].z );
        }

        if (mesh->mTextureCoords[0]) {
            hasTexCoords = true;
            vertices.push_back( mesh->mTextureCoords[0][i].x );
            vertices.push_back( mesh->mTextureCoords[0][i].y );
        }

        if (mesh->HasTangentsAndBitangents()) {
            hasTangentSpace = true;

            vertices.push_back( mesh->mTangents[i].x );
            vertices.push_back( mesh->mTangents[i].y );
            vertices.push_back( mesh->mTangents[i].z );

            vertices.push_back( mesh->mBitangents[i].x );
            vertices.push_back( mesh->mBitangents[i].y );
            vertices.push_back( mesh->mBitangents[i].z );
        }


    }

    // get indices
    for (int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++) {
            indices.push_back( face.mIndices[j]);
        }
    }


    // generate the new mesh
    VBO meshVBO = VBO( vertices );
    EBO meshEBO = EBO( indices );
    Mesh newMesh = Mesh( meshVBO, meshEBO, indices.size(), hasNormals, hasTexCoords, hasTangentSpace );


    // get vertex layout
    // binary coded -> LSB to MSB
    // Position
    // Normal
    // TexCoord
    // (Bit-)Tangent
    // Example: Mesh with Position, Normals and Tangentspace
    // ==>  1011
    //  ==> Vertexlayout = 11

    unsigned int vertexFormat = 1;
    if (hasNormals) vertexFormat += 2;
    if (hasTexCoords) vertexFormat += 4;
    if (hasTangentSpace) vertexFormat += 8;
    

    // textures
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        loadMaterialTexturesAndGetShader( material, &newMesh, vertexFormat );
        
    }


    return newMesh;
}

// return the count of textures of specified type
void ModelLoader::loadMaterialTexturesAndGetShader(aiMaterial *mat, Mesh* _mesh, unsigned int _vertexFormat) {
        aiString str;

        unsigned int diffuseCount = mat->GetTextureCount( aiTextureType_DIFFUSE );
        bool hasSpecular = mat->GetTextureCount( aiTextureType_SPECULAR );
        bool hasAmbient = mat->GetTextureCount( aiTextureType_AMBIENT );
        bool hasEmissive = mat->GetTextureCount( aiTextureType_EMISSIVE );
        bool hasHeight = mat->GetTextureCount( aiTextureType_HEIGHT );
        bool hasNormal = mat->GetTextureCount( aiTextureType_NORMALS );
        bool hasShininess = mat->GetTextureCount( aiTextureType_SHININESS );

        unsigned int curTextureSlot = 0;

        // diffuse maps
        for(unsigned int i = 0; i < diffuseCount; i++)
        {
            loadTextureIntoMesh(_mesh, mat, aiTextureType_DIFFUSE, i, i);
            curTextureSlot++;
        }

        if (hasSpecular) {
            loadTextureIntoMesh(_mesh, mat, aiTextureType_SPECULAR, 0, 7);
            curTextureSlot++;
        }

        if (hasAmbient) {
            loadTextureIntoMesh(_mesh, mat, aiTextureType_AMBIENT, 0, 8);
            curTextureSlot++;
        }

        if (hasEmissive) {
            loadTextureIntoMesh(_mesh, mat, aiTextureType_EMISSIVE, 0, 9);
            curTextureSlot++;
        }

        if (hasHeight) {
            loadTextureIntoMesh(_mesh, mat, aiTextureType_HEIGHT, 0, 10);
            curTextureSlot++;
        }

        if (hasNormal) {
            loadTextureIntoMesh(_mesh, mat, aiTextureType_NORMALS, 0, 11);
            curTextureSlot++;
        }

        if (hasShininess) {
            loadTextureIntoMesh(_mesh, mat, aiTextureType_SHININESS, 0, 12);
            curTextureSlot++;
        }

        //get the needed shader from ressourcemanager
        const unsigned int meshShader = RessourceManager::GetShader( diffuseCount, hasSpecular, hasAmbient, hasEmissive, hasHeight, hasNormal, _vertexFormat );
        _mesh->setShader( meshShader );
}

void ModelLoader::loadTextureIntoMesh( Mesh* _mesh, aiMaterial* _mat, aiTextureType _textureType, unsigned int _whichTexture, unsigned int _curTextureSlot ) {
            aiString path;
            aiTextureMapping mapping;
            unsigned int uvindex;
            float blendStrength;
            aiTextureOp operation;
            aiTextureMapMode mapMode;

            _mat->GetTexture(_textureType, _whichTexture, &path, &mapping, &uvindex, &blendStrength, &operation, &mapMode);

            GLenum textureMapping = GL_REPEAT;
            switch (mapMode) {
                case(aiTextureMapMode_Wrap): {
                    textureMapping = GL_REPEAT;
                    break;
                }
                case(aiTextureMapMode_Clamp): {
                    textureMapping = GL_CLAMP_TO_EDGE;
                    break;
                }
                case(aiTextureMapMode_Decal): {
                    textureMapping = GL_CLAMP_TO_BORDER;
                    break;
                }
                case(aiTextureMapMode_Mirror): {
                    textureMapping = GL_MIRRORED_REPEAT;
                    break;
                }
            }

            std::string texturepath = directory;
            texturepath.append(path.C_Str());
            Texture newTexture = RessourceManager::GetTexture( texturepath );
            _mesh->addTexture( newTexture, _curTextureSlot, textureMapping, textureMapping);
}