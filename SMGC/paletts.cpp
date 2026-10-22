#include "paletts.h"

glm::vec3 PaletteCosinka(float t) {
    t = std::clamp(t, 0.0f, 1.0f);
    constexpr float TAU = 6.2831853f;
    constexpr float PI  = 3.14159265f;

    // 1) Основная косинусная волна — «скелет» палитры
    glm::vec3 base = 0.5f + 0.5f * glm::cos(
        TAU * (glm::vec3(t) + glm::vec3(0.0f, 0.33f, 0.67f))
    );

    // 2) Вторая волна с другими частотами — интерференция, характер
    glm::vec3 detail = 0.15f * glm::cos(
        TAU * (glm::vec3(2.0f, -2.0f, 3.0f) * t + glm::vec3(0.5f, 0.2f, 0.8f))
    );

    // 3) Мягкий «горб» яркости в середине — цвета в центре сочнее
    float pulse = 0.9f + 0.15f * glm::sin(PI * t);

    return glm::clamp((base + detail) * pulse, 0.0f, 1.0f);
}

glm::vec3 PaletteCosinka2(float t) {
    t = std::clamp(t, 0.0f, 1.0f);
    constexpr float TAU = 6.2831853f;
    constexpr float PI  = 3.14159265f;

    // 1) Основная косинусная волна — «скелет» палитры
    glm::vec3 base = 0.5f + 0.5f * glm::cos(
        TAU * (glm::vec3(t) + glm::vec3(0.666f, 0.333f, 0.0f))
    );

    // 2) Вторая волна с другими частотами — интерференция, характер
    glm::vec3 detail = 0.15f * glm::cos(
        TAU * (glm::vec3(2.0f, -2.0f, 3.0f) * t + glm::vec3(0.333f, 0.666f, 0.333f))
    );

    // 3) Мягкий «горб» яркости в середине — цвета в центре сочнее
    float pulse = 0.9f + 0.15f * glm::sin(PI * t);

    return glm::clamp((base + detail) * pulse, 0.0f, 1.0f);
}