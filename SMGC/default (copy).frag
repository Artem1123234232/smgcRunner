#version 460 core
out vec4 fragColor;

uniform float iTime;
uniform vec2 iResolution;

void main() {
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = gl_FragCoord.xy / iResolution.xy;

    // Time varying pixel color
    vec3 col = vec3(0.0, 0.5, 1.0);//0.5 + 0.5*cos(iTime+uv.xyx+vec3(0,2,4));

    //col *= sqrt(pow(uv.x - 0.5, 2.0) + pow(uv.y - 0.5, 2.0));

    float wave = sin((uv.x - iTime * 0.25) * 3.14 * 15.0) * 0.025 + 0.5;
    col = mix(col, vec3(0.9, 0.9, 0.9), step(uv.y, wave));
    col = mix(col, vec3(0.0, 0.3, 1.0), step(uv.y + 0.01, wave));

    // Output to screen
    fragColor = vec4(col,1.0);
}