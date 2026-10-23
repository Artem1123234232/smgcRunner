#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <algorithm>
#include <vector>

#include "VBO.h"

void Quad(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, float attached = 0.0f);
void Cube(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, float radius, float attached = 0.0f);
void AntiCube(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, float radius, float attached = 0.0f);