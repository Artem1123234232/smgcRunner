#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec3 pos;
    float attached; // 0.0 = world, 1.0 = camera
    GLint objectIdx = -1;
};

class VBO {
public:
    GLuint ID;
    size_t capacityBytes = 0;

    VBO();

    void Upload(const std::vector<Vertex>& vertices);
    void Bind();
    void Unbind();
    void Delete();
};