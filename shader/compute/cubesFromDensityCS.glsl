#version 430 core

layout (local_size_x = 33, local_size_y = 33, local_size_z = 33) in;

layout(r32f, binding = 0) uniform image3D imgOutput;

layout(std430, binding = 1 ) writeonly buffer vertices
{
    float vertexData[];
};

layout(std430, binding = 2 ) writeonly buffer indices
{
    unsigned int indiceData[];
};

shared int dataIterator;
shared int indiceIterator;

float cubeVertices[] = {
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

unsigned int cubeIndices[] = {
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

void main() {
    float density = 0.0f;
    uvec3 localID = gl_LocalInvocationID;
    ivec3 texelCoord = ivec3(gl_GlobalInvocationID.xyz);
	if(localID.x == 0 && localID.y == 0 && localID.z == 0) dataIterator = 0;

    if(imageLoad(imgOutput, texelCoord).x > 0.0f) {
        float cubeData[24*(3+3+2)];

        // add cube at texelPos
        for(int i = 0; i < 24; i++) {
            cubeData[i*8 + 0] = cubeVertices[i*8]       + 1.0f * texelCoord.x;
            cubeData[i*8 + 1] = cubeVertices[i*8 + 1]   + 1.0f * texelCoord.y;
            cubeData[i*8 + 2] = cubeVertices[i*8 + 2]   + 1.0f * texelCoord.z;

            cubeData[i*8 + 3] = cubeVertices[i*8 + 3];
            cubeData[i*8 + 4] = cubeVertices[i*8 + 4];
            cubeData[i*8 + 5] = cubeVertices[i*8 + 5];

            cubeData[i*8 + 6] = cubeVertices[i*8 + 6];
            cubeData[i*8 + 7] = cubeVertices[i*8 + 7];
        }

        memoryBarrierShared();
        //barrier();

        for(int i = 0; i < 192; i++) {
            vertexData[dataIterator*192 + i] = cubeData[i];
        }

        for(int i = 0; i < 36; i++) {
            indiceData[dataIterator*36 + i] = indices[i] + dataIterator*24;
        }

        atomicAdd(dataIterator, 1);
    }
}
