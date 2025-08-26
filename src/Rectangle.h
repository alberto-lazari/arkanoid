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

        const char* vertexShader = R"glsl(
            #version 330 core
            layout(location = 0) in vec2 aPos;
            layout(location = 1) in vec3 aColor;
            out vec3 vColor;

            uniform vec2 uScale;
            uniform vec2 uOffset;
            uniform float uAspect;

            void main()
            {
                vec2 scaledPos = aPos * uScale;
                scaledPos.x /= uAspect;
                gl_Position = vec4(scaledPos + uOffset, 0.0, 1.0);

                vColor = aColor;
            }
        )glsl";
        const char* fragmentShader = R"glsl(
            #version 330 core
            in vec3 vColor;
            out vec4 fragColor;

            void main()
            {
                fragColor = vec4(vColor, 1.0);
            }
        )glsl";
    };

    Rectangle(const Params& params);
    ~Rectangle();

    constexpr float getPosWidth() { return width; }
    constexpr float getPosHeight() { return height; }
    constexpr float getPosX() { return posX; }
    constexpr float getPosY() { return posY; }

    void update(float dt);
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

    const char* vertexShader;
    const char* fragmentShader;

    void initBuffers();
};
