#include "Renderer.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>
#include <algorithm>
#include "Snake.hpp"
#include "Quad.hpp"
#include "Apple.hpp"

GLFWwindow* initGl(const int width, const int height, const char* const title) {
    if (!glfwInit())
        return nullptr;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);    // V-sync
    if (glewInit())
        return nullptr;
    return window;
}

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    std::cerr << std::hex << (type == GL_DEBUG_TYPE_ERROR ? "ERROR: " : "WARNING: ") << "type: 0x" << type
              << ", severity: 0x" << severity << ", " << message << std::endl;
}

void enableGlDebug() {
    std::cout << glGetString(GL_VERSION) << std::endl;
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, nullptr);
}

// Declaring static variables in this cpp unit
uint8_t Snake::direction;
uint8_t Snake::previousDirection;
std::vector<GLfloat> Snake::horizontalPositions;
std::vector<GLfloat> Snake::verticalPositions;
std::vector<Quad> Snake::snake;
size_t Snake::length;
uint8_t Snake::score;
Quad Apple::apple;
GLfloat Apple::horizontalPosition;
GLfloat Apple::verticalPosition;
GLubyte Snake::r, Snake::g, Snake::b;
GLubyte Snake::rIncrement, Snake::gIncrement, Snake::bIncrement;


int main() {
	GLFWwindow* window = initGl(720, 720, "CppSnake");
    if (window == nullptr)
        return EXIT_FAILURE;
    //enableGlDebug();

    constexpr GLsizei maxQuads = 2000;
    constexpr GLsizei maxVertices = 4 * maxQuads;
    constexpr GLsizei maxIndices = 6 * maxQuads;



	
	DynamicVertexBuffer dynVertexBuffer(maxVertices * sizeof(Vertex));

	VertexBufferLayout layout;
    layout.add(Vertex::positionCount, GL_FLOAT);
    layout.add(Vertex::colorCount, GL_UNSIGNED_BYTE);

	VertexArray vertexArray;
	vertexArray.addBuffer(dynVertexBuffer, layout);

    // Indices necessary to draw all triangles making the quads
    std::array<GLuint, maxIndices> indices = IndexBuffer::genIndices<maxIndices>();
	IndexBuffer indexBuffer(indices);

	Shader shader("./res/vertex.shader", "./res/fragment.shader");
	shader.bind();

	Renderer::setClearColor(static_cast<GLubyte>(22), 22, 22);

	Snake::create();
	Apple::create();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		Renderer::clear();

		Snake::checkMove();

		std::vector<Quad> data;
		data.reserve(Snake::snake.size() + 1);  // 1 is the number of apples
		data.insert(data.end(), Snake::snake.begin(), Snake::snake.end());
		data.insert(data.end(), Apple::apple);
		dynVertexBuffer.setData(data);

		if (Apple::checkCollision(Snake::snake.front())) {
            Apple::create();
		    Snake::addQuad();
		}

		if (Snake::checkCollision())
		    glfwSetWindowShouldClose(window, GLFW_TRUE);

        if (Snake::score == 107)
            Snake::RGB();

		Renderer::draw(vertexArray, indexBuffer, shader);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
		glfwSetKeyCallback(window, Snake::key_callback);
	}
	std::cout << "Punteggio: " << static_cast<short>(Snake::score) << std::endl;
	glfwTerminate();
}
/*
 * To compile:
 * g++ $(pkg-config --cflags glfw3 gl) main.cpp -o main $(pkg-config --static --libs glfw3 gl) /usr/lib64/libGLEW.a -std=c++17
 */
