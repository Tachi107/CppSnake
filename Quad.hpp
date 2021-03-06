#pragma once
#include "Vertex.hpp"
#include <utility>

struct Quad {
    Vertex vertices[4];

    /*
     * This function creates a quad using the coordinates at the bottom left as the starting point,
     * and then defining the coordinates of the other three vertices by moving a little away from that point
     */
    void make(const GLfloat x, const GLfloat y) {
        vertices[0].setPosition(x, y);
        vertices[1].setPosition(x + 0.1f, y);
        vertices[2].setPosition(x + 0.1f, y + 0.1f);
        vertices[3].setPosition(x, y + 0.1f);
        
        setColor(255, 128, 0);
    }

    void make(const GLfloat x, const GLfloat y, const GLubyte r, const GLubyte g, const GLubyte b) {
        vertices[0].setPosition(x, y);
        vertices[1].setPosition(x + 0.1f, y);
        vertices[2].setPosition(x + 0.1f, y + 0.1f);
        vertices[3].setPosition(x, y + 0.1f);

        setColor(r, g, b);
    }

    void setColor(GLubyte r, GLubyte g, GLubyte b) {
        for (Vertex& vertex : vertices)
            vertex.setColor(r, g, b);
    }

    std::pair<GLfloat, GLfloat> getPosition() const {
        return std::make_pair(vertices[0].positions[0], vertices[0].positions[1]);
    }
};
