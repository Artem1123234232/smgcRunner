#version 460 core
out vec4 fragColor;

#define MAX_DISTANCE 50.0f

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

float map(vec3 p) {
    return length(p) - 1.0f;
}

vec3 ray_march(vec3 ro, vec3 rd)
{
    vec3 p = vec3(0.0);
    vec3 col = vec3(0.5,0.5,0.5);
    float total_distance_traveled = 0.0;
    bool water = false;
    for (int i = 0; i < 1000; i++)
    {
        p = ro + total_distance_traveled * rd;
        float d = map(p);
        if (total_distance_traveled > MAX_DISTANCE || d < 0.001) {
            break;
        }
        total_distance_traveled += d;
    }
    return p;
}

void main() {
    vec2 uv = (gl_FragCoord.xy - iResolution.xy / 2.0) / min(iResolution.x, iResolution.y);
    vec3 ro = vec3(0.0, 0.0, -5.0);
    vec3 rd = vec3(uv, 1.0);

    vec3 col = vec3(0.0, 0.0, 0.0);
    
    /*for (int i = 0; i < ObjectsData.items.length(); ++i) {
        Object obj = ObjectsData.items[i];
        float type = obj.data1.x;
        vec3 pos = obj.data1.yzw;
        vec4 baseCol = obj.data3;
        col = mix(baseCol.rgb, col, circle(uv, pos.xy, 0.5));
    }*/

    vec3 p = ray_march(ro, rd);
    col = p;


    // Output to screen
    fragColor = vec4(col,1.0);
}