#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

// For vectors
#include <vector>

struct Object {
    glm::vec4 data1;
    glm::vec4 data2;
    glm::vec4 data3;
    glm::vec4 data4;
};
// std430: три vec4 = 48 байт
static_assert(sizeof(Object) == 64, "Object layout does not match std430");

struct GpuObject {
    glm::vec4 data1;
    glm::vec4 data2;
    glm::vec4 data3;
    glm::vec4 invRot[3];
};
static_assert(sizeof(GpuObject) == 96, "GpuObject layout does not match std430");

class ObjectsBuffer {
public:
    GLuint ID;
    size_t capacityBytes = 0;
    ObjectsBuffer();

    void Upload(const std::vector<GpuObject>& objects);
    void Bind(int bind);
    void Delete();
};