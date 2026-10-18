#version 460 core
out vec4 fragColor;

#define ITERATIONS 1000
#define MAX_DISTANCE 50.0
#define EPSILON 0.001

uniform float iTime;
uniform vec2 iResolution;
uniform vec3 iCameraPos;
uniform vec3 iCameraRot;

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

float sphereSDF(float r, vec3 p) {
    return length(p) - r;
}

vec4 map(vec3 p) {
    float d = MAX_DISTANCE;
    vec3 col = vec3(0.0);

    float d1 = abs(p.y + 1.0);
    col = mix(vec3(0.333), col, step(EPSILON, d1));
    d = min(d, d1);

    for (int i = 0; i < ObjectsData.items.length(); ++i) {
        Object obj = ObjectsData.items[i];
        int type = int(round(obj.data1.x));
        vec3 lp = p - obj.data1.yzw;
        vec4 baseCol = obj.data3;
        float dx = MAX_DISTANCE;
        //if (type == 0) {
            dx = sphereSDF(obj.data2.x, lp);
        //}
        //baseCol.a = 0.5;
        col = mix(baseCol.rgb, col, step(EPSILON, dx));
        d = min(d, dx);
    }

    return vec4(col, d);
}

vec3 normal(vec3 p) {
    const vec2 k = vec2(1.0, -1.0);
    return normalize(
        k.xyy * map(p + k.xyy * EPSILON).w +
        k.yyx * map(p + k.yyx * EPSILON).w +
        k.yxy * map(p + k.yxy * EPSILON).w +
        k.xxx * map(p + k.xxx * EPSILON).w
    );
}

float raymarchLight(vec3 ro, vec3 rd) {
    float dO = 0.0;
    float md = 1.0;
    for (int i = 0; i < 20; i++)
    {
        vec3 p = ro + rd * dO;
        float dS = map(p).w;
        md = min(md, dS);
        dO += dS;
        if (dO > 50.0 || dS < 0.1) {
            break;
        }
    }
    return md;
}

float light(vec3 p) {
    vec3 light_pos = vec3(1.0, 2.0, 1.0);
    vec3 l = normalize(light_pos - p);
    vec3 normal = normal(p);
    float lambert = clamp(dot(normal, l) * 0.5 + 0.5, 0.0, 1.0);
    float shadow = clamp(raymarchLight(p + normal, l) + 1.0, 0.0, 1.0);
    return lambert * shadow;
}

vec3 calcColor(vec3 p, vec3 ro, int i, float d) {
    // base color
    vec3 col = map(p).xyz;

    // light
    col *= light(p);

    // ambient occlusion
    col *= pow(1.0 - (float(i) / float(ITERATIONS) * 2.0), 2.0);

    // fog
    float fog = pow(clamp(distance(p, ro) / MAX_DISTANCE, 0.0, 1.0), 2.0);
    col = col * (1.0 - fog) + 0.28 * fog;
    
    return col;
}

vec3 raymarch(vec3 ro, vec3 rd) {
    float total_distance_traveled = 0.0;
    for (int i = 0; i < ITERATIONS; i++)
    {
        vec3 p = ro + total_distance_traveled * rd;
        float d = map(p).w;
        if (total_distance_traveled > MAX_DISTANCE || d < EPSILON) {
            return calcColor(p, ro, i, d);
        }
        total_distance_traveled += d;
    }
    return vec3(0.0);
}

mat3 cameraRotation(vec3 deg) {
    vec3 r = radians(deg);
    float cp = cos(r.x), sp = sin(r.x);   // pitch
    float cy = cos(r.y), sy = sin(r.y);   // yaw
    float cr = cos(r.z), sr = sin(r.z);   // roll

    // ВАЖНО: mat3 в GLSL задаётся ПО СТОЛБЦАМ
    mat3 Rx = mat3(1.0, 0.0, 0.0,
                   0.0,  cp,  sp,
                   0.0, -sp,  cp);

    mat3 Ry = mat3( cy, 0.0, -sy,
                   0.0, 1.0, 0.0,
                    sy, 0.0,  cy);

    mat3 Rz = mat3( cr,  sr, 0.0,
                   -sr,  cr, 0.0,
                   0.0, 0.0, 1.0);

    // порядок применения: сначала yaw, потом pitch, потом roll
    return Rz * Rx * Ry;
}

void main() {
    vec2 uv = (gl_FragCoord.xy - iResolution.xy / 2.0) / min(iResolution.x, iResolution.y);
    vec3 rd = normalize(vec3(uv, 1.0)) * cameraRotation(iCameraRot);

    vec3 col = raymarch(iCameraPos, rd);

    // Output to screen
    fragColor = vec4(col, 1.0);
}