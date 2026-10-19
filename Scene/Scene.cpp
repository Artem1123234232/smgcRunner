#include "Scene.h"

// Core class
#include "../Core/Core.h"

Scene::Scene() : BaseComponent("Scene") {
    // Constructor
}

int Scene::tick(long long tickCounter) {
    sendTask(std::make_unique<task_SmgcClearObjects>(), "SMGC");
    
    float m = (sin(float(tickCounter) / float(Core_getTPS()) * 2.0f)) * 0.5f + 0.5f;
    glm::vec3 col = PaletteCosinka(m);
    sendTask(
        std::make_unique<task_SmgcPushObject>(
            std::make_unique<Object>(
                glm::vec4{1.0f, m, m, 0.75f},
                glm::vec4{0.5f, 0.0f, 0.0f, 0.0f},
                glm::vec4{col.x, col.y, col.z, 1.0f}
            )
        ),
        "SMGC"
    );
    sendTask(
        std::make_unique<task_SmgcPushObject>(
            std::make_unique<Object>(
                glm::vec4{2.0f, m, m, 2.25f},
                glm::vec4{0.5f, 0.0f, 0.0f, 0.0f},
                glm::vec4{col.x, col.y, col.z, 1.0f}
            )
        ),
        "SMGC"
    );
    sendTask(
        std::make_unique<task_SmgcPushObject>(
            std::make_unique<Object>(
                glm::vec4{-1.0f, 0.0f, 0.0f, -0.75f},
                glm::vec4{0.5f, 0.0f, 0.0f, 0.0f},
                glm::vec4{0.75f, 0.75f, 0.75f, 1.0f}
            )
        ),
        "SMGC"
    );
    sendTask(
        std::make_unique<task_SmgcPushObject>(
            std::make_unique<Object>(
                glm::vec4{-2.0f, 0.0f, 0.0f, -2.25f},
                glm::vec4{0.5f, 0.0f, 0.0f, 0.0f},
                glm::vec4{1.0f, 1.0f, 0.4f, 1.0f}
            )
        ),
        "SMGC"
    );
    
    sendTask(std::make_unique<task_SmgcSwapObjects>(), "SMGC");
    return 0;
}