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
        self->windowResize();
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

void SMGC::windowResize() {
    draw();
}

void SMGC::swapObjects() {
    std::swap(Objects_A, Objects_B);
}
void SMGC::clearObjects() {
    std::vector<Object>().swap(Objects_B);
}
void SMGC::pushObject(const Object& obj) {
    Objects_B.push_back(obj);
}
void SMGC::pushObject(Object&& obj) {
    Objects_B.push_back(std::move(obj));
}

int SMGC::keyboard() {
    float dt = 1.0f / float(Core_getTPS());

    if (glfwGetKey(window, GLFW_KEY_LEFT)  == GLFW_PRESS) cameraRot.y += rotSpeed * dt;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) cameraRot.y -= rotSpeed * dt;
    if (glfwGetKey(window, GLFW_KEY_UP)    == GLFW_PRESS) cameraRot.x += rotSpeed * dt;
    if (glfwGetKey(window, GLFW_KEY_DOWN)  == GLFW_PRESS) cameraRot.x -= rotSpeed * dt;

    // ограничение pitch, чтобы не было переворота (gimbal-lock)
    cameraRot.x = std::clamp(cameraRot.x, -89.0f, 89.0f);
    
    // ограничение yaw чтобы не было бесконечного увеличения числа
    cameraRot.y = std::fmod(cameraRot.y, 360.0f);

    // пересчитываем углы
    float yaw   = glm::radians(cameraRot.y);
    float pitch = glm::radians(cameraRot.x);

    // --- направления ---
    glm::vec3 forward = {0.0f, 0.0f, 0.0f};
    forward.x = -cos(pitch) * sin(yaw);
    forward.y =  sin(pitch);
    forward.z =  cos(pitch) * cos(yaw);

    glm::vec3 right;
    right.x = cos(yaw);
    right.y = 0.0f;
    right.z = sin(yaw);

    // --- ДВИЖЕНИЕ (WASD) ---
    float step = moveSpeed * dt;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) cameraPos += forward * step;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) cameraPos -= forward * step;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) cameraPos += right   * step;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) cameraPos -= right   * step;
    
    return 0;
}

int SMGC::draw() {
    //glClearColor(1.0f, 0.2f, 0.2f, 1.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (!objectsBuffer) {std::cerr << getPrefix() << "Critical Error: objectsBuffer is nullptr" << std::endl; return -ENODEV;}
    objectsBuffer->Upload(Objects_A);

    if (!shaderProgram) {std::cerr << getPrefix() << "Critical Error: shaderProgram is nullptr" << std::endl; return -ENODEV;}
    shaderProgram->Activate();
    shaderProgram->setFloat("iTime", float(localTickCounter) / float(Core_getTPS()));
    shaderProgram->setVec2("iResolution", float(windowWidth), float(windowHeight));
    shaderProgram->setVec3("iCameraPos", cameraPos);
    shaderProgram->setVec3("iCameraRot", cameraRot);
    
    if (!vao) {std::cerr << getPrefix() << "Critical Error: vao is nullptr" << std::endl; return -ENODEV;}
    vao->Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    return 0;
}

int SMGC::tick(long long tickCounter) {
    localTickCounter = tickCounter;
    if (glfwWindowShouldClose(window)) {
        Core_stop();
    } else {
        //cameraPos = {0.0f, 0.0f, sin(float(localTickCounter) / float(Core_getTPS())) * 5.0f};
        keyboard();

        if (Core_isDebugModeEnabled()) std::clog << getPrefix() << "cameraPos: " << std::to_string(cameraPos.x) << ";" << std::to_string(cameraPos.y) << ";" << std::to_string(cameraPos.z) << std::endl;
        if (Core_isDebugModeEnabled()) std::clog << getPrefix() << "cameraRot: " << std::to_string(cameraRot.x) << ";" << std::to_string(cameraRot.y) << ";" << std::to_string(cameraRot.z) << std::endl;
        
        int errorCode = draw();
        if (errorCode != 0) return errorCode;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    if (tickCounter % 1 == 0) {
        clearObjects();
        float m = (sin(float(tickCounter) / float(Core_getTPS()) * 2.0f)) * 0.5f + 0.5f;
        glm::vec3 col = PaletteCosinka(m);
        pushObject({{0.0f, m, m, m}, {0.5f, 0.0f, 0.0f, 0.0f}, {col.x, col.y, col.z, 1.0f}});
        swapObjects();
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