#ifndef SMGC_H
#define SMGC_H

// Базовый компонент
#include "../Core/BaseComponent.h"

// Для работы со строками, вывода в консоль и других базовых операций
#include <iostream>
#include <format>

// For unique_ptr
#include <memory>

// Графика
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Opengl classes
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class SMGC: public BaseComponent
{
public:
    SMGC();
    int init() override;
    int tick(long long tickCounter) override;
    void death() override;
private:
    GLFWwindow* window = nullptr;
    
    std::unique_ptr<Shader> shaderProgram = nullptr;

    std::unique_ptr<VAO> vao = nullptr;
    std::unique_ptr<VBO> vbo = nullptr;
    std::unique_ptr<EBO> ebo = nullptr;

    int windowWidth  = 800;
    int windowHeight = 800;
};

#endif // SMGC_H
