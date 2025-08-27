#include "Quad.h"

#include "Game.h"
#include "shader_utils.h"

#include <algorithm>

Quad::Quad(const Params& params)
    : width(params.width)
    , height(params.height)
    , posX(params.posX)
    , posY(params.posY)
    , lastX(posX)
    , lastY(posY)
    , colors(params.colors)
    , vertexShader(params.vertexShader)
    , fragmentShader(params.fragmentShader)
{
    initBuffers();

    shaderProgramHandle = compileProgram({
        { GL_VERTEX_SHADER, vertexShader },
        { GL_FRAGMENT_SHADER, fragmentShader },
    });
}

Quad::~Quad()
{
    glDeleteBuffers(1, &vboHandle);
    glDeleteBuffers(1, &eboHandle);
    glDeleteVertexArrays(1, &vaoHandle);
    glDeleteProgram(shaderProgramHandle);
}

void Quad::update(float dt)
{
}

void Quad::render(float aspectRatio, float alpha)
{
    glBindVertexArray(vaoHandle);
    glUseProgram(shaderProgramHandle);

    const GLuint scaleLoc = glGetUniformLocation(shaderProgramHandle, "uScale");
    glUniform2f(scaleLoc, width, height);

    // Interpolate position
    const GLuint offsetLoc = glGetUniformLocation(shaderProgramHandle, "uOffset");
    const float smoothX = posX * alpha + lastX * (1 - alpha);
    const float smoothY = posY * alpha + lastY * (1 - alpha);
    glUniform2f(offsetLoc, smoothX, smoothY);

    const GLuint aspectLoc = glGetUniformLocation(shaderProgramHandle, "uAspect");
    glUniform1f(aspectLoc, aspectRatio);

    const GLuint worldSizeLoc = glGetUniformLocation(shaderProgramHandle, "uWorldSize");
    glUniform2f(worldSizeLoc, Game::WIDTH, Game::HEIGHT);

    // Reset last position, otherwise it trembles on no movement
    lastX = posX;
    lastY = posY;

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glUseProgram(0);
    glBindVertexArray(0);
}

void Quad::move(float dx, float dy)
{
    lastX = posX;
    lastY = posY;
    posX += dx;
    posY += dy;
}

std::array<float, 2> Quad::distanceFrom(const Quad& other) const
{
    const float distanceX = std::abs(posX - other.posX) - (width + other.width) / 2.0;
    const float distanceY = std::abs(posY - other.posY) - (height + other.height) / 2.0;

    return { distanceX, distanceY };
}

void Quad::resolveCollisionWith(const Quad& other, const std::array<float, 2>& distance)
{
    const auto& [distX, distY] = distance;

    // Check if the quads are actually colliding
    if (distX > 0.0f || distY > 0.0f) return;

    // Push self outside of the other quad
    posX += posX > other.posX ? distX : -distX;
    posY += posY > other.posY ? distY : -distY;
}


void Quad::initBuffers()
{
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);

    constexpr unsigned int positionAttributes = 2;
    constexpr unsigned int colorAttributes = 3;
    constexpr unsigned int attributes = positionAttributes + colorAttributes;
    float vertices[][attributes] = {
        // posX,  posY,     r,            g,            b
        { -0.5f, -0.5f,     colors.bl[0], colors.bl[1], colors.bl[2] },
        {  0.5f, -0.5f,     colors.br[0], colors.br[1], colors.br[2] },
        {  0.5f,  0.5f,     colors.tr[0], colors.tr[1], colors.tr[2] },
        { -0.5f,  0.5f,     colors.tl[0], colors.tl[1], colors.tl[2] },
    };
    glGenBuffers(1, &vboHandle);
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(
        /* location */              0,
        /* number of elements */    positionAttributes,
        /* type of elements */      GL_FLOAT,
        /* normalize */             GL_FALSE,
        /* stride (vertex size) */  sizeof(*vertices),
        /* attribute offset */      (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(
        /* location */              1,
        /* number of elements */    colorAttributes,
        /* type of elements */      GL_FLOAT,
        /* normalize */             GL_FALSE,
        /* stride (vertex size) */  sizeof(*vertices),
        /* attribute offset */      (void*)(positionAttributes * sizeof(**vertices)));
    glEnableVertexAttribArray(1);

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,
    };
    glGenBuffers(1, &eboHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Unbind vbo and vao, to allow later reuse without conflicts
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
