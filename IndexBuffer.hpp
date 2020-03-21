#pragma once
#include "vendor/glad/include/glad/glad.h"
#include <array>

class IndexBuffer {
private:
    GLuint id;
    GLsizei count;

public:
    IndexBuffer(const GLuint* data, GLsizei count) : count(count) {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
    }

    template<typename type, size_t size>
    IndexBuffer(const std::array<type, size>& indices) : count(indices.size()) {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);
    }

    ~IndexBuffer() {
        glDeleteBuffers(1, &id);
    }

    void bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    static void unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    template<GLsizei size>
    static constexpr std::array<GLuint, size> genIndices() {
        std::array<GLuint, size> indices;
        GLsizei offset = 0;

        for (GLsizei i = 0; i < size; i += 6) {
            indices[i + 0] = 0 + offset;
            indices[i + 1] = 1 + offset;
            indices[i + 2] = 2 + offset;

            indices[i + 3] = 2 + offset;
            indices[i + 4] = 3 + offset;
            indices[i + 5] = 0 + offset;

            offset += 4;
        }
        return indices;
    }

    inline GLsizei getCount() const { return count; };
};
