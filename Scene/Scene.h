#pragma once

// Base component
#include "../Core/BaseComponent.h"

// Base task
#include "../Core/BaseTask.h"

// SMGC
#include "../SMGC/SMGC.h"

class Scene: public BaseComponent
{
public:
    Scene();
    int tick(long long tickCounter) override;
};