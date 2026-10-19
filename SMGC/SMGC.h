#pragma once

// Base component
#include "../Core/BaseComponent.h"

// Base task
#include "../Core/BaseTask.h"

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
    int proccessTask(std::unique_ptr<BaseTask> task) override;
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

    std::unique_ptr<ObjectsBuffer> objectsBuffer = nullptr;

    glm::vec3 cameraPos = {0.0f, 0.0f, 0.0f};
    glm::vec3 cameraRot = {0.0f, 0.0f, 0.0f};

    float moveSpeed = 3.0f;
    float rotSpeed  = 90.0f;

    int windowWidth  = 800;
    int windowHeight = 800;
};