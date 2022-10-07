#pragma once

#include <map>
#include <vector>
#include <iostream>

#include "../utils/definitions.h"
#include "../utils/texture_cubemap.h"
#include "../utils/mesh.h"
#include "../utils/dataprovider.h"
#include "../utils/camera.h"

#define DIRLIGHT_UNIFORM_SLOT 2
#define POINTLIGHTS_UNIFORM_SLOT 5

#define MAX_POINTLIGHTS 6
#define POINTLIGHT_STRIDE 80

class Scene {
	struct DirLight {
		glm::vec3 direction = glm::vec3(0.0f);
		glm::vec3 color = glm::vec3(0.0f);
	};

	struct PointLight {
		Entity* parentObject = nullptr;
		glm::vec3 posRelativeToObject = glm::vec3(0.0f);

		glm::vec3 color = glm::vec3(0.0f);

		float constant = 0.0f;
		float linear = 0.0f;
		float quadratic = 0.0f;
	};

public:
	Scene(GameSettings _settings);
	void createBuffers();

	void update(float _deltaTime, float _lastFrame);
	void updateCameraMatrices();

	void setCamera( Camera* _camera );

	void setDirLight( glm::vec3 _direction, glm::vec3 _color );
	void addPointLight( Entity* _parentObj, glm::vec3 _posToParent, glm::vec3 _color, float _constant, float _linear, float _quadratic );
	void setLightsInShader();

	void setSkybox( std::vector<const char*> _skyboxPaths );

	void setClippingPlane( glm::vec4 _clippingPlane );

private:


public:

	std::map<std::string, std::vector<Entity*>> entities;
	Mesh skybox;

private:
	GameSettings m_settings;
	Camera* m_camera = nullptr;

	unsigned int m_dirLightBuffer;
	std::vector<PointLight> m_pointLights;

	unsigned int m_pointLightBuffer;
	DirLight m_dirLight;

	unsigned int m_timeBuffer;
	unsigned int m_clippingPlaneBuffer;
	unsigned int m_camPosBuffer;
	unsigned int m_viewProjectionBuffer;


};