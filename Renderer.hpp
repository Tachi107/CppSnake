#pragma once
#include <GL/glew.h>
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

class Renderer {
public:
    static void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) {
        vertexArray.bind();
        indexBuffer.bind();
        shader.bind();
        // In drawElements devo definire cosa disegnare, in numero di indici che saranno necessari per disegnare i trinagoli, il tipo degli indici e il buffer di essi. Gli do nullptr perché deve partire dall'inizio del buffer boundato - (TheCherno: Gli do nullptr perché non devo specificare cosa deve disegnare, in quanto il buffer degli indici è già selezionato)
        glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
    }

    static void clear() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    static void setClearColor(const GLfloat r, const GLfloat g, const GLfloat b, const GLfloat a) {
        glClearColor(r, g, b, a);
    }

    static void setClearColor(const GLfloat r, const GLfloat g, const GLfloat b) {
        glClearColor(r, g, b, 1.0f);
    }

    static void setClearColor(const GLubyte r, const GLubyte g, const GLubyte b, const GLubyte a) {
        glClearColor(r/255.0f, g/255.0f, b/255.0f, a/255.0f);
    }

    static void setClearColor(const GLubyte r, const GLubyte g, const GLubyte b) {
        glClearColor(r/255.0f, g/255.0f, b/255.0f, 1.0f);
    }
};
