#include "gamelogic.h"



GameLogic::GameLogic( GameSettings _settings )
    :m_settings(_settings)
{
    if (m_settings.CAM_MODE == Camera_Mode::FREE_FLOAT) {
        m_camera = new Camera_FreeFloat( glm::vec3( 0.0f, 3.0f, 3.0f ) );
    }
    else {
        m_player = addShip(
                // position
            glm::vec3( 0.0f, 0.0f, 0.0f ),
            //scale
            glm::vec3( 0.1f ),
            //rotation
            glm::vec3( 0.0f, 0.0f, 0.0f )
        );

        m_camera = new Camera_Isometric( m_player );
    }

    m_scene = new Scene( _settings );
    m_scene->setCamera( m_camera );
}

void GameLogic::tick( float _deltaTime, float _lastFrame ) {

    m_scene->update( _deltaTime, _lastFrame );
}

Entity* GameLogic::getPlayer() {
    return m_player;
}

void GameLogic::setupGame() {
        // add ship test model
    Entity* newEntity = new Entity ( {
            glm::vec3( 0.0f, 0.0f, 0.0f ),
            glm::vec3( 15.0f ),
            glm::vec3( 0.0f )
        } );
    Entity* newEntity1 = new Entity ( {
            glm::vec3( 3.0f, 0.5f, 0.0f ),
            glm::vec3( 1.0f ),
            glm::vec3( 0.0f, 45.0f, 0.0f )
        } );
    Entity* newEntity2 = new Entity ( {
            glm::vec3( -3.0f, 0.5f, 0.0f ),
            glm::vec3( 1.0f ),
            glm::vec3( 0.0f )
        } );
    Entity* newEntity3 = new Entity ( {
            glm::vec3( 0.0f, 0.5f, -3.0f ),
            glm::vec3( 1.0f ),
            glm::vec3( 0.0f )
        } );
    Entity* newEntity4 = new Entity ( {
        glm::vec3( 0.0f, 1.0f, 0.0f ),
        glm::vec3( 0.5f ),
        glm::vec3( 0.0f )
        } );
        Entity* newEntity5 = new Entity ( {
        glm::vec3( 4.0f, 1.0f, 0.0f ),
        glm::vec3( 0.5f ),
        glm::vec3( 0.0f )
        } );    Entity* newEntity6 = new Entity ( {
        glm::vec3( -4.0f, 1.0f, 0.0f ),
        glm::vec3( 0.5f ),
        glm::vec3( 0.0f )
        } );    Entity* newEntity7 = new Entity ( {
        glm::vec3( 0.0f, 1.0f, 4.0f ),
        glm::vec3( 0.5f ),
        glm::vec3( 0.0f )
        } );    Entity* newEntity8 = new Entity ( {
        glm::vec3( 0.0f, 1.0f, -4.0f ),
        glm::vec3( 0.5f ),
        glm::vec3( 0.0f )
        } );
        Entity* newEntity9 = new Entity ( {
        glm::vec3( 4.0f, 1.0f, -4.0f ),
        glm::vec3( 0.5f ),
        glm::vec3( 0.0f )
        } );

    // set scene lights
    //m_scene->setDirLight( glm::vec3( 0.1f, -1.0f, 0.1f ), glm::vec3( 1.0f ) );

    //glm::vec3 pLightCol( 1.0f, 0.0f, 3.0f );
    //glm::vec3 pLightCol1( 0.0f, 0.0f, 1.0f );
    //glm::vec3 pLightCol2( 0.0f, 1.0f, 1.0f );
    //glm::vec3 pLightCol3( 1.0f, 0.0f, 1.0f );
    //glm::vec3 pLightCol4( 0.0f, 1.0f, 0.0f );
    //glm::vec3 pLightCol5( 0.0f, 1.0f, 1.0f );
    //m_scene->entities["lightCube"].push_back(newEntity4);
    //m_scene->addPointLight( newEntity4, glm::vec3( 0.0f ), pLightCol, 1.0f, 0.027, 0.0028 );
    //m_scene->entities["lightCube"].push_back(newEntity5);
    //m_scene->addPointLight( newEntity5, glm::vec3( 0.0f ), pLightCol1, 1.0f, 0.027, 0.0028 );
    //m_scene->entities["lightCube"].push_back(newEntity6);
    //m_scene->addPointLight( newEntity6, glm::vec3( 0.0f ), pLightCol2, 1.0f, 0.027, 0.0028 );
    //m_scene->entities["lightCube"].push_back(newEntity7);
    //m_scene->addPointLight( newEntity7, glm::vec3( 0.0f ), pLightCol3, 1.0f, 0.027, 0.0028 );
    //m_scene->entities["lightCube"].push_back(newEntity8);
    //m_scene->addPointLight( newEntity8, glm::vec3( 0.0f ), pLightCol4, 1.0f, 0.027, 0.0028 );
    ////m_scene->entities["lightCube"].push_back(newEntity9);
    ////m_scene->addPointLight( newEntity9, glm::vec3( 0.0f ), pLightCol5, 1.0f, 0.027, 0.0028 );

    ////m_entities["ship"].push_back( newEntity );
    ////m_entities["ship"].push_back( newEntity1 );
    ////m_entities["smb"].push_back( newEntity3 );
    //m_scene->entities["testCube"].push_back( newEntity3 );
    //m_scene->entities["testCube"].push_back(newEntity1);
    //m_scene->entities["testCube"].push_back(newEntity2);
    //m_scene->entities["floor"].push_back(newEntity);
    //m_entities["budda"].push_back( newEntity4 );

    std::vector<const char*> skyboxPaths =
    {
        "ressources/skybox/day_water/right.jpg",
        "ressources/skybox/day_water/left.jpg",
        "ressources/skybox/day_water/top.jpg",
        "ressources/skybox/day_water/bottom.jpg",
        "ressources/skybox/day_water/front.jpg",
        "ressources/skybox/day_water/back.jpg"
    };
    m_scene->setSkybox( skyboxPaths );

    //addShip(
    //    // position
    //    glm::vec3( 0.0f, 0.0f, 0.0f ),
    //    //scale
    //    glm::vec3( 0.1f ),
    //    //rotation
    //    glm::vec3( 0.0f, 0.0f, 0.0f )
    //);

    m_scene->update( 0.0f, 0.0f );
}

void GameLogic::restartGame() {

}

Camera* GameLogic::getCamera() {
    return m_camera;
}

Scene& GameLogic::getScene() {
    return *m_scene;
}


void GameLogic::processKeyboard( PlayerAction _action, float _deltaTime ) {
    
    if (m_settings.CAM_MODE == Camera_Mode::FREE_FLOAT) {
        switch (_action) {
            case PlayerAction::FORWARD:
            {
                m_camera->ProcessKeyboard( PlayerAction::FORWARD, _deltaTime );
                break;
            }
            case PlayerAction::BACKWARD:
            {
                m_camera->ProcessKeyboard( PlayerAction::BACKWARD, _deltaTime );
                break;
            }
            case PlayerAction::LEFT:
            {
                m_camera->ProcessKeyboard( PlayerAction::LEFT, _deltaTime );
                break;
            }
            case PlayerAction::RIGHT:
            {
                m_camera->ProcessKeyboard( PlayerAction::RIGHT, _deltaTime );
                break;
            }
        }
    }
    else {

    }

}

// debuggin
void GameLogic::fillImGui() {
    //ImGui::Text( "" );
    //ImGui::Text( "Collision Testing" );
    //ImGui::Text( "Ship 1" );
    //ImGui::SliderFloat3( "Position1", &testShip1->Position.x, -5.0f, 5.0f);
    //ImGui::SliderFloat3( "Rotation1", &testShip1->Rotation.x, -180.0f, 180.0f);
    //ImGui::SliderFloat3( "Scale1", &testShip1->Scale.x, 0.1f, 5.0f);
    //ImGui::Text( "Ship 2" );
    //ImGui::SliderFloat3( "Position2", &testShip2->Position.x, -5.0f, 5.0f);
    //ImGui::SliderFloat3( "Rotation2", &testShip2->Rotation.x, -180.0f, 180.0f);
    //ImGui::SliderFloat3( "Scale2", &testShip2->Scale.x, 0.1f, 5.0f);
}

// entity management
Entity* GameLogic::addEntity( glm::vec3 _position, glm::vec3 _scale, glm::vec3 _rotation, std::string _modelName ) {

    Entity* newEntity = new Entity {
        // position
        _position,
        //scale
        _scale,
        //rotation
        _rotation,
    };

    m_scene->entities[_modelName].push_back( newEntity );

    return newEntity;
}

Entity* GameLogic::addRock( glm::vec3 _position, glm::vec3 _scale, glm::vec3 _rotation ) {
    Entity* entityPtr = addEntity( _position, _scale, _rotation, "rock" );
    return entityPtr;
}

Entity* GameLogic::addCannonball( glm::vec3 _position, glm::vec3 _scale, glm::vec3 _rotation ) {
    Entity* entityPtr = addEntity( _position, _scale, _rotation, "cannonball" );
    return entityPtr;
}

Entity* GameLogic::addCrate( glm::vec3 _position, glm::vec3 _scale, glm::vec3 _rotation ) {
    Entity* entityPtr = addEntity( _position, _scale, _rotation, "crate");
    return entityPtr;
}

Entity* GameLogic::addShip( glm::vec3 _position, glm::vec3 _scale, glm::vec3 _rotation ) {
    Entity* entityPtr = addEntity( _position, _scale, _rotation, "ship");
    return entityPtr;
}

Entity* GameLogic::addWater( glm::vec3 _position, glm::vec3 _scale, glm::vec3 _rotation ) {
    Entity* entityPtr = addEntity( _position, _scale, _rotation, "water");
    return entityPtr;
}