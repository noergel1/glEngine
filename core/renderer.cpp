#include "renderer.h"


	Renderer::Renderer(GameSettings _settings)
		:m_settings(_settings)
	{
	}

	void Renderer::renderScene( Scene& _scene )
	{
		std::vector<Mesh> meshes;

		// set instancing buffers
		for (const auto& modelEntities : _scene.entities) {
			std::vector<glm::mat4> modelMatrices;
			modelMatrices.reserve( modelEntities.second.size() );

			for ( const auto& entity : modelEntities.second) {
				modelMatrices.push_back(createSRTMat4( *entity ));
			}

			Model curModel = ModelManager::GetModel( modelEntities.first );
			curModel.setInstances( modelMatrices );
			std::vector<Mesh> modelMeshes = curModel.getMeshes();
			meshes.insert(meshes.end(), modelMeshes.begin(), modelMeshes.end());
		}

		// sort meshes
		// -----------------------

		// draw meshes
		// -----------------------
		unsigned int curShader = 0;
		for (auto mesh : meshes) {
			if (curShader != mesh.m_shader) {
				curShader = mesh.m_shader;
				Shader::useShader( curShader );
			}
			mesh.bindVao();
			mesh.bindTextures();

			glDrawElementsInstanced( GL_TRIANGLES, mesh.indiceCount, GL_UNSIGNED_INT, 0, mesh.entityCount );

		}




		// render skybox
		glDepthFunc( GL_LEQUAL );
		glCullFace( GL_FRONT );
		Shader::useShader( _scene.skybox.m_shader );
		_scene.skybox.bindVao();
		_scene.skybox.bindTextures();
		glDrawElements( GL_TRIANGLES, _scene.skybox.indiceCount, GL_UNSIGNED_INT, 0 );

	}

	
	void Renderer::renderColliders( const std::map<std::string, std::vector<Entity*>> _entities, std::map<std::string, ModelCollider> _modelColliders, std::vector<std::string> _exclude ) {
		//const unsigned int modelShader = m_shaders["showColliders"];
		const unsigned int modelShader = 0;

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		// go through all key/value pairs in the _entities map
		for (auto const& _entityVector : _entities) {

			const std::string modelName = _entityVector.first;

			// skip the models which are to be excluded
			if (std::find( _exclude.begin(), _exclude.end(), modelName ) != _exclude.end()) {
				continue;
			}

			std::vector<Entity*> entities = _entityVector.second;

			// skip if the model has no collider
			if (_modelColliders.find(modelName) == _modelColliders.end()) continue;

			ColliderType curColliderType = _modelColliders[modelName].colliderType;
			ColliderData curCollider = m_colliders[curColliderType];
			Entity colliderTransform = _modelColliders[modelName].diffToModel;

			// bind vao
			BindVao( curCollider.vao );

			// get data
			const unsigned int indiceCount = curCollider.indiceCount;


			// render
			//----------

			// activate shader
			Shader::useShader( modelShader );

			for (int i = 0; i < entities.size(); i++) {
				// collider matrix
				glm::mat4 colliderMat = createSRTMat4( colliderTransform );

				// model matrix
				glm::mat4 modelMat = createSRTMat4( *entities[i]);

				Shader::setMat4( modelShader, "model[" + std::to_string(i) + "]", modelMat * colliderMat);
			}

			glDrawElementsInstanced( GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, 0, entities.size() );
		}

		if(!m_settings.ENABLE_POLYGONMODE) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		Shader::useShader( 0 );
	}

	void Renderer::modelRender( const Entity* _entity, unsigned int _shader, unsigned int _indiceCount )
	{

		glm::mat4 model = createSRTMat4( *_entity );



		Shader::setMat4( _shader, "model", model );


		// draw
		glDrawElements(GL_TRIANGLES, _indiceCount, GL_UNSIGNED_INT, 0);
	}

	bool Renderer::shutdownRenderer()
	{

		// free all VAOS
		std::vector<unsigned int> deletedVaos;
		//for (auto const& model : m_models)
		//{
		//	const ModelData* modelData = model.second;

		//	if (modelData == NULL) continue;

		//	unsigned int modelVao = modelData->m_VAO;
		//	if (std::find(deletedVaos.begin(), deletedVaos.end(), modelVao) != deletedVaos.end())
		//	{
		//		// VAO already in deletedVaos
		//		continue;
		//	}
		//	else
		//	{
		//		deletedVaos.push_back(modelVao);
		//	}
		//}

		// should also free all VBOs aswell

		/////////
		////////
		///////



		// delete all the VAOs at once
		glDeleteVertexArrays(deletedVaos.size(), &deletedVaos[0]);



		// free all shaders
		/*for (auto const& shader : m_shaders)
		{
			unsigned int shaderId = shader.second;
			glDeleteProgram(shaderId);
		}*/

		return false;
	};


	bool Renderer::BindVao(unsigned int _vao)
	{
		glBindVertexArray(_vao);

		return true;
	}

	void Renderer::AddColliderVao( ColliderType _colliderType, unsigned int _vao, unsigned int _indiceCount ) {
		ColliderData colliderData = ColliderData( {
				_vao,
				_indiceCount
			} );

		m_colliders[_colliderType] = colliderData;
	}
