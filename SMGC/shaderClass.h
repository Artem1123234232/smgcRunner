#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glad/glad.h>

// For console output
#include <iostream>

// For read files
#include "../Core/tools.h"

class Shader {
public:
    GLuint ID;

    Shader(const char* vertexFile, const char* fragmentFile);
    
    void Activate();
    void Delete();
    int getStatus(); // Get status - error or normal

    void setVec3(const char* name, float x, float y, float z);
    void setVec2(const char* name, float x, float y);
    void setFloat(const char* name, float v);
    void setVec3(const char* name, glm::vec3 v);
    void setVec2(const char* name, glm::vec2 v);
private:
    int status;
};