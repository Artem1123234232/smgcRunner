#include "ObjectsGenerator.h"

void Quad(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, float attached) {
    const auto base = static_cast<GLuint>(vertices.size());

    static constexpr std::array<glm::vec3, 4> kQuad = {{
        {-1.0f, -1.0f, 0.0f},
        { 1.0f, -1.0f, 0.0f},
        { 1.0f,  1.0f, 0.0f},
        {-1.0f,  1.0f, 0.0f},
    }};
    for (auto& p : kQuad) vertices.push_back({p, attached});

    indices.reserve(indices.size() + 6);
    indices.insert(indices.end(), {
        base + 0, base + 1, base + 2,
        base + 2, base + 3, base + 0,
    });
}
void Cube(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, float radius, float attached) {
    const auto base = static_cast<GLuint>(vertices.size());

    static constexpr std::array<glm::vec3, 8> kCube = {{
        {-1.0f, -1.0f, -1.0f},
        { 1.0f, -1.0f, -1.0f},
        { 1.0f,  1.0f, -1.0f},
        {-1.0f,  1.0f, -1.0f},
        {-1.0f, -1.0f, 1.0f},
        { 1.0f, -1.0f, 1.0f},
        { 1.0f,  1.0f, 1.0f},
        {-1.0f,  1.0f, 1.0f}
    }};
    for (auto& p : kCube) vertices.push_back({p * radius, attached});

    indices.reserve(indices.size() + 12);
    indices.insert(indices.end(), {
        base + 2, base + 3, base + 0,
        base + 0, base + 1, base + 2,

        base + 6, base + 5, base + 4,
        base + 4, base + 7, base + 6,

        base + 7, base + 4, base + 0,
        base + 0, base + 3, base + 7,

        base + 6, base + 2, base + 1,
        base + 1, base + 5, base + 6,

        base + 5, base + 1, base + 0,
        base + 0, base + 4, base + 5,

        base + 6, base + 7, base + 3,
        base + 3, base + 2, base + 6
    });
}
void AntiCube(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, float radius, float attached) {
    const auto base = static_cast<GLuint>(vertices.size());

    static constexpr std::array<glm::vec3, 8> kCube = {{
        {-1.0f, -1.0f, -1.0f},
        { 1.0f, -1.0f, -1.0f},
        { 1.0f,  1.0f, -1.0f},
        {-1.0f,  1.0f, -1.0f},
        {-1.0f, -1.0f, 1.0f},
        { 1.0f, -1.0f, 1.0f},
        { 1.0f,  1.0f, 1.0f},
        {-1.0f,  1.0f, 1.0f}
    }};
    for (auto& p : kCube) vertices.push_back({p * radius, attached});

    indices.reserve(indices.size() + 12);
    indices.insert(indices.end(), {
        base + 0, base + 3, base + 2,
        base + 2, base + 1, base + 0,

        base + 4, base + 5, base + 6,
        base + 6, base + 7, base + 4,

        base + 0, base + 4, base + 7,
        base + 7, base + 3, base + 0,

        base + 1, base + 2, base + 6,
        base + 6, base + 5, base + 1,

        base + 0, base + 1, base + 5,
        base + 5, base + 4, base + 0,

        base + 3, base + 7, base + 6,
        base + 6, base + 2, base + 3
    });
}