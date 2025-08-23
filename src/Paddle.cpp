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
                uniform vec2 uScale;
                uniform vec2 uOffset;
                uniform float uAspect;

                void main()
                {
                    vec2 scaledPos = aPos * uScale;
                    scaledPos.x /= uAspect;
                    gl_Position = vec4(scaledPos + uOffset, 0.0, 1.0);
                }
            )glsl"
        },
        {
            GL_FRAGMENT_SHADER, R"glsl(
                #version 330 core
                out vec4 FragColor;

                void main()
                {
                    FragColor = vec4(0.7, 0.7, 0.7, 1.0);
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

    float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f,
    };
    glGenBuffers(1, &vboHandle);
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,
    };
    glGenBuffers(1, &eboHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
