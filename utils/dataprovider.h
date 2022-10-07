#pragma once
#include <vector>
#include "definitions.h"
#include "helpers.h"
#include "benchmark.h"
#include "model.h"
#include "../core/ressourcemanager.h"

class DataProvider {
public:
    static const Mesh generateCubeMesh(float _a);
    static const Mesh generatePlaneMesh( glm::vec3 _v0, glm::vec3 _v1, glm::vec3 _v2, glm::vec3 _v3, unsigned int _div );

    // procedural plane
    static const std::vector<float> generatePlaneVertices( glm::vec3 _v0, glm::vec3 _v1, glm::vec3 _v2, glm::vec3 _v3, unsigned int _div );
    static const std::vector<unsigned int> generatePlaneIndices( unsigned int _div );

    // procedural sphere
    static const std::vector<float> generateSphereVertices( unsigned int _sectorCount, unsigned int _stackCount, float _radius );
    static const std::vector<unsigned int> generateSphereIndices( unsigned int _sectorCount, unsigned int _stackCount );

    // procedural capsule
    static const std::vector<float> generateCapsuleVertices( unsigned int _divisions, float _height, float _radius );
    static const std::vector<unsigned int> generateCapsuleIndices( unsigned int _divisions );

    // vertices for a quad that fille the entire screen in Normalized Device Coordinates
    static const std::vector<float> getQuadVertices();
    static const std::vector<unsigned int> getQuadIndices();

    static const std::string getShipObjPath();

    // kernels for postprocessing
    static std::vector<float> noPostProcessing();
    static std::vector<float> getSharpenKernel();
    static std::vector<float> getBlurKernel();
    static std::vector<float> getEdgeDetectionKernel();



private:
    static const std::vector<float> cubeVertices;
    static const std::vector<unsigned int> cubeIndices;

    static const std::vector<float> planeVertices;
    static const std::vector<unsigned int> planeIndices;
};