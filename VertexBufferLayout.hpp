#pragma once
#include <glbinding/gl/gl.h>
#include <vector>

using namespace gl;

struct VertexBufferElement {
    GLuint type;
    GLint count;

    static inline GLsizei sizeOfGlType(const GLuint type) {
        switch (type) {
            case static_cast<GLuint>(GL_FLOAT):          return 4;
            case static_cast<GLuint>(GL_UNSIGNED_INT):   return 4;
            case static_cast<GLuint>(GL_UNSIGNED_BYTE):  return 1;
            case static_cast<GLuint>(GL_INT):            return 4;
            case static_cast<GLuint>(GL_BYTE):           return 1;
            case static_cast<GLuint>(GL_SHORT):          return 2;
            case static_cast<GLuint>(GL_UNSIGNED_SHORT): return 2;
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
