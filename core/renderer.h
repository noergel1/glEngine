#pragma once

#include <unordered_map>
#include <map>
#include <numeric>
#include <boost/regex.hpp>

#include "../utils/shader.h"
#include "../utils/definitions.h"
#include "../utils/camera.h"
#include "../utils/dataprovider.h"
#include "../utils/helpers.h"
#include "../utils/framebuffer.h"
#include "../utils/texture_cubemap.h"

#include "modelmanager.h"
#include "scene.h"

#include "../utils/model_data.h"



class Renderer {

	struct ColliderData {
		unsigned int vao;
		unsigned int indiceCount;
	};

public:

	Renderer(GameSettings _settings);
	bool shutdownRenderer();


	void renderScene( Scene& _scene );

	void renderColliders( const std::map<std::string, std::vector<Entity*>> _entities, std::map<std::string, ModelCollider> _modelColliders, std::vector<std::string> _exclude );

	void AddColliderVao( ColliderType _colliderType, unsigned int _vao, unsigned int _indiceCount );

	bool BindVao(unsigned int _vao);

private:
	void modelRender( const Entity* _entity, unsigned int _shader, unsigned int _indiceCount );

	GameSettings m_settings;

	// vaos for the different collider type
	std::map<ColliderType, ColliderData> m_colliders;

};
