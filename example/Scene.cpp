#include "Scene.h"

// Core class
#include <smpb/Core.h>

Scene::Scene() : BaseComponent("Scene") {
    // Constructor
}

int Scene::tick(long long tickCounter) {
    sendTask(std::make_unique<task_SmgcClearObjects>(), "SMGC");
    
    float time = float(tickCounter) / float(Core_getTPS());
    float m = (sin(time * 2.0f)) * 0.5f + 0.5f;
    glm::vec3 col = PaletteCosinka(m);
    glm::vec3 col2 = PaletteCosinka(std::fmod(time, 1.0));
    float rot = std::fmod(time, 360.0f);
    sendTask(
        std::make_unique<task_SmgcPushObject>(
            std::make_unique<Object>(
                glm::vec4{1.0f, m, m, 0.75f},
                glm::vec4{0.5f, 0.0f, 0.0f, 0.0f},
                glm::vec4{col.x, col.y, col.z, 1.0f},
                glm::vec4{0.0f, 0.0f, 0.0f, 0.0f}
            )
        ),
        "SMGC"
    );
    for (int i = -2; i < 2; i += 2) {
        sendTask(
            std::make_unique<task_SmgcPushObject>(
                std::make_unique<Object>(
                    glm::vec4{2.0f, float(i), 0.0f, 2.25f},
                    glm::vec4{0.5f, 0.0f, 0.0f, 0.0f},
                    glm::vec4{col2.x, col2.y, col2.z, 1.0f},
                    glm::vec4{rot, rot, rot, 0.0f}
                )
            ),
            "SMGC"
        );
    }
    sendTask(
        std::make_unique<task_SmgcPushObject>(
            std::make_unique<Object>(
                glm::vec4{3.0f, 0.0f, 0.75f, 3.75f},
                glm::vec4{0.5f, 0.0f, 0.0f, 1.0f},
                glm::vec4{col2.x, col2.y, col2.z, 1.0f},
                glm::vec4{rot, rot, rot, 0.0f}
            )
        ),
        "SMGC"
    );
    sendTask(
        std::make_unique<task_SmgcPushObject>(
            std::make_unique<Object>(
                glm::vec4{-1.0f, 0.0f, 0.0f, -0.75f},
                glm::vec4{0.5f, 0.0f, 0.0f, 0.0f},
                glm::vec4{0.75f, 0.75f, 0.75f, 1.0f},
                glm::vec4{0.0f, 0.0f, 0.0f, 0.0f}
            )
        ),
        "SMGC"
    );
    sendTask(
        std::make_unique<task_SmgcPushObject>(
            std::make_unique<Object>(
                glm::vec4{-2.0f, 0.0f, 0.0f, -2.25f},
                glm::vec4{0.5f, 0.0f, 0.0f, 0.0f},
                glm::vec4{1.0f, 1.0f, 0.4f, 1.0f},
                glm::vec4{0.0f, 0.0f, 0.0f, 0.0f}
            )
        ),
        "SMGC"
    );
    
    sendTask(std::make_unique<task_SmgcSwapObjects>(), "SMGC");
    return 0;
}