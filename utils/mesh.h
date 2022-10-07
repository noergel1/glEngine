#pragma once
#include "vao.h"
#include "vbo.h"
#include "ebo.h"

#include "definitions.h"
#include "texture_2d.h"

class Mesh {
	struct MeshTexture {
		Texture texture;
		unsigned int place;
		GLenum blendMode;
		float blendFactor;
		GLenum wrapMode;
	};

public:
	Mesh( VBO _vbo, EBO _ebo, unsigned int _indiceCount, bool _hasNormals, bool _hasTexCoords, bool _hasTangentSpace );
	Mesh( std::vector<float> _vertices, std::vector<unsigned int> _indices, bool _hasNormals, bool _hasTexCoords, bool _hasTangentSpace );

public:
	VAO getVao();
	void addTexture( Texture _texture, unsigned int _place, GLenum _blendMode = GL_FUNC_ADD, float _blendFactor = 1.0f, GLenum _wrapMode = GL_REPEAT);
	void setShader(const unsigned int _shader);
	void bindVao();
	void bindTextures();

public: 
	VAO m_vao;
	VBO m_vbo;
	EBO m_ebo;
	unsigned int indiceCount = 0;
	unsigned int entityCount = 0;

	unsigned int m_shader = 0;


private:
	std::vector<MeshTexture> textures;
};