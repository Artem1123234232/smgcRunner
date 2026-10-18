#version 460 core
out vec4 fragColor;

uniform float iTime;
uniform vec2 iResolution;

struct Object {
    vec4 data1;
    vec4 data2;
    vec4 data3;
};

layout(std430, binding = 0) buffer ObjectsBuffer {
    Object items[];
} ObjectsData;

float circle(vec2 uv, vec2 p, float r) {
    vec2 l = vec2(uv.x, 1.0 - uv.y) - p;
    return step(pow(r, 2.0), dot(l, l));
}

void main() {
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = gl_FragCoord.xy / iResolution.xy;

    // Data varying pixel color
    vec3 col = vec3(0.0, 0.0, 0.0);
    
    for (int i = 0; i < ObjectsData.items.length(); ++i) {
        vec4 baseCol = ObjectsData.items[i].data3;
        col = mix(baseCol.rgb, col, circle(uv, vec2(0.5), 0.5));
    }


    // Output to screen
    fragColor = vec4(col,1.0);
}