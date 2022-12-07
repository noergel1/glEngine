#include "modelmanager.h"


ModelManager::ModelManager() {
	// TODO : add the error model
}

void ModelManager::IAddModel( std::string _modelName, Model _model ) {
	m_models.insert( std::make_pair( _modelName, _model ) );
}

Model& ModelManager::IGetModel( std::string _modelName ) {
	if (m_models.count( _modelName )) {
		return m_models.at( _modelName );
	}
	else {
		std::cout << "ERROR IN MODELMANAGER\n"
			<< "---------------------\n"
			<< "Model " << _modelName << " not found!\n";
		return m_models.at( "error" );
	}
}

void ModelManager::ILoadModelList( const std::vector<std::pair<std::string, std::string>>& _modelList) {
	for (auto pair : _modelList) {
		std::string modelTitle = pair.first;
		std::string modelPath = pair.second;

		Model newModel = ModelLoader::LoadModel( modelPath, true );

		m_models.insert( std::make_pair( modelTitle, newModel ) );
	}
}

void ModelManager::ISetModelInstancing( std::string _modelTitle, const std::vector<glm::mat4>& _instances ) {
}
