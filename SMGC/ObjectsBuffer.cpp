#include "ObjectsBuffer.h"

ObjectsBuffer::ObjectsBuffer() {
    glGenBuffers(1, &ID);
}

void ObjectsBuffer::Upload(const std::vector<Object>& objects) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ID);

    const size_t needed = sizeof(Object) * objects.size();

    if (needed == capacityBytes && needed > 0) {
        // Размер тот же — просто перезаписываем
        glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, needed, objects.data());
    } else {
        // Размер изменился (или буфер ещё пустой) — переаллокация
        glBufferData(GL_SHADER_STORAGE_BUFFER,
                     needed,
                     objects.empty() ? nullptr : objects.data(),
                     GL_DYNAMIC_DRAW);
        capacityBytes = needed;
    }

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
void ObjectsBuffer::Bind(int bind) {
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bind, ID);
}
void ObjectsBuffer::Delete() {
    glDeleteBuffers(1, &ID);
}