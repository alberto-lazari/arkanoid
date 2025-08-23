#pragma once

#include <glad/glad.h>

class Paddle
{
public:
    Paddle(float x = 0.0f, float y = -0.9f);
    ~Paddle();

    void render(float aspectRatio);

    void move(float dx) { posX += dx; }
    void setPosition(float x) { posX = x; }

private:
    // Vertex Buffer Object (vertices used by the paddle)
    GLuint vboHandle = 0;
    // Element Buffer Object (triangles that create the paddle)
    GLuint eboHandle = 0;
    // Vertex Array Object (array of vertex buffers)
    GLuint vaoHandle = 0;

    GLuint shaderProgramHandle = 0;

    float width = 0.4f;
    float height = 0.05f;

    float posX;
    float posY;

    void initBuffers();
};
