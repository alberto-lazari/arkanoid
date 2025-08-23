#include "Paddle.h"

#include "shader_utils.h"

Paddle::Paddle(float x, float y)
    : posX(x)
    , posY(y)
{
    initBuffers();

    // Minimal shaders for rendering a solid color
    shaderProgramHandle = compileProgram({
        {
            GL_VERTEX_SHADER, R"glsl(
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
            )glsl"
        },
        {
            GL_FRAGMENT_SHADER, R"glsl(
                #version 330 core
                in vec3 vColor;
                out vec4 fragColor;

                void main()
                {
                    fragColor = vec4(vColor, 1.0);
                }
            )glsl"
        },
    });
}

Paddle::~Paddle()
{
    glDeleteBuffers(1, &vboHandle);
    glDeleteBuffers(1, &eboHandle);
    glDeleteVertexArrays(1, &vaoHandle);
    glDeleteProgram(shaderProgramHandle);
}

void Paddle::render(float aspectRatio)
{
    glBindVertexArray(vaoHandle);

    glUseProgram(shaderProgramHandle);
    const GLuint scaleLoc = glGetUniformLocation(shaderProgramHandle, "uScale");
    const GLuint offsetLoc = glGetUniformLocation(shaderProgramHandle, "uOffset");
    const GLuint aspectLoc = glGetUniformLocation(shaderProgramHandle, "uAspect");
    glUniform2f(scaleLoc, width, height);
    glUniform2f(offsetLoc, posX, posY);
    glUniform1f(aspectLoc, aspectRatio);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glUseProgram(0);
    glBindVertexArray(0);
}

void Paddle::initBuffers()
{
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);

    constexpr unsigned int positionAttributes = 2;
    constexpr unsigned int colorAttributes = 3;
    constexpr unsigned int attributes = positionAttributes + colorAttributes;
    float vertices[][attributes] = {
        // posX,  posY,     r,    g,    b
        { -0.5f, -0.5f,     0.4f, 0.4f, 0.4f },
        {  0.5f, -0.5f,     0.4f, 0.4f, 0.4f },
        {  0.5f,  0.5f,     0.9f, 0.9f, 0.9f },
        { -0.5f,  0.5f,     0.9f, 0.9f, 0.9f },
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

    // Unbind vbo and vao, to allow potential reuse without conflicts
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
