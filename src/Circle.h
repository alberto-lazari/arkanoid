#pragma once

#include "Quad.h"

#include <memory>

class Circle : public Quad
{
public:
    struct Params
    {
        float ray = 0.07f;

        float posX = 0.0f;
        float posY = 0.0f;

        Colors colors;

        const char* fragmentShader = R"glsl(
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
        )glsl";
    };

    Circle(const Params& params);

    constexpr float getRay() const { return getWidth() / 2.0f; }
};
