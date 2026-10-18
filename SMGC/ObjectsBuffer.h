#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

// For vectors
#include <vector>

struct Object {
    glm::vec4 data1;
    glm::vec4 data2;
    glm::vec4 data3;
};
// std430: три vec4 = 48 байт, без выравнивающих «дыр»
static_assert(sizeof(Object) == 48, "Object layout does not match std430");

class ObjectsBuffer {
public:
    GLuint ID;
    size_t capacityBytes = 0;
    ObjectsBuffer();

    void Upload(const std::vector<Object>& objects);
    void Bind(int bind);
    void Delete();
};