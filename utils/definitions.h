#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <unordered_map>
#include <map>


struct Entity {
    glm::vec3 Position;
    glm::vec3 Scale;
    glm::vec3 Rotation;
};

// defines possible inputs of player
enum class PlayerAction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

enum class ColliderType {
    CAPSULE,
    CUBE,
    SPHERE
};

struct ModelCollider {
    ColliderType colliderType;
    Entity diffToModel;			// defines the deviation from the models entity
};

template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}










#endif