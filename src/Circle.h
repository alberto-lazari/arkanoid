#pragma once

#include "Quad.h"

#include <memory>

class Circle : public Quad
{
public:
    static constexpr Quad::Params DEFAULT_QUAD_PARAMS = {
        .width = 0.08f,
        .height = 0.08f,
        .posY = 0.0f,
        .posX = -0.5f,
        .colors = {
            .tl = { 1.0f, 1.0f, 1.0f, 1.0f },
            .tr = { 0.7f, 0.7f, 0.7f, 1.0f },
            .bl = { 0.5f, 0.6f, 0.6f, 1.0f },
            .br = { 0.3f, 0.3f, 0.3f, 1.0f },
        },
        .vertexShader = R"glsl(
            #version 330 core
            layout(location = 0) in vec2 aPos;
            layout(location = 1) in vec3 aColor;
            out vec2 vPos;
            out vec3 vColor;

            uniform vec2 uScale;
            uniform vec2 uOffset;
            uniform float uAspect;

            void main()
            {
                vPos = aPos;

                vec2 scaledPos = aPos * uScale;
                scaledPos.x /= uAspect;
                gl_Position = vec4(scaledPos + uOffset, 0.0, 1.0);

                vColor = aColor;
            }
        )glsl",
        .fragmentShader = R"glsl(
            #version 330 core
            in vec2 vPos;
            in vec3 vColor;
            out vec4 fragColor;

            void main()
            {
                float r = length(vPos);
                // Discard outside circle
                if (r > 0.5) discard;

                fragColor = vec4(vColor, 1.0);
            }
        )glsl",
    };

    Circle(const Params& quadParams = DEFAULT_QUAD_PARAMS);
};
