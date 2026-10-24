#pragma once

// Base component
#include <smpb/BaseComponent.h>

// Base task
#include <smpb/BaseTask.h>

// SMGC
#include <smgc/display3D.h>

class Scene: public BaseComponent
{
public:
    Scene();
    int tick(long long tickCounter) override;
};