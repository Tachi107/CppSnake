#pragma once
#include <glbinding/gl/gl.h>
#include <array>
#include <vector>

using namespace gl;

class VertexBuffer {
protected:
    GLuint id;

public:
    virtual ~VertexBuffer() {
        glDeleteBuffers(1, &id);
    }

    virtual void bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    static void unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

protected:  // Necessario per non rendere istanziabile VertexBuffer
    VertexBuffer() = default;
};

class StaticVertexBuffer : public VertexBuffer {
public:
    StaticVertexBuffer(const void* data, const GLsizeiptr size) {
        // Genero un buffer e memorizzo il suo id
        glGenBuffers(1, &id);
        // Seleziono il buffer appena creato, e dico che è un buffer array
        glBindBuffer(GL_ARRAY_BUFFER, id);
        // Creo il buffer contenente i dati del triangolo; specifico il tipo, la dimensione in byte, un indirizzo all'array, e come verrà utilizzato il buffer (STATIC significa che viene creato in sola lettura, DYNAMIC che può essere letto e modificato; DRAW perché andrò a disegnare il triangolo)
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    template<typename type, size_t size>
    StaticVertexBuffer(const std::array<type, size>& vertices) {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
    }
};



class DynamicVertexBuffer : public VertexBuffer {
public:
    DynamicVertexBuffer(const GLuint size) {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        // Creo un buffer del quale definisco solo la grandezza. Andrò a riempirlo più tardi
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    template<typename type, size_t size>
    void setData(const std::array<type, size>& vertices) {
        bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices.data());
    }

    void setData(const void* data, const GLsizeiptr size) {
        bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    template<typename type>
    void setData(const std::vector<type>& vertices) {
        bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(type), vertices.data());
    }
};
