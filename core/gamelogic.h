#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "../utils/imgui/imgui.h"

#include "../utils/definitions.h"
#include "../utils/cooldown.h"
#include "../utils/camera_freefloat.h"
#include "../utils/camera_isometric.h"
#include "gamesettings.h"
#include "../utils/dataprovider.h"
#include "../utils/collision_detection.h"
#include "scene.h"

#include <map>
#include <functional>

const float waterHeight = 0.0f;



class GameLogic {
public:
	GameLogic( GameSettings _settings );

	void tick( float _deltaTime, float _lastFrame );

	void setupGame();
	void restartGame();

	Camera* getCamera();
	Entity* getPlayer();
	Scene& getScene();
	const std::map<std::string, ModelCollider>& getColliders() const;

	void processKeyboard( PlayerAction _action, float _deltaTime );


private:
	Camera* m_camera;
	GameSettings m_settings;

	Scene* m_scene;

	//player
private:
	Entity* m_player;										// pointer to the player entity

	// entity management
	// -------------
	Entity* addEntity( glm::vec3 _position, glm::vec3 _scale, glm::vec3 _rotation, std::string _modelName );
		  
	Entity* addRock( glm::vec3 _position, glm::vec3 _scale = glm::vec3( 1.0f, 1.0f, 1.0f ), glm::vec3 _rotation = glm::vec3( 0.0f, 0.0f, 0.0f ) );
	Entity* addCannonball( glm::vec3 _position, glm::vec3 _scale = glm::vec3( 1.0f, 1.0f, 1.0f ), glm::vec3 _rotation = glm::vec3( 0.0f, 0.0f, 0.0f ) );
	Entity* addCrate( glm::vec3 _position, glm::vec3 _scale = glm::vec3( 1.0f, 1.0f, 1.0f ), glm::vec3 _rotation = glm::vec3( 0.0f, 0.0f, 0.0f ) );
	Entity* addShip( glm::vec3 _position, glm::vec3 _scale = glm::vec3( 1.0f, 1.0f, 1.0f ), glm::vec3 _rotation = glm::vec3( 0.0f, 0.0f, 0.0f ) );
	Entity* addWater( glm::vec3 _position, glm::vec3 _scale = glm::vec3( 1.0f, 1.0f, 1.0f ), glm::vec3 _rotation = glm::vec3( 0.0f, 0.0f, 0.0f ) );

	// ship collider
	float shipCapsuleRadius = 1.1f;
	float shipCapsuleLength = 6.3f;

//debugging
public:
	void fillImGui();
};