#version 460 core
in vec3 fragPos; // Интерполированная позиция фрагмента
out vec4 fragColor;

uniform float iOutline;
uniform float iMaxDist;

void main() {
    if (iOutline > 0.5) {
        fragColor = vec4(1.0, 0.5, 0.0, 1.0);
        return;
    }

    fragColor = vec4(vec3(1.0 - clamp(length(fragPos) / iMaxDist, 0.0, 1.0)), 1.0);
    return;

    vec3 dx = dFdx(fragPos);
    vec3 dy = dFdy(fragPos);
    
    vec3 normal = normalize(cross(dx, dy));
    
    vec3 light_pos = vec3(1.0, 2.0, 1.0);
    vec3 col = vec3(clamp(dot(normal, normalize(light_pos)) * 0.5 + 0.5, 0.0, 1.0));
    
    fragColor = vec4(col, 1.0);
}