#include "dataprovider.h"


const std::string DataProvider::getShipObjPath()
{
    return "ressources/ship_2cannons.obj";
};

std::vector<float> DataProvider::noPostProcessing() {

    return std::vector<float>();
}

std::vector<float> DataProvider::getSharpenKernel()
{
    return std::vector<float>{
            2, 2, 2,
            2, -15, 2,
            2, 2, 2
    };
}
std::vector<float> DataProvider::getBlurKernel()
{
    return std::vector<float>{
        1.0 / 16, 2.0 / 16, 1.0 / 16,
            2.0 / 16, 4.0 / 16, 2.0 / 16,
            1.0 / 16, 2.0 / 16, 1.0 / 16
    };
}
std::vector<float> DataProvider::getEdgeDetectionKernel()
{
    return std::vector<float>{
        1, 1, 1,
            1, -8, 1,
            1, 1, 1
    };
};

const Mesh DataProvider::generateCubeMesh( float _a) {
    float halfSideLength = _a / 2;
    unsigned int floatPerVertex = 8;

    // positions
    glm::vec3 frontBottomLeft = glm::vec3( -halfSideLength, -halfSideLength, halfSideLength );
    glm::vec3 frontBottomRight = glm::vec3( halfSideLength, -halfSideLength, halfSideLength );
    glm::vec3 frontTopLeft = glm::vec3( -halfSideLength, halfSideLength, halfSideLength );
    glm::vec3 frontTopRight = glm::vec3( halfSideLength, halfSideLength, halfSideLength );
    glm::vec3 backBottomLeft = glm::vec3( -halfSideLength, -halfSideLength, -halfSideLength );
    glm::vec3 backBottomRight = glm::vec3( halfSideLength, -halfSideLength, -halfSideLength );
    glm::vec3 backTopLeft = glm::vec3( -halfSideLength, halfSideLength, -halfSideLength );
    glm::vec3 backTopRight = glm::vec3( halfSideLength, halfSideLength, -halfSideLength );

    // normals
    glm::vec3 front = glm::vec3( 0.0f, 0.0f, 1.0f );
    glm::vec3 back = glm::vec3( 0.0f, 0.0f, -1.0f );
    glm::vec3 left = glm::vec3( -1.0f, 0.0f, 0.0f );
    glm::vec3 right = glm::vec3( 1.0f, 0.0f, 0.0f );
    glm::vec3 up = glm::vec3( 0.0f, 1.0f, 0.0f );
    glm::vec3 down = glm::vec3( 0.0f, -1.0f, 0.0f );

    // texCoords
    glm::vec2 bottomLeft = glm::vec2( 0.0f, 0.0f );
    glm::vec2 bottomRight = glm::vec2( 1.0f, 0.0f );
    glm::vec2 topLeft = glm::vec2( 0.0f, 1.0f );
    glm::vec2 topRight = glm::vec2( 1.0f, 1.0f );

    std::vector<float> vertices;
    vertices.reserve( 24 * floatPerVertex );

    std::vector<unsigned int> indices;
    indices.reserve( 36 );

    vertices = {
    // position                  // normals                // texcoords
    -0.5f,   -0.5f,    0.5f,     0.0f,   0.0f,   1.0f,     1.0f,  0.0f,  
     0.5f,   -0.5f,    0.5f,     0.0f,   0.0f,   1.0f,     0.0f,  0.0f,  
     0.5f,    0.5f,    0.5f,     0.0f,   0.0f,   1.0f,     0.0f,  1.0f, 
    -0.5f,    0.5f,    0.5f,     0.0f,   0.0f,   1.0f,     1.0f,  1.0f,  
     0.5f,   -0.5f,   -0.5f,     0.0f,   0.0f,  -1.0f,     1.0f,  0.0f, 
    -0.5f,   -0.5f,   -0.5f,     0.0f,   0.0f,  -1.0f,     0.0f,  0.0f,  
    -0.5f,    0.5f,   -0.5f,     0.0f,   0.0f,  -1.0f,     0.0f,  1.0f,  
     0.5f,    0.5f,   -0.5f,     0.0f,   0.0f,  -1.0f,     1.0f,  1.0f,  
    -0.5f,   -0.5f,   -0.5f,    -1.0f,   0.0f,   0.0f,     0.0f,  0.0f,  
    -0.5f,   -0.5f,    0.5f,    -1.0f,   0.0f,   0.0f,     1.0f,  0.0f,  
    -0.5f,    0.5f,    0.5f,    -1.0f,   0.0f,   0.0f,     1.0f,  1.0f,  
    -0.5f,    0.5f,   -0.5f,    -1.0f,   0.0f,   0.0f,     0.0f,  1.0f,  
     0.5f,   -0.5f,    0.5f,     1.0f,   0.0f,   0.0f,     1.0f,  0.0f,  
     0.5f,   -0.5f,   -0.5f,     1.0f,   0.0f,   0.0f,     0.0f,  0.0f,  
     0.5f,    0.5f,   -0.5f,     1.0f,   0.0f,   0.0f,     0.0f,  1.0f,  
     0.5f,    0.5f,    0.5f,     1.0f,   0.0f,   0.0f,     1.0f,  1.0f,  
     0.5f,    0.5f,   -0.5f,     0.0f,   1.0f,   0.0f,     1.0f,  1.0f,  
    -0.5f,    0.5f,   -0.5f,     0.0f,   1.0f,   0.0f,     0.0f,  1.0f,  
    -0.5f,    0.5f,    0.5f,     0.0f,   1.0f,   0.0f,     0.0f,  0.0f,  
     0.5f,    0.5f,    0.5f,     0.0f,   1.0f,   0.0f,     1.0f,  0.0f,  
    -0.5f,   -0.5f,   -0.5f,     0.0f,  -1.0f,   0.0f,     0.0f,  0.0f,  
     0.5f,   -0.5f,   -0.5f,     0.0f,  -1.0f,   0.0f,     1.0f,  0.0f,  
     0.5f,   -0.5f,    0.5f,     0.0f,  -1.0f,   0.0f,     1.0f,  1.0f,  
    -0.5f,   -0.5f,    0.5f,     0.0f,  -1.0f,   0.0f,     0.0f,  1.0f
};

    indices = {
    // front
    0,   1,  2,  0,  2,  3, 
    // back
    4,   5,  6,  4,  6,  7, 
    // left
    8,   9, 10,  8, 10, 11, 
    // right
    12, 13, 14, 12, 14, 15,
    // top
    16, 17, 18, 16, 18, 19, 
    // bottom
    20, 21, 22, 20, 22, 23
};

    Mesh cubeMesh = Mesh( vertices, indices, true, true, false );
    cubeMesh.setShader( RessourceManager::GetShader( 1, false, false, false, false, false, 7 ) );

    return cubeMesh;
}

const Mesh DataProvider::generatePlaneMesh( glm::vec3 _v0, glm::vec3 _v1, glm::vec3 _v2, glm::vec3 _v3, unsigned int _div ) {
    std::vector<float> planeVertices = generatePlaneVertices( _v0, _v1, _v2, _v3, _div );
    std::vector<unsigned int> planeIndices = generatePlaneIndices( _div );

    return Mesh(planeVertices, planeIndices, true, true, false);
}

const std::vector<float> DataProvider::generatePlaneVertices( glm::vec3 _v0, glm::vec3 _v1, glm::vec3 _v2, glm::vec3 _v3, unsigned int _div ) {

    //  v3-----v2
    //  |       |
    //  |       |
    //  v0-----v1
    std::vector<float> vertices;
    float divFloat = float( _div );
    glm::vec3 vec03 = (_v3 - _v0) / divFloat;
    glm::vec3 vec12 = (_v2 - _v1) / divFloat;

    for (int row = 0; row < _div + 1; row++) {
        float rowFloat = float( row );
        glm::vec3 start = _v0 + vec03 * rowFloat;
        glm::vec3 end = _v1 + vec12 * rowFloat;
        glm::vec3 lineDiv = (end - start) / divFloat;

        for (int col = 0; col < _div + 1; col++) {
            float colFloat = float( col );
            glm::vec3 position = start + colFloat * lineDiv;
            glm::vec3 normal = glm::cross( glm::normalize(vec03), glm::normalize((end - start)) );
            glm::vec2 texCoords = glm::vec2( colFloat / _div, rowFloat / _div );

            vertices.emplace_back(position.x);
            vertices.emplace_back(position.y);
            vertices.emplace_back(position.z);
            vertices.emplace_back(normal.x);
            vertices.emplace_back(normal.y);
            vertices.emplace_back(normal.z);
            vertices.emplace_back(texCoords.x);
            vertices.emplace_back(texCoords.y);
        }
    }

    return vertices;
}

const std::vector<unsigned int> DataProvider::generatePlaneIndices(unsigned int _div ) {
    
    
        //  v3-----v2
        //  |       |
        //  |       |
        //  v0-----v1
 
        // moving up a row equals index+div+1
    std::vector<unsigned int> indices;

    // only div-1 iterations, since there are no vertices to connect to at the end
    for (int row = 0; row < _div; row++) {
        for (int col = 0; col < _div; col++) {

            unsigned int curIndex;
            curIndex = row * (_div + 1) + col;

            unsigned int otherIndex1, otherIndex2;
            // first triangle
            // 1--------2
            // |       /
            // |      /
            // |     /
            // |    /
            // |   /
            // |  /
            // | /
            // |/
            // C

            otherIndex1 = curIndex + _div + 1;
            otherIndex2 = curIndex + _div + 2;
            indices.push_back( curIndex );
            indices.push_back( otherIndex1 );
            indices.push_back( otherIndex2 );

            // second triangle
            //          1
            //         /|
            //        / |
            //       /  |
            //      /   |
            //     /    |
            //    /     |
            //   /      |
            //  /       |
            // C--------2

            otherIndex1 = curIndex + _div + 2;
            otherIndex2 = curIndex + 1;
            indices.push_back( curIndex );
            indices.push_back( otherIndex1 );
            indices.push_back( otherIndex2 );
        }
    }

    return indices;
}
