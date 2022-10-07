#include "application.h"



Application::Application(GameSettings _settings)
    : m_settings(_settings)
{

    setupWindow(m_settings.SCR_WIDTH, m_settings.SCR_HEIGHT);
    setupModels();
    m_gameLogic = new GameLogic( m_settings );
    m_renderer = new Renderer(m_settings);
}

bool Application::setupWindow(unsigned int _width, unsigned int _height)
{
    // glfw: initialize and configure
 // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // set 4 subsamples per pixel for MSAA
    glfwWindowHint( GLFW_SAMPLES, 4 );

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // enable debugger
    m_debugger = new glDebugger();

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(_width, _height, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);

    
    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return NULL;
    }

    // enable testing and MSAA
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_STENCIL_TEST );
    glEnable( GL_CULL_FACE );
    glEnable( GL_MULTISAMPLE );


    m_debugger->enableDebug();

    m_window = window;

    if (m_settings.ENABLE_POLYGONMODE) enablePolygonMode();


    return true;
}

bool Application::setupModels()
{
    Model cubeModel( true );
    Mesh cubeMesh = DataProvider::generateCubeMesh( 1.0f );
    cubeMesh.addTexture( Texture_2D( "ressources/crate/crate.png" ), 0 );
    cubeModel.addMesh( cubeMesh );
    cubeModel.finishModel();
    ModelManager::AddModel( "cube", cubeModel );

    Model testCubeModel( true );
    Mesh testCubeMesh = DataProvider::generateCubeMesh( 1.0f );
    unsigned int testCubeShader = RessourceManager::GetShader( "testStandard" );
    Shader::useShader( testCubeShader );
    Shader::setInt( testCubeShader, "material1.diffuse0", 0 );
    testCubeMesh.addTexture( Texture_2D( "ressources/crate/crate.png" ), 0 );
    Shader::setInt( testCubeShader, "material1.specular", 1 );
    testCubeMesh.addTexture( Texture_2D( "ressources/crate/crate_specular.png" ), 1 );
    Shader::useShader( 0 );
    testCubeMesh.setShader( testCubeShader );
    testCubeModel.addMesh( testCubeMesh );
    testCubeModel.finishModel();
    ModelManager::AddModel( "testCube", testCubeModel );

    Model floorModel( true );
    Mesh floorMesh = DataProvider::generatePlaneMesh( glm::vec3( -0.5f, 0.0f, -0.5f ), glm::vec3( 0.5f, 0.0f, -0.5f ), glm::vec3( 0.5f, 0.0f, 0.5f ), glm::vec3( -0.5f, 0.0f, 0.5f ), 1 );
    floorMesh.setShader( RessourceManager::GetShader( "testStandard" ));
    floorMesh.addTexture( Texture_2D( "ressources/crate/crate.png" ), 0 );
    floorMesh.addTexture( Texture_2D( "ressources/crate/crate_specular.png" ), 1 );
    floorModel.addMesh( floorMesh );
    floorModel.finishModel();
    ModelManager::AddModel( "floor", floorModel );

    Model lightCubeModel( true );
    Mesh lightCubeMesh = DataProvider::generateCubeMesh( 1.0f );
    lightCubeMesh.setShader( RessourceManager::GetShader( "light" ) );
    lightCubeModel.addMesh( lightCubeMesh );
    lightCubeModel.finishModel();
    ModelManager::AddModel( "lightCube", lightCubeModel );




    std::vector<std::pair<std::string, std::string>> modelList;
    //modelList.emplace_back( "ship", "ressources/ship/ship_2cannons.obj" );
    //modelList.emplace_back( "smb", "ressources/fireball/esfera.obj" );
    //modelList.emplace_back( "budda", "ressources/budda/Pizza.obj" );
    ModelManager::LoadModelList( modelList );



    return false;
}


bool Application::runApplication()
{
#ifndef NDEBUG

    // initialize imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 430");

#endif // !NDEBUG

    m_gameLogic->setupGame();

    while (!glfwWindowShouldClose(m_window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;


        // input
        // -----
        processInput(m_window);

        // update gamestate
        // ----------------
        m_gameLogic->tick( deltaTime, lastFrame);


        // reset everything
        // ---------------
        clearBufferBits();
        resetTesting();


        // imgui
#ifndef NDEBUG
        if (cursorEnabled == true)
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }
#endif // !NDEBUG

        // render the scene
        m_renderer->renderScene( m_gameLogic->getScene() );


        fillImGui();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    stopApplication();

    return true;
}

//bool Application::updateUniforms() {
//    updateCameraMatrices();
//
//    glBindBuffer( GL_UNIFORM_BUFFER, timeBuffer );
//    glBufferSubData( GL_UNIFORM_BUFFER, 0, sizeof( float ), &lastFrame );
//    glBindBuffer( GL_UNIFORM_BUFFER, 0 );
//
//        // uniform buffer for directional light
//    glBindBuffer( GL_UNIFORM_BUFFER, dirLightBuffer );
//
//    //set the directional light here, because it doesn't need to be updated every frame
//    glm::vec3 lightDirection = glm::vec3( 0.1f, -1.0f, 0.1f );
//    glm::vec3 ambientColor = glm::vec3( 0.2f );
//    glm::vec3 diffuseColor = glm::vec3( 0.2f );
//    glm::vec3 specularColor = glm::vec3( 1.0f );
//
//    glBufferSubData( GL_UNIFORM_BUFFER, 0, sizeof( glm::vec3 ), glm::value_ptr( lightDirection ) );
//    glBufferSubData( GL_UNIFORM_BUFFER, sizeof( glm::vec4 ), sizeof( glm::vec3 ), glm::value_ptr( ambientColor ) );
//    glBufferSubData( GL_UNIFORM_BUFFER, 2 * sizeof( glm::vec4 ), sizeof( glm::vec3 ), glm::value_ptr( diffuseColor ) );
//    glBufferSubData( GL_UNIFORM_BUFFER, 3 * sizeof( glm::vec4 ), sizeof( glm::vec3 ), glm::value_ptr( specularColor ) );
//    glBindBuffer( GL_UNIFORM_BUFFER, 0 );
//
//    // set the camera position
//    glBindBuffer( GL_UNIFORM_BUFFER, cameraBuffer );
//    glm::vec3 cameraPos = m_gameLogic->getCamera()->getPosition();
//    glBufferSubData( GL_UNIFORM_BUFFER, 0, sizeof( glm::vec3 ), &cameraPos );
//    glBindBuffer( GL_UNIFORM_BUFFER, 0 );
//
//    return true;
//}



bool Application::renderFrame() {

    // render scene
    // --------------

    //m_renderer->renderScene( entities, std::vector<std::string>{"skybox"});


    // render skybox
    // --------------
    //change depth function to LEQUAL, so the skybox doesn't z-fight with the clearcolor
    //glDepthFunc( GL_LEQUAL );
    //// change face culling to cull outer instead of inner faces
    //glCullFace( GL_FRONT );
    //m_renderer->renderEntities( "skybox", entities.at( "skybox" ) );
    //resetTesting();

    // render debugging options
    // --------------
    //if (m_settings.SHOW_NORMALS) {
    //    m_renderer->renderScene( entities, "showNormals", std::vector<ModelName>{ModelName::SKYBOX, ModelName::WATER} );
    //    m_renderer->renderEntities( ModelName::WATER, entities.at(ModelName::WATER), "waterNormals");
    //}

    //if (m_settings.SHOW_VERTICES) {
    //    m_renderer->renderScene( entities, "showVertices", std::vector<ModelName>{ModelName::SKYBOX, ModelName::WATER} );
    //}

    //if (m_settings.SHOW_COLLIDERS) {
    //    m_renderer->renderColliders( entities, m_gameLogic->getColliders(), std::vector<ModelName>{ModelName::SKYBOX, ModelName::WATER} );
    //};

    return false;
}

bool Application::SetUniforms() {
        //standard shader
        // --------------
    //unsigned int standardShader = m_renderer->getShaderID("standard");
    //Shader::useShader( standardShader );

    //// set material sampler slots
    //Shader::setInt( standardShader, "material1.diffuse", 0 );
    //Shader::setInt( standardShader, "material1.specular", 1 );
    //Shader::setFloat( standardShader, "material1.shininess", 16.0f );

    //Shader::useShader( 0 );

    ////water shader
    //// --------------
    //unsigned int waterShader = m_renderer->getShaderID("water");
    //Shader::useShader( waterShader );
    //Shader::setVec3( waterShader, "viewPos", m_gameLogic->getCamera()->getPosition() );
    //Shader::setInt( waterShader, "reflectionTexture", 0 );
    //Shader::setInt( waterShader, "refractionTexture", 1 );
    //Shader::setInt( waterShader, "dudvTexture", 2 );
    //Shader::useShader( 0 );

    ////post processing
    //// --------------
    //if (!m_settings.POSTPROCESSING_KERNEL.empty())         {
    //    unsigned int postprocessingShader = m_renderer->getShaderID( "postprocessing" );
    //    const std::vector<float> kernel = m_settings.POSTPROCESSING_KERNEL;
    //    Shader::useShader( postprocessingShader );
    //    Shader::setInt( postprocessingShader, "screenTexture", 0 );
    //    for (int i = 0; i < 9; i++) {
    //        std::string curKernel = "kernel[" + std::to_string( i ) + "]";
    //        Shader::setFloat( postprocessingShader, curKernel, kernel[i] );
    //    }
    //    Shader::useShader( 0 );
    //}


    return false;
}


void Application::fillImGui() {
        // imgui
#ifndef NDEBUG
        if (cursorEnabled == true)
        {
        ImVec2 windowSize = ImVec2( 50.0f, 50.0f );
        //ImGui::SetNextWindowSize( windowSize );

        ImGui::Begin("Debugging");
        ImGui::Text("Settings");
        ImGui::Checkbox( "Show Colliders", &m_settings.SHOW_COLLIDERS );
        ImGui::Checkbox( "Poligon Mode", &m_settings.ENABLE_POLYGONMODE );
        ImGui::Checkbox( "Show Normals", &m_settings.SHOW_NORMALS );
        ImGui::Checkbox( "Show Vertices", &m_settings.SHOW_VERTICES );

        m_gameLogic->fillImGui();
        ImGui::End();

            ImGui::Render();
            ImGui:ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
#endif // !NDEBUG

}

bool Application::stopApplication()
{
    // delete vaos, vbos & shaders
    //m_renderer->shutdownRenderer();

#ifndef NDEBUG
    // shutdown imgui if debugmode is enabled
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
#endif // !NDEBUG


    return false;
}





// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Application::processInput(GLFWwindow* _window)
{

    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);

    if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
        m_gameLogic->processKeyboard(PlayerAction::LEFT, deltaTime);

    if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
        m_gameLogic->processKeyboard(PlayerAction::RIGHT, deltaTime);
    if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
        m_gameLogic->processKeyboard(PlayerAction::FORWARD, deltaTime);

    if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
        m_gameLogic->processKeyboard(PlayerAction::BACKWARD, deltaTime);


    if (glfwGetKey( _window, GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS)
        m_gameLogic->getCamera()->Accelerated = true;

    if (glfwGetKey( _window, GLFW_KEY_LEFT_SHIFT ) == GLFW_RELEASE)
        m_gameLogic->getCamera()->Accelerated = false;

    if (glfwGetKey(_window, GLFW_KEY_TAB) == GLFW_PRESS && (lastFrame - lastCursorToggle) >= cursorToggleDelay)
    {
        lastCursorToggle = lastFrame;

        if (cursorEnabled == false)
        {
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            cursorEnabled = true;
        }
        else
        {
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            cursorEnabled = false;
        }
    }


}

void Application::process_resize(GLFWwindow* _window, int _width, int _height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, _width, _height);
}

void Application::process_mouse(GLFWwindow* _window, double _xpos, double _ypos)
{
    if (cursorEnabled == false)
    {
        if (firstMouse)
        {
            lastX = _xpos;
            lastY = _ypos;
            firstMouse = false;
        }

        float xoffset = _xpos - lastX;
        float yoffset = lastY - _ypos; // reversed since y-coordinates go from bottom to top

        lastX = _xpos;
        lastY = _ypos;

        m_gameLogic->getCamera()->ProcessMouseMovement(xoffset, yoffset);
    }
}

void Application::process_scroll(GLFWwindow* _window, double _xoffset, double _yoffset)
{
    m_gameLogic->getCamera()->ProcessMouseScroll(_yoffset);
}

bool Application::clearBufferBits() {
    glClearColor( 1.0f, 0.0f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

    return false;
}

bool Application::resetTesting() {
    // enable testing
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_STENCIL_TEST );
    glEnable( GL_CULL_FACE );

    // reset depth test
    glDepthFunc( GL_LESS );
    glDepthMask( GL_TRUE );

    // reset face culling
    glFrontFace( GL_CCW );
    glCullFace( GL_BACK );

    return false;
}

bool Application::setClippingPlane( glm::vec4 _clippingPlane ) {
    glBindBuffer( GL_UNIFORM_BUFFER, clippingPlaneBuffer );
    glBufferSubData( GL_UNIFORM_BUFFER, 0, sizeof( glm::vec4 ), glm::value_ptr( _clippingPlane ) );
    glBindBuffer( GL_UNIFORM_BUFFER, 0 );
    return false;
}




void Application
::enablePolygonMode()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

