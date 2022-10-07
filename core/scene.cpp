#include "scene.h"

Scene::Scene(GameSettings _settings) 
    :m_settings(_settings)
	,skybox(DataProvider::generateCubeMesh(1.0f))
{
    createBuffers();

    unsigned int skyboxShader = RessourceManager::GetShader( "skybox" );
    skybox.setShader( skyboxShader );
    Shader::useShader( skyboxShader );
    Shader::setInt( skyboxShader, "skybox", 0 );
}

void Scene::createBuffers() {
    // uniform buffer for directional light
    glGenBuffers( 1, &m_dirLightBuffer );
    glBindBuffer( GL_UNIFORM_BUFFER, m_dirLightBuffer );
    glBufferData( GL_UNIFORM_BUFFER, 4*16, NULL, GL_STATIC_DRAW);
    glBindBufferRange( GL_UNIFORM_BUFFER, DIRLIGHT_UNIFORM_SLOT, m_dirLightBuffer, 0, 4 * sizeof( glm::vec4 ) );
    glBindBuffer( GL_UNIFORM_BUFFER, 0 );

    // uniform buffer for point lights
    glGenBuffers( 1, &m_pointLightBuffer );
    glBindBuffer( GL_UNIFORM_BUFFER, m_pointLightBuffer );
    glBufferData( GL_UNIFORM_BUFFER, MAX_POINTLIGHTS * POINTLIGHT_STRIDE + 4, NULL, GL_STATIC_DRAW);
    //glBindBufferRange( GL_UNIFORM_BUFFER, POINTLIGHTS_UNIFORM_SLOT, m_pointLightBuffer, 0, MAX_POINTLIGHTS * POINTLIGHT_STRIDE + 4 );
    glBindBufferBase( GL_UNIFORM_BUFFER, POINTLIGHTS_UNIFORM_SLOT, m_pointLightBuffer);
    glBindBuffer( GL_UNIFORM_BUFFER, 0 );

        // uniform buffer for view and projection matrix
    glGenBuffers( 1, &m_viewProjectionBuffer );
    glBindBuffer( GL_UNIFORM_BUFFER, m_viewProjectionBuffer );
    glBufferData( GL_UNIFORM_BUFFER, 2 * sizeof( glm::mat4 ), NULL, GL_STATIC_DRAW );
    glBindBufferRange( GL_UNIFORM_BUFFER, 0, m_viewProjectionBuffer, 0, 2 * sizeof( glm::mat4 ) );
    glBindBuffer( GL_UNIFORM_BUFFER, 0 );

    // uniform buffer for time
    glGenBuffers( 1, &m_timeBuffer );
    glBindBuffer( GL_UNIFORM_BUFFER, m_timeBuffer );
    glBufferData( GL_UNIFORM_BUFFER, sizeof(float), NULL, GL_STATIC_DRAW );
    glBindBufferRange( GL_UNIFORM_BUFFER, 1, m_timeBuffer, 0, sizeof( float ) );
    glBindBuffer( GL_UNIFORM_BUFFER, 0 );

    // uniform buffer for clipping plane
    glEnable( GL_CLIP_DISTANCE0 );
    glGenBuffers( 1, &m_clippingPlaneBuffer );
    glBindBuffer( GL_UNIFORM_BUFFER, m_clippingPlaneBuffer );
    glBufferData( GL_UNIFORM_BUFFER, sizeof( glm::vec4 ), NULL, GL_STATIC_DRAW);
    glBindBufferRange( GL_UNIFORM_BUFFER, 3, m_clippingPlaneBuffer, 0, sizeof( glm::vec4 ) );
    setClippingPlane( glm::vec4( 0.0f, 0.0f, 0.0f, 0.0f ) );
    glBindBuffer( GL_UNIFORM_BUFFER, 0 );

    // uniform buffer for camera
    glEnable( GL_CLIP_DISTANCE0 );
    glGenBuffers( 1, &m_camPosBuffer );
    glBindBuffer( GL_UNIFORM_BUFFER, m_camPosBuffer );
    glBufferData( GL_UNIFORM_BUFFER, sizeof( glm::vec4 ), NULL, GL_STATIC_DRAW );
    glBindBufferRange( GL_UNIFORM_BUFFER, 4, m_camPosBuffer, 0, sizeof( glm::vec3 ) );
    glBindBuffer( GL_UNIFORM_BUFFER, 0 );
}

void Scene::update(float _deltaTime, float _lastFrame) {
    updateCameraMatrices();

    glBindBuffer( GL_UNIFORM_BUFFER, m_timeBuffer );
    glBufferSubData( GL_UNIFORM_BUFFER, 0, sizeof( float ), &_lastFrame );
    glBindBuffer( GL_UNIFORM_BUFFER, 0 );

    // set the camera position
    glBindBuffer( GL_UNIFORM_BUFFER, m_camPosBuffer );
    glm::vec3 cameraPos = m_camera->getPosition();
    glBufferSubData( GL_UNIFORM_BUFFER, 0, sizeof( glm::vec3 ), &cameraPos );
    glBindBuffer( GL_UNIFORM_BUFFER, 0 );
}

void Scene::updateCameraMatrices() {
        // update matrices
    glm::mat4 view = m_camera->GetViewMatrix();
    glm::mat4 projection = glm::perspective( glm::radians( m_camera->getZoom() ), (float)m_settings.SCR_WIDTH / (float)m_settings.SCR_HEIGHT, 0.1f, 100.0f );

    glBindBuffer( GL_UNIFORM_BUFFER, m_viewProjectionBuffer );
    glBufferSubData( GL_UNIFORM_BUFFER, 0, sizeof( glm::mat4 ), glm::value_ptr( projection ) );
    glBufferSubData( GL_UNIFORM_BUFFER, sizeof( glm::mat4 ), sizeof( glm::mat4 ), glm::value_ptr( view ) );
    glBindBuffer( GL_UNIFORM_BUFFER, 0 );
}

void Scene::setCamera( Camera* _camera ) {
    m_camera = _camera;
}

void Scene::setDirLight( glm::vec3 _direction, glm::vec3 _color ) {
    m_dirLight.direction = _direction;
    m_dirLight.color = _color;

    setLightsInShader();
}

void Scene::addPointLight( Entity* _parentObj, glm::vec3 _posToParent, glm::vec3 _color, float _constant, float _linear, float _quadratic ) {
    PointLight newPointLight;
    newPointLight.parentObject = _parentObj;
    newPointLight.posRelativeToObject = _posToParent;
    newPointLight.color = _color;
    newPointLight.constant = _constant;
    newPointLight.linear = _linear;
    newPointLight.quadratic = _quadratic;

    m_pointLights.push_back( newPointLight );

    setLightsInShader();
}

void Scene::setLightsInShader() {
    // set directional light
    glBindBuffer( GL_UNIFORM_BUFFER, m_dirLightBuffer );

    glBufferSubData( GL_UNIFORM_BUFFER, 0, sizeof( glm::vec3 ), glm::value_ptr( m_dirLight.direction ) );
    glBufferSubData( GL_UNIFORM_BUFFER, sizeof( glm::vec4 ), sizeof( glm::vec3 ), glm::value_ptr( m_dirLight.color * 0.2f ) );
    glBufferSubData( GL_UNIFORM_BUFFER, 2 * sizeof( glm::vec4 ), sizeof( glm::vec3 ), glm::value_ptr( m_dirLight.color * 0.2f ) );
    glBufferSubData( GL_UNIFORM_BUFFER, 3 * sizeof( glm::vec4 ), sizeof( glm::vec3 ), glm::value_ptr( m_dirLight.color ) );

    glBindBuffer( GL_UNIFORM_BUFFER, 0 );

    // set point lights
    glBindBuffer( GL_UNIFORM_BUFFER, m_pointLightBuffer);

    unsigned int pointLightCount = m_pointLights.size();
    for (int i = 0; i < m_pointLights.size(); i++) {
        PointLight curLight = m_pointLights[i];
        glm::vec3 lightPos = curLight.parentObject->Position + curLight.posRelativeToObject;
        glm::vec3 ambLight = curLight.color * 0.2f;
        glm::vec3 diffLight = curLight.color * 0.2f;
        glm::vec3 specLight = curLight.color;


        glBufferSubData( GL_UNIFORM_BUFFER, i*POINTLIGHT_STRIDE,                                                sizeof( glm::vec3 ),    glm::value_ptr( lightPos ));
        glBufferSubData( GL_UNIFORM_BUFFER, i*POINTLIGHT_STRIDE + 1 * sizeof( glm::vec4 ),                      sizeof( glm::vec3 ),    glm::value_ptr( ambLight ) );
        glBufferSubData( GL_UNIFORM_BUFFER, i*POINTLIGHT_STRIDE + 2 * sizeof( glm::vec4 ),                      sizeof( glm::vec3 ),    glm::value_ptr( diffLight ) );
        glBufferSubData( GL_UNIFORM_BUFFER, i*POINTLIGHT_STRIDE + 3 * sizeof( glm::vec4 ),                      sizeof( glm::vec3 ),    glm::value_ptr( specLight ) );
        glBufferSubData( GL_UNIFORM_BUFFER, i*POINTLIGHT_STRIDE + 4 * sizeof( glm::vec4 ),                      sizeof( float ),        &curLight.constant);
        glBufferSubData( GL_UNIFORM_BUFFER, i*POINTLIGHT_STRIDE + 4 * sizeof( glm::vec4 ) + 1 * sizeof(float),  sizeof( float ),        &curLight.linear );
        glBufferSubData( GL_UNIFORM_BUFFER, i*POINTLIGHT_STRIDE + 4 * sizeof( glm::vec4 ) + 2 * sizeof(float),  sizeof( float ),        &curLight.quadratic );
    };
    glBufferSubData( GL_UNIFORM_BUFFER, MAX_POINTLIGHTS * POINTLIGHT_STRIDE, sizeof( float ), &pointLightCount );

    glBindBuffer( GL_UNIFORM_BUFFER, 0 );
}

void Scene::setSkybox( std::vector<const char*> _skyboxPaths ) {
	std::vector<const char*> skyboxPaths =
    {
        "ressources/skybox/day_water/right.jpg",
        "ressources/skybox/day_water/left.jpg",
        "ressources/skybox/day_water/top.jpg",
        "ressources/skybox/day_water/bottom.jpg",
        "ressources/skybox/day_water/front.jpg",
        "ressources/skybox/day_water/back.jpg"
    };
    Texture_CubeMap skyboxTexture = Texture_CubeMap( skyboxPaths );
    skybox.addTexture( skyboxTexture, 0 );
}

void Scene::setClippingPlane( glm::vec4 _clippingPlane ) {
    glBindBuffer( GL_UNIFORM_BUFFER, m_clippingPlaneBuffer );
    glBufferSubData( GL_UNIFORM_BUFFER, 0, sizeof( glm::vec4 ), glm::value_ptr( _clippingPlane ) );
    glBindBuffer( GL_UNIFORM_BUFFER, 0 );
}
