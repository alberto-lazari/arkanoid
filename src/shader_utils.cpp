#include "shader_utils.h"

#include <iostream>

GLuint compileShader(const Shader& shader)
{
    const GLuint handle = glCreateShader(shader.type);
    glShaderSource(handle, 1, &shader.source, nullptr);
    glCompileShader(handle);

    int success;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(handle, 512, nullptr, infoLog);
        std::cerr << "Error compiling " << (
                shader.type == GL_VERTEX_SHADER ? "vertex" :
                shader.type == GL_FRAGMENT_SHADER ? "fragment" :
                shader.type == GL_GEOMETRY_SHADER ? "geometry" :
                // No compute shaders until OpenGL 4.3
                // shader.type == GL_COMPUTE_SHADER ? "compute" :
                 "unknown"
            )
            << " shader:\n" << infoLog << std::endl;

        glDeleteShader(handle);
        return 0;
    }

    return handle;
}

GLuint linkProgram(const std::vector<GLuint>& compiledShaders)
{
    const GLuint programHandle = glCreateProgram();
    for (const GLuint shaderHandle : compiledShaders)
    {
        if (shaderHandle) glAttachShader(programHandle, shaderHandle);
    }

    glLinkProgram(programHandle);

    int success;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(programHandle, 512, nullptr, infoLog);
        std::cerr << "Program linking failed:\n" << infoLog << std::endl;

        // Cleanup shaders
        for (const GLuint handle : compiledShaders)
        {
            glDeleteShader(handle);
        }

        glDeleteProgram(programHandle);
        return 0;
    }

    // Once linked, shader objects are no longer needed
    for (const GLuint handle : compiledShaders)
    {
        glDeleteShader(handle);
    }

    return programHandle;
}

GLuint compileProgram(const std::vector<Shader>& shaders)
{
    std::vector<GLuint> compiledShaders;

    // Compile each shader
    for (const Shader& shader : shaders)
    {
        const GLuint handle = compileShader(shader);
        if (!handle) return 0;
        compiledShaders.push_back(handle);
    }

    return linkProgram(compiledShaders);
}
