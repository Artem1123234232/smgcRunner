#pragma once

// Base task
#include "../Core/BaseTask.h"

// Object class
#include "ObjectsBuffer.h"

// For unique_ptr
#include <memory>

class task_SmgcSwapObjects: public BaseTask {
public:
    task_SmgcSwapObjects();
};
bool taskIs_SmgcSwapObjects(uint32_t taskIdx);

class task_SmgcClearObjects: public BaseTask {
public:
    task_SmgcClearObjects();
};
bool taskIs_SmgcClearObjects(uint32_t taskIdx);

class task_SmgcPushObject: public BaseTask {
public:
    task_SmgcPushObject(std::unique_ptr<Object> t_obj);
    std::unique_ptr<Object> obj = nullptr;
};
bool taskIs_SmgcPushObject(uint32_t taskIdx);