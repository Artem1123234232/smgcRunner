#pragma once

// Base component
#include <smpb/BaseComponent.h>

// Base task
#include <smpb/BaseTask.h>

// SMGC
#include "../SMGC/SMGC.h"

class Scene: public BaseComponent
{
public:
    Scene();
    int tick(long long tickCounter) override;
};