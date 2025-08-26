#pragma once

#include <glad/glad.h>

class Rectangle
{
public:
    struct Colors
    {
        float tl[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        float tr[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        float bl[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        float br[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    };

    struct Params
    {
        float width = 0.5f;
        float height = 0.25f;

        float posX = 0.0f;
        float posY = 0.0f;

        Colors colors;
    };

    Rectangle(const Params& params);
    ~Rectangle();

    constexpr float getPosWidth() { return width; }
    constexpr float getPosHeight() { return height; }
    constexpr float getPosX() { return posX; }
    constexpr float getPosY() { return posY; }

    void render(float aspectRatio, float alpha);

    void move(float dx)
    {
        lastX = posX;
        posX += dx;
    }
    void setPosition(float x) { lastX = posX = x; }

private:
    // Vertex Buffer Object (vertices used by the rectangle)
    GLuint vboHandle = 0;
    // Element Buffer Object (triangles that create the rectangle)
    GLuint eboHandle = 0;
    // Vertex Array Object (array of vertex buffers)
    GLuint vaoHandle = 0;

    GLuint shaderProgramHandle = 0;

    float width;
    float height;

    float posX;
    // Previous x position for interpolation
    float lastX;
    float posY;

    Colors colors;

    void initBuffers();
};
