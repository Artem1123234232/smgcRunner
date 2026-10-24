#include "SMGC.h"

// Core class
#include <smpb/Core.h>

SMGC::SMGC() : BaseComponent("SMGC") {
    // Constructor
}

int SMGC::init() {
    glfwSetErrorCallback([](int error, const char* desc){
        std::cerr << "GLFW Error " << error << ": " << desc << "\n";
    });

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

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
    if (errorCode == 0) {std::cerr << getPrefix() << "Critical Error: gladLoadGL failed, return code " << std::to_string(errorCode) << std::endl; return -ENODEV;}
    std::clog << getPrefix() << "GL: " << glGetString(GL_VERSION) << "\n";

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glViewport(0, 0, windowWidth, windowHeight);

    shaderProgram = std::make_unique<Shader>("SMGC/default.vert", "SMGC/default.frag");
    if (!shaderProgram) {std::cerr << getPrefix() << "Critical Error: shaderProgram is nullptr" << std::endl; return -ENODEV;}
    errorCode = shaderProgram->getStatus();
    if (errorCode != 0) {std::cerr << getPrefix() << "Critical Error: shaderProgram status code is " << std::to_string(errorCode) << std::endl; return errorCode;}
    
    vao = std::make_unique<VAO>();
    if (!vao) {std::cerr << getPrefix() << "Critical Error: vao is nullptr" << std::endl; return -ENODEV;}
    vao->Bind();

    vbo = std::make_unique<VBO>();
    if (!vbo) {std::cerr << getPrefix() << "Critical Error: vbo is nullptr" << std::endl; return -ENODEV;}

    ebo = std::make_unique<EBO>();
    if (!ebo) {std::cerr << getPrefix() << "Critical Error: ebo is nullptr" << std::endl; return -ENODEV;}
    ebo->Bind();

    objectsBuffer = std::make_unique<ObjectsBuffer>();
    if (!objectsBuffer) {std::cerr << getPrefix() << "Critical Error: objectsBuffer is nullptr" << std::endl; return -ENODEV;}
    objectsBuffer->Bind(0);

    vao->LinkVBO(*vbo, 0, 1);
    
    vao->Unbind();
    vbo->Unbind();
    ebo->Unbind();

    clearObjects();
    swapObjects();

    return 0;
}

void SMGC::windowResize() {
}

void SMGC::swapObjects() {
    std::swap(Objects_A, Objects_B);
    std::swap(Vertices_A, Vertices_B);
    std::swap(Indices_A, Indices_B);

    vao->Unbind();
    vbo->Upload(Vertices_A);
    ebo->Upload(Indices_A);
}
void SMGC::clearObjects() {
    Objects_B.clear();
    Vertices_B.clear();
    Indices_B.clear();

    //Quad(Vertices_B, Indices_B);
    AntiCube(Vertices_B, Indices_B, maxDist, 1.0f);
    Plane(Vertices_B, Indices_B, camera.pos, maxDist, -1.0f, epsilon);
}
void SMGC::pushObject(std::unique_ptr<Object> obj) {
    const float bound = ObjectBoundingRadius(*obj);
    const float dist = glm::distance(glm::vec3(obj->data1.y, obj->data1.z, obj->data1.w), camera.pos);
    if (bound >= 0.0f && dist - bound > maxDist) return;

    const size_t vertexStart = Vertices_B.size();
    const size_t indexStart = Indices_B.size();
    if (GenerateObject(Vertices_B, Indices_B, *obj) && dist + bound > maxDist)
        CullFarTriangles(Vertices_B, Indices_B, vertexStart, indexStart, camera.pos, maxDist);

    Objects_B.push_back(std::move(*obj));
}
/*void SMGC::getCamera(glm::vec3 newPos, glm::vec3 newRot) {
    camera.pos = newPos;
    camera.rot = newRot;
}
void SMGC::setCamera(glm::vec3 newPos, glm::vec3 newRot) {
    camera.pos = newPos;
    camera.rot = newRot;
}*/

int SMGC::keyboard() {
    float dt = 1.0f / float(Core_getTPS());

    if (glfwGetKey(window, GLFW_KEY_LEFT)  == GLFW_PRESS) camera.rot.y += rotSpeed * dt;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) camera.rot.y -= rotSpeed * dt;
    if (glfwGetKey(window, GLFW_KEY_UP)    == GLFW_PRESS) camera.rot.x += rotSpeed * dt;
    if (glfwGetKey(window, GLFW_KEY_DOWN)  == GLFW_PRESS) camera.rot.x -= rotSpeed * dt;
    
    // ограничение pitch, чтобы не было переворота (gimbal-lock)
    camera.rot.x = std::clamp(camera.rot.x, -89.0f, 89.0f);
    
    // ограничение yaw чтобы не было бесконечного увеличения числа
    camera.rot.y = std::fmod(camera.rot.y, 360.0f);

    // пересчитываем углы
    float yaw   = glm::radians(camera.rot.y);
    float pitch = glm::radians(camera.rot.x);

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

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.pos += forward * step;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.pos -= forward * step;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.pos += right   * step;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.pos -= right   * step;


    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        camera.rot.x = round(camera.rot.x / 45.0f) * 45.0f;
        camera.rot.y = round(camera.rot.y / 45.0f) * 45.0f;
        camera.rot.z = round(camera.rot.z / 45.0f) * 45.0f;
        camera.pos.x = floor(camera.pos.x) + 0.5;
        camera.pos.y = floor(camera.pos.y) + 0.5;
        camera.pos.z = floor(camera.pos.z) + 0.5;
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        camera.rot = {0.0f, 0.0f, 0.0f};
        camera.pos = {0.0f, 0.0f, 0.0f};
        moveSpeed = standartMoveSpeed;
        rotSpeed = standartRotSpeed;
    }

    if (localTickCounter % 10 == 0) {
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            rotSpeed /= 2.0f;
            moveSpeed /= 2.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            rotSpeed *= 2.0f;
            moveSpeed *= 2.0f;
        }
    }

    return 0;
}

int SMGC::draw() {
    //glClearColor(1.0f, 0.2f, 0.2f, 1.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!objectsBuffer) {std::cerr << getPrefix() << "Critical Error: objectsBuffer is nullptr" << std::endl; return -ENODEV;}
    objectsBuffer->Upload(Objects_A);

    if (!shaderProgram) {std::cerr << getPrefix() << "Critical Error: shaderProgram is nullptr" << std::endl; return -ENODEV;}
    shaderProgram->Activate();
    shaderProgram->setFloat("iTime", float(localTickCounter) / float(Core_getTPS()));
    shaderProgram->setVec2("iResolution", float(windowWidth), float(windowHeight));
    shaderProgram->setVec3("iCameraPos", camera.pos);
    shaderProgram->setVec3("iCameraRot", camera.rot);
    shaderProgram->setFloat("iMaxDist", maxDist);
    shaderProgram->setFloat("iEpsilon", epsilon);
    
    if (!vao) {std::cerr << getPrefix() << "Critical Error: vao is nullptr" << std::endl; return -ENODEV;}
    vao->Bind();

    // 1) заливка
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0f, 1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    shaderProgram->setFloat("iOutline", 1.0f);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    glDrawElements(GL_TRIANGLES, Indices_A.size(), GL_UNSIGNED_INT, 0);

    shaderProgram->setFloat("iOutline", 0.0f);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthFunc(GL_EQUAL);
    glDepthMask(GL_FALSE);
    glDrawElements(GL_TRIANGLES, Indices_A.size(), GL_UNSIGNED_INT, 0);

    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);

    // 2) обводка
    shaderProgram->setFloat("iOutline", 1.0f);
    glDisable(GL_POLYGON_OFFSET_FILL);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(1.0f);
    glDrawElements(GL_TRIANGLES, Indices_A.size(), GL_UNSIGNED_INT, 0);

    vao->Unbind();

    return 0;
}

int SMGC::processTask(std::unique_ptr<BaseTask> task) {
    uint32_t taskIdx = task->getIdx();
    if (taskIs_SmgcSwapObjects(taskIdx)) {
        swapObjects();
    } else if (taskIs_SmgcClearObjects(taskIdx)) {
        clearObjects();
    } else if (taskIs_SmgcPushObject(taskIdx)) {
        auto* typed = static_cast<task_SmgcPushObject*>(task.get());
        pushObject(std::move(typed->obj));
        typed->obj = nullptr;
    }
    return 0;
}

int SMGC::tick(long long tickCounter) {
    localTickCounter = tickCounter;
    if (glfwWindowShouldClose(window)) {
        Core_stop();
    } else {
        //camera.pos = {0.0f, 0.0f, sin(float(localTickCounter) / float(Core_getTPS())) * 5.0f};
        keyboard();

        if (Core_isDebugModeEnabled()) std::clog << getPrefix() << "camera.pos: " << std::to_string(camera.pos.x) << ";" << std::to_string(camera.pos.y) << ";" << std::to_string(camera.pos.z) << std::endl;
        if (Core_isDebugModeEnabled()) std::clog << getPrefix() << "camera.rot: " << std::to_string(camera.rot.x) << ";" << std::to_string(camera.rot.y) << ";" << std::to_string(camera.rot.z) << std::endl;
        
        int errorCode = draw();
        if (errorCode != 0) return errorCode;

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