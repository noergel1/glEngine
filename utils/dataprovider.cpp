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


    //// front
    //vertices.insert( vertices.end(), { frontBottomLeft.x, frontBottomLeft.y, frontBottomLeft.z,     front.x,front.y,front.z,   bottomRight.x,  bottomRight.y });
    //vertices.insert( vertices.end(), { frontBottomRight.x, frontBottomRight.y, frontBottomRight.z,  front.x,front.y,front.z,   bottomLeft.x,   bottomLeft.y });
    //vertices.insert( vertices.end(), { frontTopRight.x, frontTopRight.y, frontTopRight.z,           front.x,front.y,front.z,   topLeft.x,      topLeft.y });
    //vertices.insert( vertices.end(), { frontTopLeft.x, frontTopLeft.y, frontTopLeft.z,              front.x,front.y,front.z,   topRight.x,     topRight.y });
    //indices.insert( indices.end(), {  0, 1, 2, 0, 2, 3 } );

    //// back
    //vertices.insert( vertices.end(), { backBottomRight.x, backBottomRight.y, backBottomRight.z, back.x,back.y,back.z, bottomRight.x, bottomRight.y });
    //vertices.insert( vertices.end(), { backBottomLeft.x, backBottomLeft.y, backBottomLeft.z, back.x,back.y,back.z, bottomLeft.x, bottomLeft.y });
    //vertices.insert( vertices.end(), { backTopLeft.x, backTopLeft.y, backTopLeft.z, back.x,back.y,back.z, topLeft.x, topLeft.y });
    //vertices.insert( vertices.end(), { backTopRight.x, backTopRight.y, backTopRight.z, back.x,back.y,back.z, topRight.x, topRight.y });
    //indices.insert( indices.end(), { 4,5,6,4,6,7 } );

    //// left
    //vertices.insert( vertices.end(), { backBottomLeft.x, backBottomLeft.y, backBottomLeft.z, left.x,left.y,left.z, bottomLeft.x, bottomLeft.y });
    //vertices.insert( vertices.end(), { frontBottomLeft.x, frontBottomLeft.y, frontBottomLeft.z, left.x,left.y,left.z, bottomRight.x, bottomRight.y });
    //vertices.insert( vertices.end(), { frontTopLeft.x, frontTopLeft.y, frontTopLeft.z, left.x,left.y,left.z, topRight.x, topRight.y });
    //vertices.insert( vertices.end(), { backTopLeft.x, backTopLeft.y, backTopLeft.z, left.x,left.y,left.z, topLeft.x, topLeft.y });
    //indices.insert( indices.end(), { 8, 9, 10, 8, 10, 11 } );

    //// right
    //vertices.insert( vertices.end(), { frontBottomRight.x, frontBottomRight.y, frontBottomRight.z, right.x,right.y,right.z, bottomRight.x, bottomRight.y });
    //vertices.insert( vertices.end(), { backBottomRight.x, backBottomRight.y, backBottomRight.z, right.x,right.y,right.z, bottomLeft.x, bottomLeft.y });
    //vertices.insert( vertices.end(), { backTopRight.x, backTopRight.y, backTopRight.z, right.x,right.y,right.z, topLeft.x, topLeft.y });
    //vertices.insert( vertices.end(), { frontTopRight.x, frontTopRight.y, frontTopRight.z, right.x,right.y,right.z, topRight.x, topRight.y });
    //indices.insert( indices.end(), { 12, 13, 14, 12, 14, 15 } );

    //// top
    //vertices.insert( vertices.end(), { backTopRight.x, backTopRight.y, backTopRight.z, up.x,up.y,up.z, topRight.x, topRight.y });
    //vertices.insert( vertices.end(), { backTopLeft.x, backTopLeft.y, backTopLeft.z, up.x,up.y,up.z, topLeft.x, topLeft.y });
    //vertices.insert( vertices.end(), { frontTopLeft.x, frontTopLeft.y, frontTopLeft.z, up.x,up.y,up.z, bottomLeft.x, bottomLeft.y });
    //vertices.insert( vertices.end(), { frontTopRight.x, frontTopRight.y, frontTopRight.z, up.x,up.y,up.z, bottomRight.x, bottomRight.y });
    //indices.insert( indices.end(), { 16, 17, 18, 16, 18, 19 } );

    //// bottom
    //vertices.insert( vertices.end(), { backBottomLeft.x,    backBottomLeft.y,   backBottomLeft.z,   down.x,down.y,down.z,   bottomLeft.x,   bottomLeft.y });
    //vertices.insert( vertices.end(), { backBottomRight.x,   backBottomRight.y,  backBottomRight.z,  down.x,down.y,down.z,   bottomRight.x,  bottomRight.y });
    //vertices.insert( vertices.end(), { frontBottomRight.x,  frontBottomRight.y, frontBottomRight.z, down.x,down.y,down.z,   topRight.x,     topRight.y });
    //vertices.insert( vertices.end(), { frontBottomLeft.x,      frontBottomLeft.y,     frontBottomLeft.z,     down.x,down.y,down.z,   topLeft.x,      topLeft.y });
    //indices.insert( indices.end(), { 20, 21, 22, 20, 22, 23 } );

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

    //std::cout << "VERTICES:\n";
    //for (int i = 0; i < vertices.size(); i++) {
    //    std::cout << vertices[i] << ",";
    //}
    //std::cout << "\nINDICES:\n";
    //for (int i = 0; i < indices.size(); i++) {
    //    std::cout << indices[i] << ",";
    //}
    //std::cout << "\n";


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

//const std::vector<VertexData> DataProvider::generateSphereVertices( unsigned int _sectorCount, unsigned int _stackCount, float _radius ) {
//    std::vector<VertexData> vertices;
//
//    float x, y, z, xy;                              // vertex position
//    float nx, ny, nz, lengthInv = 1.0f / _radius;    // vertex normal
//    float s, t;                                     // vertex texCoord
//
//    float sectorStep = 2 * M_PI / _sectorCount;
//    float stackStep = M_PI / _stackCount;
//    float sectorAngle, stackAngle;
//
//    for (int i = 0; i <= _stackCount; ++i) {
//        stackAngle = M_PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
//        xy = _radius * cosf( stackAngle );             // r * cos(u)
//        z = _radius * sinf( stackAngle );              // r * sin(u)
//
//        // add (sectorCount+1) vertices per stack
//        // the first and last vertices have same position and normal, but different tex coords
//        for (int j = 0; j <= _sectorCount; ++j) {
//            VertexData newVertex;
//
//            sectorAngle = j * sectorStep;           // starting from 0 to 2pi
//
//            // vertex position (x, y, z)
//            x = xy * cosf( sectorAngle );             // r * cos(u) * cos(v)
//            y = xy * sinf( sectorAngle );             // r * cos(u) * sin(v)
//            newVertex.Position.x = x;
//            newVertex.Position.y = y;
//            newVertex.Position.z = z;
//
//            // normalized vertex normal (nx, ny, nz)
//            nx = x * lengthInv;
//            ny = y * lengthInv;
//            nz = z * lengthInv;
//            newVertex.Normal.x = nx;
//            newVertex.Normal.y = ny;
//            newVertex.Normal.z = nz;
//
//            // vertex tex coord (s, t) range between [0, 1]
//            s = (float)j / _sectorCount;
//            t = (float)i / _stackCount;
//            newVertex.TexCoords.x = s;
//            newVertex.TexCoords.y = t;
//
//            vertices.push_back( newVertex );
//        }
//    }
//
//    return vertices;
//}
//
//const std::vector<unsigned int> DataProvider::generateSphereIndices( unsigned int _sectorCount, unsigned int _stackCount ) {
//    std::vector<unsigned int> indices;
//
//    // generate CCW index list of sphere triangles
//    // k1--k1+1
//    // |  / |
//    // | /  |
//    // k2--k2+1
//    std::vector<unsigned int> lineIndices;
//    int k1, k2;
//    for (int i = 0; i < _stackCount; ++i) {
//        k1 = i * (_sectorCount + 1);     // beginning of current stack
//        k2 = k1 + _sectorCount + 1;      // beginning of next stack
//
//        for (int j = 0; j < _sectorCount; ++j, ++k1, ++k2) {
//            // 2 triangles per sector excluding first and last stacks
//            // k1 => k2 => k1+1
//            if (i != 0) {
//                indices.push_back( k1 );
//                indices.push_back( k2 );
//                indices.push_back( k1 + 1 );
//            }
//
//            // k1+1 => k2 => k2+1
//            if (i != (_stackCount - 1)) {
//                indices.push_back( k1 + 1 );
//                indices.push_back( k2 );
//                indices.push_back( k2 + 1 );
//            }
//
//            // store indices for lines
//            // vertical lines for all stacks, k1 => k2
//            lineIndices.push_back( k1 );
//            lineIndices.push_back( k2 );
//            if (i != 0)  // horizontal lines except 1st stack, k1 => k+1
//            {
//                lineIndices.push_back( k1 );
//                lineIndices.push_back( k1 + 1 );
//            }
//        }
//    }
//
//    return indices;
//}
//
//    // procedural capsule
//const std::vector<VertexData> DataProvider::generateCapsuleVertices( unsigned int _divisions, float _height, float _radius ) {
//    std::vector<VertexData> vertices;
//
//    if (_divisions % 2 == 0) _divisions++;
//
//    float cylinderStep = (2 * M_PI) / _divisions;
//    float lengthInv = 1.0f / _radius;
//
//    // generate the two half spheres
//    std::vector<VertexData> upperCircleVerts;
//    std::vector<VertexData> lowerCircleVerts;
//
//    unsigned int cylinderVertCount = vertices.size();
//
//
//    float x, y, z, xz;                              // vertex position
//    float nx, ny, nz;    // vertex normal
//    float s, t;                                     // vertex texCoord
//
//    float sectorStep = 2 * M_PI / _divisions;
//    float stackStep = M_PI / _divisions;
//    float sectorAngle, stackAngle;
//
//    for (int i = 0; i <= _divisions; ++i) {
//        stackAngle = M_PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
//        xz = _radius * cosf( stackAngle );             // r * cos(u)
//        y = _radius * sinf( stackAngle );              // r * sin(u)
//
//        // add (sectorCount+1) vertices per stack
//        // the first and last vertices have same position and normal, but different tex coords
//        for (int j = 0; j <= _divisions; ++j) {
//            VertexData newVertex;
//
//            sectorAngle = j * sectorStep;           // starting from 0 to 2pi
//
//            // vertex position (x, y, z)
//            x = xz * cosf( sectorAngle );             // r * cos(u) * cos(v)
//            z = xz * sinf( sectorAngle );             // r * cos(u) * sin(v)
//            newVertex.Position.x = x;
//            newVertex.Position.y = y;
//            newVertex.Position.z = z;
//
//            // normalized vertex normal (nx, ny, nz)
//            nx = x * lengthInv;
//            ny = y * lengthInv;
//            nz = z * lengthInv;
//            newVertex.Normal.x = nx;
//            newVertex.Normal.y = ny;
//            newVertex.Normal.z = nz;
//
//            // vertex tex coord (s, t) range between [0, 1]
//            s = (float)j / _divisions;
//            t = (float)i / _divisions;
//            newVertex.TexCoords.x = s;
//            newVertex.TexCoords.y = t;
//
//            if (i == ceil( _divisions / 2 )) {
//                newVertex.Position.y += _height / 2;
//                upperCircleVerts.push_back( newVertex );
//                newVertex.Position.y -= _height;
//                lowerCircleVerts.push_back( newVertex );
//                continue;
//            }
//            if (i < ceil( _divisions / 2 )) {
//                newVertex.Position.y += _height/2;
//                upperCircleVerts.push_back( newVertex );
//                continue;
//            }
//            if (i > ceil( _divisions / 2 )) {
//                newVertex.Position.y -= _height/2;
//                lowerCircleVerts.push_back( newVertex );
//                continue;
//            }
//        }
//    }
//
//    vertices.insert(vertices.end(), upperCircleVerts.begin(), upperCircleVerts.end() );
//    vertices.insert(vertices.end(), lowerCircleVerts.begin(), lowerCircleVerts.end() );
//
//    return vertices;
//}
//
//const std::vector<unsigned int> DataProvider::generateCapsuleIndices( unsigned int _divisions ) {
//    std::vector<unsigned int> indices;
//
//    if (_divisions % 2 == 0) _divisions++;
//
//    // generate CCW index list of sphere triangles
//    // k1--k1+1
//    // |  / |
//    // | /  |
//    // k2--k2+1
//
//    std::vector<int> lineIndices;
//    int k1, k2;
//    for(int i = 0; i < _divisions + 1; ++i)
//    {
//        k1 = i * (_divisions + 1);     // beginning of current stack
//        k2 = k1 + _divisions + 1;      // beginning of next stack
//
//        //if (i == floor( _divisions / 2.0f )) continue;
//
//        for(int j = 0; j < _divisions; ++j, ++k1, ++k2)
//        {
//
//            // 2 triangles per sector excluding first and last stacks
//            // k1 => k2 => k1+1
//            if(i != 0)
//            {
//                indices.push_back(k2);
//                indices.push_back(k1);
//                indices.push_back(k1 + 1);
//            }
//
//            // k1+1 => k2 => k2+1
//            if(i != (_divisions))
//            {
//                indices.push_back(k2);
//                indices.push_back(k1 + 1);
//                indices.push_back(k2 + 1);
//            }
//
//            // store indices for lines
//            // vertical lines for all stacks, k1 => k2
//            lineIndices.push_back(k1);
//            lineIndices.push_back(k2);
//            if(i != 0)  // horizontal lines except 1st stack, k1 => k+1
//            {
//                lineIndices.push_back(k1);
//                lineIndices.push_back(k1 + 1);
//            }
//        }
//    }
//
//    return indices;
//}
//
//const std::vector<float> DataProvider::getQuadVertices()
//{
//    return std::vector<float>{
//        // positions   // texCoords
//        -1.0f, 1.0f, 0.0f, 1.0f,
//            -1.0f, -1.0f, 0.0f, 0.0f,
//            1.0f, -1.0f, 1.0f, 0.0f,
//
//            -1.0f, 1.0f, 0.0f, 1.0f,
//            1.0f, -1.0f, 1.0f, 0.0f,
//            1.0f, 1.0f, 1.0f, 1.0f
//    };
//}
//
//const std::vector<unsigned int> DataProvider::getQuadIndices()
//{
//    return std::vector<unsigned int>({ 0,1,2,3,4,5 });
//}


