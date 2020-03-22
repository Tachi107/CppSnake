#pragma once
#include <glad/glad.h>
#include <vector>

struct VertexBufferElement {
    GLuint type;
    GLint count;

    static inline GLsizei sizeOfGlType(const GLuint type) {
        switch (type) {
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_INT:   return 4;
            case GL_UNSIGNED_BYTE:  return 1;
            case GL_INT:            return 4;
            case GL_BYTE:           return 1;
            case GL_SHORT:          return 2;
            case GL_UNSIGNED_SHORT: return 2;
        }
        return 0;
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> elements;
    GLsizei stride = 0;

public:
    void add(const GLint count, const GLuint glType) {
        elements.push_back({glType, count});
        stride += count * VertexBufferElement::sizeOfGlType(glType);
    }

    inline const std::vector<VertexBufferElement>& getElements() const { return elements; }
    inline GLsizei getStride() const { return stride; }
};
