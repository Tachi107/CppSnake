#pragma once
#define GLFW_INCLUDE_NONE
#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>
#include "Quad.hpp"

/*
 * La classe è statica in quanto la funzione key_callback dev'essere passata in glfwSetKeyCallback
 * attraverso un normale function pointer. Se non fosse statica, non potrei farlo, in quanto
 * un metodo è effettivamente diverso da una funzione normale, e il suo function pointer
 * contiene dei riferimenti all'istanza della classe, rendendo il puntatore diverso e negandomi
 * la possibilità di passare la funzione in glfwSetKeyCallback.
 */
class Snake {
private:
	enum directions {
		UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3
	};

private:
	static uint8_t direction;
	static uint8_t previousDirection;
	static std::vector<GLfloat> horizontalPositions;
    static std::vector<GLfloat> verticalPositions;
    static size_t length;
    static GLubyte r, g, b;
    static GLubyte rIncrement, gIncrement, bIncrement;
public:
	static std::vector<Quad> snake;
    static uint8_t score;

public:
    static void key_callback(GLFWwindow* /*window*/, int key, int /*scancode*/, int action, int /*mods*/) {
        if (key == GLFW_KEY_W && action == GLFW_PRESS) {
            direction = directions::UP;
        }
        else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
            direction = directions::RIGHT;
        }
        else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
            direction = directions::DOWN;
        }
        else if (key == GLFW_KEY_A && action == GLFW_PRESS) {
            direction = directions::LEFT;
        }
    }

    static void create() {
        snake.reserve(500);
        snake.emplace_back();
        horizontalPositions.push_back(0);
        verticalPositions.push_back(0);
        ++length;
        r = 255; g = 128; b = 0;
        rIncrement = 5; gIncrement = 5; bIncrement = 5;
    }

    static void create(GLubyte red, GLubyte green, GLubyte blue) {
        snake.reserve(500);
        snake.emplace_back();
        horizontalPositions.push_back(0);
        verticalPositions.push_back(0);
        ++length;
        r = red; g = green; b = blue;
        rIncrement = 5; gIncrement = 5; bIncrement = 5;
    }

    static void addQuad() {
        for (uint8_t i = 0; i < 10; ++i) {
            snake.emplace_back();
            horizontalPositions.push_back(horizontalPositions[length - 1]);
            verticalPositions.push_back(verticalPositions[length - 1]);
            ++length;
        }
        ++score;
    }

    static void checkMove() {
        if ((direction == directions::UP) && (previousDirection != directions::DOWN)) {
            previousDirection = directions::UP;     // Non tocco 0 perché il primo quad va modificato diversamente
            for (size_t i = snake.size() - 1; i > 0; --i) {
                horizontalPositions[i] = horizontalPositions[i - 1];
                verticalPositions[i] = verticalPositions[i - 1];
                snake[i].make(horizontalPositions[i], verticalPositions[i], r, g, b);
            }
            verticalPositions.front() += 0.01f;
            snake.front().make(horizontalPositions.front(), verticalPositions.front(), r, g, b);
        }
        else if ((direction == directions::RIGHT) && (previousDirection != directions::LEFT)) {
            previousDirection = directions::RIGHT;
	        for (size_t i = snake.size() - 1; i > 0; --i) {
	            horizontalPositions[i] = horizontalPositions[i - 1];
                verticalPositions[i] = verticalPositions[i - 1];
	            snake[i].make(horizontalPositions[i], verticalPositions[i], r, g, b);
	        }
	        horizontalPositions.front() += 0.01f;
	        snake.front().make(horizontalPositions.front(), verticalPositions.front(), r, g, b);
        }
        else if ((direction == directions::DOWN) && (previousDirection != directions::UP)) {
            previousDirection = directions::DOWN;
            for (size_t i = snake.size() - 1; i > 0; --i) {
                horizontalPositions[i] = horizontalPositions[i - 1];
                verticalPositions[i] = verticalPositions[i - 1];
                snake[i].make(horizontalPositions[i], verticalPositions[i], r, g, b);
            }
	        verticalPositions.front() -= 0.01f;
	        snake.front().make(horizontalPositions.front(), verticalPositions.front(), r, g, b);
        }
        else if ((direction == directions::LEFT) && (previousDirection != directions::RIGHT)) {
            previousDirection = directions::LEFT;
            for (size_t i = snake.size() - 1; i > 0; --i) {
                horizontalPositions[i] = horizontalPositions[i - 1];
                verticalPositions[i] = verticalPositions[i - 1];
                snake[i].make(horizontalPositions[i], verticalPositions[i], r, g, b);
            }
	        horizontalPositions.front() -= 0.01f;
	        snake.front().make(horizontalPositions.front(), verticalPositions.front(), r, g, b);
        }
    }

    static bool checkCollision() {
        for (size_t i = 10; (i < snake.size()) && (score > 1); i += 10) {
            if ((((horizontalPositions.front() >= horizontalPositions[i] - 0.0599999f)   //È orribile ma non so come fare
                && (horizontalPositions.front() <= horizontalPositions[i] + 0.0599999f))
                &&
                ((verticalPositions.front() >= verticalPositions[i] - 0.0499999f)
                && (verticalPositions.front() <= verticalPositions[i] + 0.0499999f)))
                ||
                (horizontalPositions.front() > 0.9f || horizontalPositions.front() < -1.0f)
                || (verticalPositions.front() > 0.9f || verticalPositions.front() < -1.0f))
                    return true;
        }
        return false;
    }

    static void RGB() {
        if (r >= 255)
            rIncrement = -5;
        else if (r <= 0)
            rIncrement = 5;
        r += rIncrement;

        if (g >= 255)
            gIncrement = -5;
        else if (g <= 0)
            gIncrement = 5;
        g += gIncrement;

        if (b >= 255)
            bIncrement = -5;
        else if (b <= 0)
            bIncrement = 5;
        b += bIncrement;
    }
};

/*
 * Per creare il serpente mi servono le coordinate dei quadrati
 */

/*
 * Ok, disegnare ogni quadrato in singoli frame, e quindi singole draw call,
 * non funziona particolarmente bene, perché per ogni nuovo quadrato
 * si divide la velocità del serpente (e comunque non risolve il problema)
 *
 * Posso fare che modifico la posizione di ogni blocco durante ogni frame,
 * ma in modo indipendente.
 * Se un blocco è alto 0.1, ogni blocco sarà in ritardo rispetto
 * al precedente di 10 frame (0.1 / 0.01).
 * Quindi se il primo blocco cambia direzione, ovvero
 * la sua posizione verticale smette di aumentare e quella orizzontale
 * inizia ad aumentare, il secondo blocco dovrà continuare ad aumentare
 * la vecchia posizione per 10 frame prima di iniziare
 * ad aumentare la nuova.
 * Quando il primo blocco cambia direzione,
 */
/*
 * Souluzione by Lobi
 * Posso shiftare le posizioni così che ogni blocco
 * occupi la posizione del blocco precedente.
 * Magari tipo che a ogni frame cambio la posizione di solo il primo blocco
 * (quello che l'utente controlla) e in un ciclo faccio assumere
 * ad ogni blocco la posizione del blocco precedente
 */
