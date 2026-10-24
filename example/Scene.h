#pragma once

// Base component
#include <smpb/BaseComponent.h>

// Base task
#include <smpb/BaseTask.h>

// SMGC
#include <smgc/display3D.h>

#include <unordered_map>

class Scene: public BaseComponent
{
public:
    Scene();
    int init() override;
    int processTask(std::unique_ptr<BaseTask> task) override;
    int tick(long long tickCounter) override;
    void death() override;
private:
    bool isPressed(int key) const;
    void keyboard(long long tickCounter);

    std::unordered_map<int, bool> pressedKeys{};

    Camera camera{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}};

    float standartMoveSpeed = 3.0f;
    float standartRotSpeed  = 90.0f;

    float moveSpeed = standartMoveSpeed;
    float rotSpeed  = standartRotSpeed;
};
