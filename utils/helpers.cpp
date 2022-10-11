#include "helpers.h"

float degreeToRadians(float _angle)
{
	return _angle * (M_PI / 180);
}

float radiansToDegree(float _angle)
{
	return _angle * (180 / M_PI);
}

float getAngleBetweenVectorsDeg( glm::vec3 _vec1, glm::vec3 _vec2 ) {
	//_vec1 = glm::normalize( _vec1 );
	//_vec2 = glm::normalize( _vec2 );

	//float angle = acos( glm::dot( _vec1, _vec2 ) );
	//return angle * (180/M_PI);

	return 	atan2( glm::length( glm::cross( _vec1, _vec2 ) ), glm::dot( _vec1, _vec2 ) ) * (180/M_PI);
}

float getAngleBetweenVectorsRad( glm::vec3 _vec1, glm::vec3 _vec2 ) {
	return 	radiansToDegree(atan2( glm::length( glm::cross( _vec1, _vec2 ) ), glm::dot( _vec1, _vec2 ) ));
}

glm::vec3 rotatePointAroundCenter( glm::vec3 _point, glm::vec3 _center, glm::mat4 _rotationMat ) {
	glm::mat4x4 translate = glm::translate( 
							glm::mat4(1.0f), 
							glm::vec3( _center.x, _center.y, _center.z ) );
  glm::mat4x4 invTranslate = glm::inverse( translate );

  // The idea:
  // 1) Translate the object to the center
  // 2) Make the rotation
  // 3) Translate the object back to its original location

  glm::mat4x4 transform = translate * _rotationMat * invTranslate;

  return glm::vec3(transform * glm::vec4(_point, 1.0f));
}

glm::mat4 createSRTMat4( const Entity _entity ) {
		glm::mat4 matrix = glm::mat4( 1.0f );

						//translate
		matrix = glm::translate( matrix, _entity.Position );


				// rotate
		matrix = glm::rotate( matrix, glm::radians( _entity.Rotation.x ), glm::vec3( 1.0f, 0.0f, 0.0f ) );
		matrix = glm::rotate( matrix, glm::radians( _entity.Rotation.y ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
		matrix = glm::rotate( matrix, glm::radians( _entity.Rotation.z ), glm::vec3( 0.0f, 0.0f, 1.0f ) );

						//scale
		matrix = glm::scale( matrix, _entity.Scale );

		return matrix;
}

void printComputeShaderLimits() {
	GLint maxWorkGroupsX = 0;
    GLint maxWorkGroupsY = 0;
    GLint maxWorkGroupsZ = 0;
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &maxWorkGroupsX);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &maxWorkGroupsY);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &maxWorkGroupsZ);
    std::cout << "MAX WORK GROUP PER CALL: " << maxWorkGroupsX << " | " << maxWorkGroupsY << " | " << maxWorkGroupsZ << std::endl;

	GLint maxLocalSizeX = 0;
    GLint maxLocalSizeY = 0;
    GLint maxLocalSizeZ = 0;
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &maxLocalSizeX);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &maxLocalSizeY);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &maxLocalSizeZ);
    std::cout << "MAX LOCAL SIZE PER WORK GROUP: " << maxLocalSizeX << " | " << maxLocalSizeY << " | " << maxLocalSizeZ << std::endl;
}
