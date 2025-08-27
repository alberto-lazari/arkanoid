#pragma once

#include <glad/glad.h>

#include <array>

class Quad
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
            out vec2 vPos;
            out vec3 vColor;

            uniform vec2 uScale;
            uniform vec2 uOffset;
            uniform float uAspect;
            uniform vec2 uWorldSize;

            void main()
            {
                vec2 worldPos = aPos * uScale + uOffset;
                float worldScale = 2.0 / min(uWorldSize.x, uWorldSize.y);
                vec2 clipPos = worldPos * worldScale;
                clipPos.x /= uAspect;

                gl_Position = vec4(clipPos, 0.0, 1.0);
                vPos = aPos;
                vColor = aColor;
            }
        )glsl";
        const char* fragmentShader = R"glsl(
            #version 330 core
            in vec2 vPos;
            in vec3 vColor;
            out vec4 fragColor;

            void main()
            {
                fragColor = vec4(vColor, 1.0);
            }
        )glsl";
    };

    Quad(const Params& params);
    ~Quad();

    constexpr float getWidth()  const { return width; }
    constexpr float getHeight() const { return height; }
    constexpr float getPosX()   const { return posX; }
    constexpr float getPosY()   const { return posY; }

    void setPositionX(float x) { lastX = posX = x; }
    void setPositionY(float y) { lastY = posY = y; }

    void update(float dt);
    void render(float aspectRatio, float alpha);

    void move(float dx, float dy);

    /*
     * Distance between two quads on X and Y axis.
     * If distance < 0 it means the quads are overlapping on that axis.
     */
    std::array<float, 2> distanceFrom(const Quad& other) const;

    void resolveCollisionWith(const Quad& other, const std::array<float, 2>& distance);

private:
    // Vertex Buffer Object (vertices used by the quad)
    GLuint vboHandle = 0;
    // Element Buffer Object (triangles that create the quad)
    GLuint eboHandle = 0;
    // Vertex Array Object (array of vertex buffers)
    GLuint vaoHandle = 0;

    GLuint shaderProgramHandle = 0;

    float width;
    float height;

    float posX;
    float posY;

    // Previous position for interpolation
    float lastX;
    float lastY;

    Colors colors;

    const char* vertexShader;
    const char* fragmentShader;

    void initBuffers();
};
