#pragma once

// Base component
#include <smpb/BaseComponent.h>

// Base task
#include <smpb/BaseTask.h>

// Для работы со строками, вывода в консоль и других базовых операций
#include <iostream>
#include <format>

// For unique_ptr
#include <memory>

// Графика
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vec math
#include <glm/glm.hpp>

// Opengl classes
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

// ObjectsBuffer and Object classes
#include "ObjectsBuffer.h"

// BEATIFUL!
#include "paletts.h"

// Task definitions
#include "taskDefinitions.h"

// Objects Generator
#include "ObjectsGenerator.h"

struct Camera {
    glm::vec3 pos;
    glm::vec3 rot;
};

class SMGC: public BaseComponent
{
public:
    SMGC();
    int init() override;
    void windowResize();
    void swapObjects();
    void clearObjects();
    void pushObject(std::unique_ptr<Object> obj);
    int draw();
    int keyboard();
    int processTask(std::unique_ptr<BaseTask> task) override;
    int tick(long long tickCounter) override;
    void death() override;
private:
    GLFWwindow* window = nullptr;
    long long localTickCounter = 0;
    
    std::unique_ptr<Shader> shaderProgram = nullptr;

    std::unique_ptr<VAO> vao = nullptr;
    std::unique_ptr<VBO> vbo = nullptr;
    std::unique_ptr<EBO> ebo = nullptr;

    std::vector<Object> Objects_A{};
    std::vector<Object> Objects_B{};

    std::vector<Vertex> Vertices_A{};
    std::vector<Vertex> Vertices_B{};
    std::vector<GLuint> Indices_A{};
    std::vector<GLuint> Indices_B{};

    std::unique_ptr<ObjectsBuffer> objectsBuffer = nullptr;

    Camera camera{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}};

    float standartMoveSpeed = 3.0f;
    float standartRotSpeed  = 90.0f;

    float moveSpeed = standartMoveSpeed;
    float rotSpeed  = standartRotSpeed;

    float maxDist = 50.0f;
    float epsilon = 0.0005f;

    int windowWidth  = 800;
    int windowHeight = 800;
};