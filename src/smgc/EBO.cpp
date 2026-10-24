#include <smgc/EBO.h>

EBO::EBO() {
    glGenBuffers(1, &ID);
}

void EBO::Upload(const std::vector<GLuint>& indices) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

    const size_t needed = sizeof(GLuint) * indices.size();

    if (needed == capacityBytes && needed > 0) {
        // Размер тот же — просто перезаписываем
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, needed, indices.data());
    } else {
        // Размер изменился (или буфер ещё пустой) — переаллокация
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     needed,
                     indices.empty() ? nullptr : indices.data(),
                     GL_DYNAMIC_DRAW);
        capacityBytes = needed;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Bind()   { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); }
void EBO::Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
void EBO::Delete() { glDeleteBuffers(1, &ID); }