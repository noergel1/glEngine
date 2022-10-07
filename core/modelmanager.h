#pragma once

#include <string>

#include "ressourcemanager.h"
#include "../utils/model.h"
#include "../utils/modelloader.h"


class ModelManager {

public:
	ModelManager( const ModelManager& ) = delete;
	ModelManager& operator=(ModelManager& other) = delete;


public:
	static ModelManager& Get() {
		static ModelManager m_Instance;
		return m_Instance;
	}

	static Model& GetModel( std::string _modelName ) {
		return Get().IGetModel( _modelName );
	}


	static void SetModelInstancing( std::string _modelTitle, const std::vector<glm::mat4>& _instances ) {
		return Get().ISetModelInstancing( _modelTitle, _instances );
	}

	static void AddModel( std::string _modelName, Model _model ) {
		return Get().IAddModel( _modelName, _model );
	}

	// first value of pair is the models' title, second is the obj path
	static void LoadModelList( const std::vector<std::pair<std::string, std::string>>& _modelList ) {
		return Get().ILoadModelList(_modelList);
	}

private:
	ModelManager();

	Model& IGetModel( std::string _modelName );

	void ILoadModelList( const std::vector<std::pair<std::string, std::string>>& _modelList );

	void IAddModel( std::string _modelName, Model _model );

	void ISetModelInstancing( std::string _modelTitle, const std::vector<glm::mat4>& _instances );

private:
	std::map<std::string, Model> m_models;

private:

};