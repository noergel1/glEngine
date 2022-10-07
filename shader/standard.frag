//#version 430 core
//
//#define VERTEXFORMAT 15
//#define EMISSIVEMAP 1
//#define SPECULARMAP 1
//#define NORMALMAP 1
//#define HEIGHTMAP 1

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


in VS_OUT {

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

} fs_in;

layout(location = 0) out vec4 Output;

#define OPERATOR *

layout (std140, binding = 2) uniform dirLight
{
    vec3 dirDirection;
    vec3 dirAmbient;
    vec3 dirDiffuse;
    vec3 dirSpecular;
};

struct Material {
sampler2D diffuse0;
float diffuse0_strength;

#if DIFFUSEMAP_1
    sampler2D diffuse1;
    float diffuse1_strength;
#endif

#if DIFFUSEMAP_2
    sampler2D diffuse2;
    float diffuse2_strength;
#endif

#if DIFFUSEMAP_3
    sampler2D diffuse3;
    float diffuse3_strength;
#endif

#if DIFFUSEMAP_4
    sampler2D diffuse4;
    float diffuse4_strength;
#endif

#if DIFFUSEMAP_5
    sampler2D diffuse5;
    float diffuse5_strength;
#endif

#if SPECULARMAP
    sampler2D specular;
#endif

#if AMBIENTMAP
    sampler2D ambient;
#endif

#if EMISSIVEMAP
    sampler2D emissive;
#endif

#if HEIGHTMAP
    sampler2D height;
#endif

#if NORMALMAP
    sampler2D normal;
#endif

#if SHININESSMAP
    sampler2D shininess
#else
    float shininess;
#endif
}; 

uniform Material material1;


// Directional Light
//struct DirLight {
//    vec3 direction;
//  
//    vec3 ambient;
//    vec3 diffuse;
//    vec3 specular;
//};  
//uniform DirLight dirLight;



// Point Lights
//struct PointLight {    
//    vec3 position;
//    
//    float constant;
//    float linear;
//    float quadratic;  
//
//    vec3 ambient;
//    vec3 diffuse;
//    vec3 specular;
//};  
//#define NR_POINT_LIGHTS 4  
//uniform PointLight pointLights[NR_POINT_LIGHTS];
//
//
//// Spotlight
//struct SpotLight {
//    vec3  position;
//    vec3  direction;
//    float innerCutOff;
//    float outerCutOff;
//
//    vec3 ambient;
//    vec3 diffuse;
//    vec3 specular;
//
//    float constant;
//    float linear;
//    float quadratic;
//}; 
//uniform SpotLight spotLight;

// camera position
layout (std140, binding = 4) uniform Camera
{
    vec3 cameraPosition;
};

// Calculation Functions
vec3 CalcDirLight();
//vec3 CalcPointLight(PointLight light);  
//vec3 CalcSpotLight(SpotLight light);
vec3 GetNormal();



vec3 normal = GetNormal();
vec3 lightDir = normalize(-fs_in.FragPos);
vec3 viewDir = normalize(cameraPosition - fs_in.FragPos);
vec3 reflectDir = reflect(-lightDir, normal);

#if TEXCOORDS
    vec3 texColorAmbient = vec3(texture(material1.diffuse0, fs_in.TexCoord));
    vec3 texColorDiffuse = vec3(texture(material1.diffuse0, fs_in.TexCoord));

    #if SPECULARMAP
        vec3 texColorSpecular = vec3(texture(material1.specular, fs_in.TexCoord));
    #else
        vec3 texColorSpecular = vec3(1.0f);
    #endif

    #if SHININESSMAP 
        float shininess = vec3(texture(material1.shininess, fs_in.TexCoord));
    #else 
        float shininess = 32.0f;
    #endif
//    vec3 texColorSpecular = vec3(texture(material1.specular, fs_in.TexCoord));
//    vec3 texColorAmbient = vec3(1.0f, 1.0f, 0.0f);
//    vec3 texColorDiffuse = vec3(1.0f, 1.0f, 0.0f);
#else
    vec3 texColorAmbient = vec3(1.0f);
    vec3 texColorDiffuse = vec3(1.0f);
    vec3 texColorSpecular = vec3(1.0f);
#endif


void main()
{

//    result = vec4(1.0f);
//
    vec3 result = CalcDirLight();

    #if EMISSIVEMAP
        result += vec3(texture(material1.emissive, fs_in.TexCoord));
    #endif

    Output = vec4(result, 1.0f);
//
////    for(int i = 0; i < NR_POINT_LIGHTS; i++)
////    {
////        result += CalcPointLight(pointLights[i]);
////    }
//
//
////    result += CalcSpotLight(spotLight);
//
//        float width = 800, 
//          height = 600;
//
//    vec4 coord = gl_FragCoord;
//
//    float x = coord.x / width;
//    float y = coord.y / height;
//    
//    float xDiff = (x - 0.5f); 
//    float yDiff = (y - 0.5f);
//    float avgDiff = (abs(xDiff) + abs(yDiff));


//    gl_FragColor = vec4(result, 1.0f);
}

vec3 GetNormal() {
#if NORMALMAP
        return normalize(vec3(texture(material1.normal, fs_in.TexCoord)));
#else 
    #if NORMALS
        // normals should always be there, since they're calculated through assimp (aiProcess_GenNormals)
        return normalize(fs_in.Normal);
    #else
        return vec3(0.0f);
    #endif
#endif
}

vec3 CalcDirLight()
{
    vec3 lightDir = normalize(-dirDirection);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // combine results
    vec3 ambient  = dirAmbient  * texColorAmbient;
    vec3 diffuse  = dirDiffuse  * diff * texColorDiffuse;
    vec3 specular = dirSpecular * spec * texColorSpecular;
    return (ambient + diffuse + specular);
}  

//vec3 CalcPointLight(PointLight light)
//{
//    vec3 lightDir = normalize(light.position - fs_in.FragPos);
//    // diffuse shading
//    float diff = max(dot(norm, lightDir), 0.0);
//    // specular shading
//    vec3 reflectDir = reflect(-lightDir, norm);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material1.shininess);
//    // attenuation
//    float distance    = length(light.position - fs_in.FragPos);
//    float attenuation = 1.0 / (light.constant + light.linear * distance + 
//  			     light.quadratic * (distance * distance));    
//    // combine results
//    vec3 ambient  = light.ambient  * texColorAmbient;
//    vec3 diffuse  = light.diffuse  * diff * diff * texColorDiffuse;
//    vec3 specular = light.specular * spec * spec * texColorSpecular;
//    ambient  *= attenuation;
//    diffuse  *= attenuation;
//    specular *= attenuation;
//    return (ambient + diffuse + specular);
//} 
//
//
//vec3 CalcSpotLight(SpotLight light)
//{
//
//
//
//    vec3 viewDir = normalize(-fs_in.FragPos);
//    vec3 reflectDir = reflect(light.direction, norm);
//    vec3 lightDir = normalize(light.position - fs_in.FragPos);
//
//     
//
//    
//    // ambient
//    vec3 ambient = light.ambient * texColorAmbient;
//    
//    // diffuse 
//    float diff = max(dot(norm, lightDir), 0.0);
//    vec3 diffuse = light.diffuse * diff * texColorDiffuse;  
//    
//    // specular
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material1.shininess);
//    vec3 specular = light.specular * spec * texColorSpecular;  
//    
//    // spotlight (soft edges)
//    float theta     = dot(lightDir, normalize(-light.direction));
//    float epsilon   = light.innerCutOff - light.outerCutOff;
//    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
//    diffuse  *= intensity;
//    specular *= intensity;
//    
//    // attenuation
//    float distance    = length(light.position - fs_in.FragPos);
//    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
//    ambient  *= attenuation; 
//    diffuse   *= attenuation;
//    specular *= attenuation;   
//        
//    vec3 result = ambient + diffuse + specular;
//
//
//
//    return result;
//}