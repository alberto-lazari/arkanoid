#pragma once

#include <glad/glad.h>
#include <vector>

struct Shader
{
    GLenum type;
    const char* source;
};

/**
 * Compiles and links a program from an arbitrary list of shaders.
 * @return program handle on compilation success, 0 otherwise.
 */
GLuint compileProgram(const std::vector<Shader>& shaders);
