#pragma once
#include "Random.hpp"
#include "Quad.hpp"

class Apple {
public:
    static Quad apple;
    static GLfloat horizontalPosition;
    static GLfloat verticalPosition;

public:
    static void create() {
        horizontalPosition = Random::getReal(-1.0f, 0.9f);
        verticalPosition = Random::getReal(-1.0f, 0.9f);
        apple.make(horizontalPosition, verticalPosition, 183, 28, 28);
    }

    static bool checkCollision(const Quad& quad) {
        auto[quadHorizontalPosition, quadVerticalPosition] = quad.getPosition();

        return
            ((quadHorizontalPosition >= horizontalPosition - 0.09f) && (quadHorizontalPosition <= horizontalPosition + 0.09f))
            && ((quadVerticalPosition >= verticalPosition - 0.09f) && (quadVerticalPosition <= verticalPosition + 0.09f));
    }
};
