#pragma once
#include <unordered_map>
#include <map>
#include <string>

#include <boost/filesystem/directory.hpp>
#include <boost/regex.hpp>

#include "../utils/shader.h"
#include "../utils/texture.h"
#include "../utils/texture_2d.h"

#define DIFFUSEMAP0_TEXTURESLOT 0
#define DIFFUSEMAP1_TEXTURESLOT 1
#define DIFFUSEMAP2_TEXTURESLOT 2
#define DIFFUSEMAP3_TEXTURESLOT 3
#define DIFFUSEMAP4_TEXTURESLOT 4
#define DIFFUSEMAP5_TEXTURESLOT 5
#define DIFFUSEMAP6_TEXTURESLOT 6
#define SPECULARMAP_TEXTURESLOT 7
#define AMBIENTMAP_TEXTURESLOT 8
#define EMISSIVEMAP_TEXTURESLOT 9
#define HEIGHTMAP_TEXTURESLOT 10
#define NORMALMAP_TEXTURESLOT 11

class RessourceManager {

public:
	RessourceManager( const RessourceManager& ) = delete;
	RessourceManager& operator=(RessourceManager& other) = delete;


public:
	static RessourceManager& Get() {
		static RessourceManager m_Instance;
		return m_Instance;
	}

	static const unsigned int GetShader( unsigned int _diffuseCount, bool _specular = false, bool _ambient = false, bool _emissive = false, bool _height = false, bool _normal = false, unsigned int _vertexformat = 1 ) {
		return Get().IGetShader(_diffuseCount, _specular, _ambient, _emissive, _height, _normal, _vertexformat);
	}

	static const unsigned int GetShader(std::string _title) {
		return Get().IGetShader(_title);
	}

	static const Texture& GetTexture( std::string _path ) {
		return Get().IGetTexture( _path );
	}

private:
	RessourceManager();

	//	Standard shader name is concatenated like this:
	// Vertexformat		+ e.g. 6_
	//	N diffuse maps	+ ND_
	//	specular map	+ S_
	//	ambient map		+ A_
	//	emissive map	+ E_
	//	height map		+ H_
	//	normal map		+ N_
	//	
	//	Example 2 diffuse + specular + height + emissive
	//	Result:	6_2D_S_H_E_ (.glsl)

	
	// looks up if a standard shader with the given attributes exists, if not generates it
	const unsigned int IGetShader( unsigned int _diffuseCount, bool _specular, bool _ambient, bool _emissive, bool _height, bool _normal, unsigned int _vertexformat);

	// gets the shader by name. Either a standard shader or custom
	const unsigned int IGetShader( std::string _title );

	const Texture& IGetTexture( std::string _path );

private:
	const unsigned int generateShader( const unsigned int _diffuseCount, const bool _specular, const bool _ambient, const bool _emissive, const bool _height, const bool _normal, const unsigned int _vertexFormat );
	const unsigned int compileShader(std::string _vsCode, std::string _fsCode, std::string _gsCode = "");
	const unsigned int compileShader(std::string _computeCode );
	void setStandardShaderUniforms( const unsigned int _shader, const unsigned int _diffuseCount, const bool _specular, const bool _ambient, const bool _emissive, const bool _height, const bool _normal );
	void loadCustomShaders();
	void loadComputeShaders();
	static void checkCompileErrors( GLuint shader, std::string type );

	std::string getFileContent( std::string _filepath );

private:
	std::unordered_map<std::string, const unsigned int> m_shaders;
	std::unordered_map<std::string, Texture_2D> m_textures;

	const std::string m_standardShaderPath = "shader/standard";
	const std::string m_customShaderPath = "shader/custom/";
	const std::string m_vsFileConvention = ".vert";
	const std::string m_fsFileConvention = ".frag";
	const std::string m_gsFileConvention = "GS.glsl";
	// contains the code of the standard shader, obtained in constructor
	const std::string m_vsStandardShaderCode;
	const std::string m_fsStandardShaderCode;

};