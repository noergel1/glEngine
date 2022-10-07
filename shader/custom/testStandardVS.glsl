#version 430 core
#define VERTEXFORMAT 7

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

#if CHECK_BIT(VERTEXFORMAT, 1)
    #define NORMALS 1
#endif

#if CHECK_BIT(VERTEXFORMAT, 2)
    #define TEXCOORDS 1
#endif

#if CHECK_BIT(VERTEXFORMAT, 3)
    #define TANGENTSPACE 1
#endif

layout (location = 0) in vec3 aPos;

#if NORMALS
layout (location = 1) in vec3 aNormal;
#endif
#if TEXCOORDS
layout (location = 2) in vec2 aTexCoord;
#endif
#if TANGENTSPACE
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
#endif
layout (location = 6) in mat4 aInstanceMatrix;




layout (std140, binding = 0) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

layout (std140, binding = 3) uniform ClippingPlane
{
    vec4 clippingPlane;
};

out VS_OUT {

    vec3 FragPos;

#if NORMALS
    vec3 Normal;
#endif

#if TEXCOORDS
    vec2 TexCoord;
#endif

#if TANGENTSPACE
    vec3 Tangent;
    vec3 Bitangent;
#endif

} vs_out;  


void main()
{
    vs_out.FragPos = vec3(aInstanceMatrix * vec4(aPos, 1.0));

#if NORMALS
    vs_out.Normal = mat3(transpose(inverse(aInstanceMatrix))) * aNormal;  
#endif

#if TEXCOORDS
    vs_out.TexCoord = aTexCoord;
#endif

#if TANGENTSPACE
    vs_out.Tangent = aTangent;
    vs_out.Bitangent = aBitangent;
#endif

    gl_ClipDistance[0] = dot(aInstanceMatrix * vec4(aPos, 1.0f), clippingPlane);
    gl_Position = projection * view * vec4(vs_out.FragPos, 1.0);
}