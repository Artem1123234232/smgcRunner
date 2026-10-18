#include "shaderClass.h"

static bool checkShader(GLuint shader, const char* name) {
    GLint ok = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[2048];
        glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
        std::cerr << "Shader compile error (" << name << "):\n" << log << "\n";
        return false;
    }
    return true;
}

static bool checkProgram(GLuint prog) {
    GLint ok = 0;
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[2048];
        glGetProgramInfoLog(prog, sizeof(log), nullptr, log);
        std::cerr << "Program link error:\n" << log << "\n";
        return false;
    }
    return true;
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
    status = 0;
    
    auto [vertexCode, errorCode1] = readFile_S(vertexFile);
    if (errorCode1 != 0) {
        std::cerr << "CriticalError in Shader::Shader: readFile_S(\"" << vertexFile << "\") return error code " << std::to_string(errorCode1) << std::endl;
        status = errorCode1;
        return;
    }
    const char* vertexSource = vertexCode.c_str();

    auto [fragmentCode, errorCode2] = readFile_S(fragmentFile);
    if (errorCode2 != 0) {
        std::cerr << "CriticalError in Shader::Shader: readFile_S(\"" << fragmentFile << "\") return error code " << std::to_string(errorCode2) << std::endl;
        status = errorCode2;
        return;
    }
    const char* fragmentSource = fragmentCode.c_str();

    std::clog << "Info in Shader::Shader: fragmentSource = \"\"\"" << fragmentSource << "\"\"\"" << std::endl;
    std::clog << "Info in Shader::Shader: vertexSource = \"\"\"" << vertexSource << "\"\"\"" << std::endl;

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    if (!checkShader(vertexShader, vertexFile)) { status = -EINVAL; return; }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    if (!checkShader(fragmentShader, fragmentFile)) { status = -EINVAL; return; }

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    if (!checkProgram(ID)) { status = -EINVAL; return; }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate() {
    glUseProgram(ID);   
}

void Shader::Delete() {
    glDeleteProgram(ID);
}

int Shader::getStatus() {
    // Get status - error or normal
    return status;
}

void Shader::setVec2(const char* name, float x, float y) {
    GLint loc = glGetUniformLocation(ID, name);
    if (loc == -1) {
        std::cerr << "Error in Shader::setVec2: Uniform " << name << " not found\n";
        return;
    }
    GLint prev = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &prev);
    if (prev != (GLint)ID) glUseProgram(ID);

    glUniform2f(loc, x, y);
}

void Shader::setFloat(const char* name, float x) {
    GLint loc = glGetUniformLocation(ID, name);
    if (loc == -1) {
        std::cerr << "Error in Shader::setFloat: Uniform " << name << " not found\n";
        return;
    }
    GLint prev = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &prev);
    if (prev != (GLint)ID) glUseProgram(ID);

    glUniform1f(loc, x);
}