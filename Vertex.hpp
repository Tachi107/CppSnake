#pragma once
#include <glad/glad.h>

struct Vertex {
    static constexpr GLubyte positionCount = 2;
    static constexpr GLubyte colorCount = 4;    //Per forza 4 byte perché sennò ho problemi di allineamento della memoria
    GLfloat positions[positionCount];
    GLubyte colors[colorCount];                 // Potrei usare #pragma pack(1)?

    void setPosition(const GLfloat x, const GLfloat y) {
        positions[0] = x;
        positions[1] = y;
    }

    void setColor(const GLubyte r, const GLubyte g, const GLubyte b) {
        colors[0] = r;
        colors[1] = g;
        colors[2] = b;
    }
};
