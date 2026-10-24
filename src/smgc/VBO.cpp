#include <smgc/VBO.h>

VBO::VBO() {
    glGenBuffers(1, &ID);
}

void VBO::Upload(const std::vector<Vertex>& vertices) {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    const size_t needed = sizeof(Vertex) * vertices.size();
    if (needed == capacityBytes && needed > 0)
        glBufferSubData(GL_ARRAY_BUFFER, 0, needed, vertices.data());
    else {
        glBufferData(GL_ARRAY_BUFFER, needed,
                     vertices.empty() ? nullptr : vertices.data(),
                     GL_DYNAMIC_DRAW);
        capacityBytes = needed;
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Bind()   { glBindBuffer(GL_ARRAY_BUFFER, ID); }
void VBO::Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
void VBO::Delete() { glDeleteBuffers(1, &ID); }