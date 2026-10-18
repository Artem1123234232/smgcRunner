#include "SMGC.h"

// Core class
#include "../Core/Core.h"

/*GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};*/
GLfloat vertices[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f
};

GLuint indices[] = {
    0, 1, 2,
    2, 3, 0
};

std::vector<Object> Objects = {
    {{0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {1.0f, 0.5f, 0.2f, 1.0f}}
};

SMGC::SMGC() : BaseComponent("SMGC") {
    // Constructor
}

int SMGC::init() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    glfwSetErrorCallback([](int error, const char* desc){
        std::cerr << "GLFW Error " << error << ": " << desc << "\n";
    });

    window = glfwCreateWindow(windowWidth, windowHeight, "SMGC", NULL, NULL);
    if (!window) {
        std::cerr << getPrefix() << "glfwCreateWindow failed\n";
        glfwTerminate();
        return -ENODEV;
    }
    glfwMakeContextCurrent(window);


    glfwSetWindowUserPointer(window, this);  // привязываем this к окну

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* w, int fbW, int fbH) {
        auto* self = static_cast<SMGC*>(glfwGetWindowUserPointer(w));
        if (!self) return;
        self->windowWidth  = fbW;
        self->windowHeight = fbH;
        glViewport(0, 0, fbW, fbH);
    });

    int errorCode = gladLoadGL();
    if (errorCode == 0) {std::cerr << getPrefix() << "Critical Error: gladLoadGL failed, return code " << std::to_string(errorCode) << std::endl; return errorCode;}
    std::clog << getPrefix() << "GL: " << glGetString(GL_VERSION) << "\n";

    glViewport(0, 0, windowWidth, windowHeight);

    shaderProgram = std::make_unique<Shader>("SMGC/default.vert", "SMGC/default.frag");
    if (!shaderProgram) {std::cerr << getPrefix() << "Critical Error: shaderProgram is nullptr" << std::endl; return -ENODEV;}
    errorCode = shaderProgram->getStatus();
    if (errorCode != 0) {std::cerr << getPrefix() << "Critical Error: shaderProgram status code is " << std::to_string(errorCode) << std::endl; return errorCode;}
    
    vao = std::make_unique<VAO>();
    if (!vao) {std::cerr << getPrefix() << "Critical Error: vao is nullptr" << std::endl; return -ENODEV;}
    vao->Bind();

    vbo = std::make_unique<VBO>(vertices, sizeof(vertices));
    if (!vbo) {std::cerr << getPrefix() << "Critical Error: vbo is nullptr" << std::endl; return -ENODEV;}
    
    ebo = std::make_unique<EBO>(indices, sizeof(indices));
    if (!ebo) {std::cerr << getPrefix() << "Critical Error: ebo is nullptr" << std::endl; return -ENODEV;}

    objectsBuffer = std::make_unique<ObjectsBuffer>();
    if (!objectsBuffer) {std::cerr << getPrefix() << "Critical Error: objectsBuffer is nullptr" << std::endl; return -ENODEV;}
    objectsBuffer->Bind(0);

    vao->LinkVBO(*vbo, 0);
    
    vao->Unbind();
    vbo->Unbind();
    ebo->Unbind();

    return 0;
}

int SMGC::tick(long long tickCounter) {
    if (glfwWindowShouldClose(window)) {
        Core_stop();
    } else {
        //glClearColor(1.0f, 0.2f, 0.2f, 1.0f);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (!objectsBuffer) {std::cerr << getPrefix() << "Critical Error: objectsBuffer is nullptr" << std::endl; return -ENODEV;}
        objectsBuffer->Upload(Objects);

        if (!shaderProgram) {std::cerr << getPrefix() << "Critical Error: shaderProgram is nullptr" << std::endl; return -ENODEV;}
        shaderProgram->Activate();
        shaderProgram->setFloat("iTime", float(tickCounter) / float(Core_getTPS()));
        shaderProgram->setVec2("iResolution", float(windowWidth), float(windowHeight));
        
        if (!vao) {std::cerr << getPrefix() << "Critical Error: vao is nullptr" << std::endl; return -ENODEV;}
        vao->Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}

void SMGC::death() {
    if (vao) vao->Delete();
    if (vbo) vbo->Delete();
    if (ebo) ebo->Delete();
    if (shaderProgram) shaderProgram->Delete();
    if (objectsBuffer) objectsBuffer->Delete();
    if (window) glfwDestroyWindow(window);
    glfwTerminate();
    Core_stop();
}