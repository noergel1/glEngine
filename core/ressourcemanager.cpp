#include "ressourcemanager.h"

RessourceManager::RessourceManager() 
	:m_vsStandardShaderCode(getFileContent(m_standardShaderPath + m_vsFileConvention))
	,m_fsStandardShaderCode(getFileContent(m_standardShaderPath + m_fsFileConvention))
{
	// load some needed standard shader variants

	// compile custom shaders
	loadCustomShaders();
	loadComputeShaders();

	// load models

}

	const unsigned int RessourceManager::IGetShader( unsigned int _diffuseCount, bool _specular = false, bool _ambient = false, bool _emissive = false, bool _height = false, bool _normal = false, unsigned int _vertexFormat = 1 ) {

		//#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))
		//std::cout << CHECK_BIT( 15, 0 ) << "\n";
		//std::cout << CHECK_BIT( 15, 1 ) << "\n";
		//std::cout << CHECK_BIT( 15, 2 ) << "\n";
		//std::cout << CHECK_BIT( 15, 3 ) << "\n";

		// create look-up string
		std::string shaderStr = "";
		shaderStr += std::to_string( _vertexFormat ) + "_";
		if (_diffuseCount > 0) shaderStr += std::to_string(_diffuseCount) + "D_";
		else {
			std::cout << "Tried creating shader without diffuse maps!\n";
		}
		if (_specular) shaderStr += "S_";
		if (_ambient) shaderStr += "A_";
		if (_emissive) shaderStr += "E_";
		if (_height) shaderStr += "H_";
		if (_normal) shaderStr += "N_";

		// check if shader already exists, otherwhise compile it
		if (m_shaders.count(shaderStr)) {
			return m_shaders.at( shaderStr );
		}
		else {
			const unsigned int newShader = generateShader( _diffuseCount, _specular, _ambient, _emissive, _height, _normal, _vertexFormat );

			//set sampler texture slots
			setStandardShaderUniforms( newShader, _diffuseCount, _specular, _ambient, _emissive, _height, _normal );

			m_shaders.insert( std::pair<const std::string, const unsigned int>( shaderStr, newShader ) );
			return newShader;
		}
	};

	const unsigned int RessourceManager::generateShader(  const unsigned int _diffuseCount, const bool _specular, const bool _ambient, const bool _emissive, const bool _height, const bool _normal, const unsigned int _vertexFormat ) {
		
		std::string shaderName = "";
		std::string vsAppend = "";
		std::string fsAppend = "";
		std::string glslVersion = "#version 430 core\n";
		unsigned int curTextureSlot = 0;

		// generate the defines to append to the shader code
		vsAppend += glslVersion;
		vsAppend += "#define VERTEXFORMAT " + std::to_string( _vertexFormat ) + "\n";

		fsAppend += glslVersion;
		fsAppend += "#define VERTEXFORMAT " + std::to_string( _vertexFormat ) + "\n";
		for (int i = 1; i < _diffuseCount; i++) {
			fsAppend += "#define DIFFUSEMAP_" + std::to_string( i ) + " " + std::to_string( 1 ) + "\n";
			curTextureSlot++;
		};

		if (_specular) {
			fsAppend += "#define SPECULARMAP " + std::to_string( 1 ) + "\n";
			curTextureSlot++;
		};

		if (_ambient) {
			fsAppend += "#define AMBIENTMAP " + std::to_string( 1 ) + "\n";
			curTextureSlot++;
		};

		if (_emissive) {
			fsAppend += "#define EMISSIVEMAP " + std::to_string( 1 ) + "\n";
			curTextureSlot++;
		};

		if (_height) {
			fsAppend += "#define HEIGHTMAP " + std::to_string( 1 ) + "\n";
			curTextureSlot++;
		};

		if (_normal) {
			fsAppend += "#define NORMALMAP " + std::to_string( 1 ) + "\n";
			curTextureSlot++;
		};

		// get the standard shaders' code and append defines
		std::string vsCode = vsAppend + m_vsStandardShaderCode;
		std::string fsCode = fsAppend + m_fsStandardShaderCode;

		return compileShader( vsCode, fsCode );
	}

	const unsigned int RessourceManager::compileShader( std::string _vsCode, std::string _fsCode, std::string _gsCode ) {
		unsigned int shaderId = 0;
		bool hasGeometryShader = (_gsCode.compare( "" ) != 0);

        const char* vShaderCode = _vsCode.c_str();
        const char * fShaderCode = _fsCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // if geometry shader is given, compile geometry shader
        unsigned int geometry;
        if(hasGeometryShader)
        {
            const char * gShaderCode = _gsCode.c_str();
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &gShaderCode, NULL);
            glCompileShader(geometry);
            checkCompileErrors(geometry, "GEOMETRY");
        }
        // shader Program
        shaderId = glCreateProgram();
        glAttachShader(shaderId, vertex);
        glAttachShader(shaderId, fragment);
        if(hasGeometryShader)
            glAttachShader(shaderId, geometry);
        glLinkProgram(shaderId);
        checkCompileErrors(shaderId, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if(hasGeometryShader)
            glDeleteShader(geometry);

        return shaderId;
	}

	const unsigned int RessourceManager::compileShader( std::string _computeCode ) {
		 unsigned int shaderId = 0;
		 const char* computeCode = _computeCode.c_str();

        // 2. compile shader
        unsigned int compute;
        compute = glCreateShader(GL_COMPUTE_SHADER);
        glShaderSource(compute, 1, &computeCode, NULL);
        glCompileShader(compute);
        checkCompileErrors(compute, "COMPUTE");

        // shader Program
        shaderId = glCreateProgram();
        glAttachShader(shaderId, compute);
        glLinkProgram(shaderId);
        checkCompileErrors(shaderId, "PROGRAM");

        // delete the shader as they're linked into our program now and no longer necessery
        glDeleteShader(compute);

        return shaderId;
	}

	void RessourceManager::setStandardShaderUniforms( const unsigned int _shader, const unsigned int _diffuseCount, const bool _specular, const bool _ambient, const bool _emissive, const bool _height, const bool _normal ) {
		// TODO: check if binding shader is even necessary here
		Shader::useShader( _shader );
		
		for (int i = 0; i < _diffuseCount; i++) {
			Shader::setInt( _shader, "material1.diffuse" + std::to_string(i), i);
		}

		if (_specular) {
			Shader::setInt( _shader, "material1.specular", SPECULARMAP_TEXTURESLOT);
		}

		if (_ambient) {
			Shader::setInt( _shader, "material1.ambient", AMBIENTMAP_TEXTURESLOT);
		}

		if (_emissive) {
			Shader::setInt( _shader, "material1.emissive", EMISSIVEMAP_TEXTURESLOT);
		}

		if (_height) {
			Shader::setInt( _shader, "material1.height", HEIGHTMAP_TEXTURESLOT);
		}

		if (_normal) {
			Shader::setInt( _shader, "material1.normal", NORMALMAP_TEXTURESLOT);
		}

		Shader::useShader( 0 );

		return;
	}

	void RessourceManager::loadCustomShaders() {
		struct ShaderFiles {
			std::string vs = "";
			std::string fs = "";
			std::string gs = "";
		};

		boost::regex shaderRegex;
		std::map<const std::string, ShaderFiles> sortedShaderfiles;

		//new
		try {
			shaderRegex = boost::regex("shader\\\\custom\\\\\\w*(VS|FS|GS).glsl");
		}
		catch (const boost::regex_error err) {
			std::cout << err.what() << '\n';
			exit(1);
		};

		for (const auto& dir_entry : boost::filesystem::directory_iterator( "shader\\custom" )) {
			std::string shaderPath = dir_entry.path().string();
			if (!boost::regex_match( shaderPath, shaderRegex )) {
				std::cout << shaderPath << " didnt match regex" << '\n';
				continue;
			}

			std::string shaderTag = shaderPath.substr( shaderPath.length() - 7, 2 );
			std::string shaderTitle = shaderPath.substr(7, shaderPath.length() - 14);
			shaderTitle.replace( shaderTitle.begin(), shaderTitle.begin()+7, "");

			if (shaderTag == "VS") {
				sortedShaderfiles[shaderTitle].vs = getFileContent("shader\\custom\\" + shaderTitle + "VS.glsl");
			}
			else if (shaderTag == "FS") {
				sortedShaderfiles[shaderTitle].fs = getFileContent("shader\\custom\\" + shaderTitle + "FS.glsl");
			}
			else if (shaderTag == "GS") {
				sortedShaderfiles[shaderTitle].gs = getFileContent("shader\\custom\\" + shaderTitle + "GS.glsl");
			}
		}
		
		for (auto const& entry : sortedShaderfiles) {
			std::string shaderTitle = entry.first;
			ShaderFiles shaderFiles = entry.second;
			
			if (shaderFiles.vs.empty() || shaderFiles.fs.empty()) {
				std::cout << "Shader \"" + shaderTitle + "\" vs or fs missing \n";
				continue;
			}
			
			unsigned int shader;
			if (!shaderFiles.gs.empty()) {
				shader = compileShader(shaderFiles.vs, shaderFiles.fs, shaderFiles.gs);
			}
			else {
				shader = compileShader( shaderFiles.vs, shaderFiles.fs );
			}

			m_shaders.insert( std::pair<const std::string, const unsigned int>( shaderTitle, shader ) );

		}
	}

	void RessourceManager::loadComputeShaders() {
		boost::regex shaderRegex;
		std::vector<std::string> shaderContents;

		for (const auto& dir_entry : boost::filesystem::directory_iterator( "shader\\compute" )) {
			std::string shaderPath = dir_entry.path().string();

			std::string shaderTitle = "compute/" + shaderPath.substr( 15, shaderPath.length() - 20 );

			unsigned int shaderId = compileShader(getFileContent( shaderPath ));
			m_shaders.insert( std::pair<const std::string, const unsigned int>( shaderTitle, shaderId ) );
		}
	}

	std::string RessourceManager::getFileContent( std::string _filepath ) {
        std::ifstream file;
        // ensure ifstream objects can throw exceptions:
        file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try 
        {
            // open files
            file.open(_filepath);
            std::stringstream fileStream;
            // read file's buffer contents into streams
            fileStream << file.rdbuf();	
            // close file handlers
            file.close();
            // convert stream into string
            return fileStream.str();
        }
        catch (std::ifstream::failure& e)
        {
			std::cout << "ERROR IN RESSOURCEMANAGER\n";
			std::cout << "------------------------------------------------\n";
			std::cout << "File \"" << _filepath << "\" not found!\n";
			std::cout << "in function getFileContent\n\n";
        }
	}

	// supposed to be used for custom shaders
	const unsigned int RessourceManager::IGetShader( std::string _title ) {
		if (m_shaders.count(_title)) {
			return m_shaders.at( _title );
		}
		else {
			std::cout << "ERROR IN RESSOURCEMANAGER\n";
			std::cout << "------------------------------------------------\n";
			throw("Shader \"" + _title + "\" not found!\n");
			std::cout << "in function IGetShader\n\n";
		}
	};


	const Texture& RessourceManager::IGetTexture( std::string _path ) {
		if (m_textures.count( _path )) {
			return m_textures.at( _path );
		}
		else {
			const char* pathCStr = _path.c_str();
			Texture_2D newTexture = Texture_2D( pathCStr );
			m_textures[_path] = newTexture;

			return m_textures.at(_path);
		}
	}

	// utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void RessourceManager::checkCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        if(type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }