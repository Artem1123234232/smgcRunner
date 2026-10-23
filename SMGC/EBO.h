#pragma once

#include <glad/glad.h>
#include <vector>

class EBO {
public:
    GLuint ID;
    size_t capacityBytes = 0;

    EBO();

    void Upload(const std::vector<GLuint>& indices);
    void Bind();
    void Unbind();
    void Delete();
};