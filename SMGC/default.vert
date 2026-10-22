#version 460 core
layout (location = 0) in vec3 aPos;

uniform float iTime;

void main() {
    gl_Position = vec4(aPos.xy * (sin(iTime) * 0.5 + 0.5), aPos.z, 1.0);
}