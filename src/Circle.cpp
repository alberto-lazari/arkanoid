#include "Circle.h"

#include "shader_utils.h"

Circle::Circle(const Params& params)
    : Quad({
        .width = params.ray * 2.0f,
        .height = params.ray * 2.0f,
        .posX = params.posX,
        .posY = params.posY,
        .colors = params.colors,
        .shaderProgramHandle = getShaderProgramHandle(),
    })
{
}

GLuint Circle::getShaderProgramHandle()
{
    static GLuint handle = 0;
    if (!handle)
    {
        handle = compileProgram({
            { GL_VERTEX_SHADER, Quad::VERTEX_SHADER },
            { GL_FRAGMENT_SHADER, Circle::FRAGMENT_SHADER },
        });
    }

    return handle;
}
