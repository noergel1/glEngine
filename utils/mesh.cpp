#include "mesh.h"

Mesh::Mesh( VBO _vbo, EBO _ebo, unsigned int _indiceCount, bool _hasNormals, bool _hasTexCoords, bool _hasTangentSpace ) 
	:m_vbo(_vbo)
	,m_ebo(_ebo)
	,m_vao(_vbo, _ebo, _hasNormals, _hasTexCoords, _hasTangentSpace)
	,indiceCount(_indiceCount)
{
}


Mesh::Mesh( std::vector<float> _vertices, std::vector<unsigned int> _indices, bool _hasNormals, bool _hasTexCoords, bool _hasTangentSpace ) 
	:m_vbo(_vertices)
	,m_ebo(_indices)
	,indiceCount(_indices.size())
{
	m_vao = VAO( m_vbo, m_ebo, _hasNormals, _hasTexCoords, _hasTangentSpace );
	return;
}

VAO Mesh::getVao() {
	return m_vao;
}

void Mesh::bindVao() {
	m_vao.bind();
}

void Mesh::bindTextures() {
	for (auto texture : textures) {
		texture.texture.use( texture.place );
	}
}


void Mesh::addTexture( Texture _texture, unsigned int _place, GLenum _blendMode, float _blendFactor, GLenum _wrapMode) {
	MeshTexture newTexture = MeshTexture( {
		_texture,
		_place,
		_blendMode,
		_blendFactor,
		_wrapMode
		} );

	textures.push_back( newTexture );
}

void Mesh::setShader( const unsigned int _shader ) {
	m_shader = _shader;
}