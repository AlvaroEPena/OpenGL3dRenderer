#ifndef CUBE_H
#define CUBE_H

#include "Primitive.h"

class Cube : public Primitive {
public:
    Cube() { build(); }

    void build() override {
        vertices = {
			// Front face
			{{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 2.0f / 3.0f}, {0.0f, 0.0f, 1.0f}}, // top left
			{{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f / 3.0f}, {0.0f, 0.0f, 1.0f}}, // bottom left
			{{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.25f, 1.0f / 3.0f}, {0.0f, 0.0f, 1.0f}}, // bottom right
			{{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.25f, 2.0f / 3.0f}, {0.0f, 0.0f, 1.0f}}, // top right

			// Back face
			{{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.5f, 2.0f / 3.0f}, {0.0f, 0.0f, -1.0f}}, // top right
			{{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.5f, 1.0f / 3.0f}, {0.0f, 0.0f, -1.0f}}, // bottom right
			{{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.75f, 1.0f / 3.0f}, {0.0f, 0.0f, -1.0f}}, // bottom left
			{{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.75f, 2.0f / 3.0f}, {0.0f, 0.0f, -1.0f}}, // top left

			// Left face
			{{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.75f, 2.0f / 3.0f}, {-1.0f, 0.0f, 0.0f}}, // top left
			{{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.75f, 1.0f / 3.0f}, {-1.0f, 0.0f, 0.0f}}, // bottom left
			{{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f / 3.0f}, {-1.0f, 0.0f, 0.0f}}, // bottom right
			{{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 2.0f / 3.0f}, {-1.0f, 0.0f, 0.0f}}, // top right

			// Right face
			{{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.25f, 2.0f / 3.0f}, {1.0f, 0.0f, 0.0f}}, // top left
			{{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.25f, 1.0f / 3.0f}, {1.0f, 0.0f, 0.0f}}, // bottom left
			{{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.5f, 1.0f / 3.0f}, {1.0f, 0.0f, 0.0f}}, // bottom right
			{{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.5f, 2.0f / 3.0f}, {1.0f, 0.0f, 0.0f}}, // top right

			// Top face
			{{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.25f, 1.0f}, {0.0f, 1.0f, 0.0f}}, // top left
			{{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.25f, 2.0f / 3.0f}, {0.0f, 1.0f, 0.0f}}, // bottom left
			{{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.5f, 2.0f / 3.0f}, {0.0f, 1.0f, 0.0f}}, // bottom right
			{{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.5f, 1.0f}, {0.0f, 1.0f, 0.0f}}, // top right

			// Bottom face
			{{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.25f, 1.0f / 3.0f}, {0.0f, -1.0f, 0.0f}}, // bottom left
			{{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.25f, 0.0f}, {0.0f, -1.0f, 0.0f}}, // top left
			{{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.0f}, {0.0f, -1.0f, 0.0f}}, // top right
			{{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.5f, 1.0f / 3.0f}, {0.0f, -1.0f, 0.0f}}  // bottom right
        };

        indices = {
			0, 1, 2, 2, 3, 0,         // Front face
			4, 5, 6, 6, 7, 4,         // Back face
			8, 9, 10, 10, 11, 8,      // Left face
			12, 13, 14, 14, 15, 12,   // Right face
			16, 17, 18, 18, 19, 16,   // Top face
			20, 21, 22, 22, 23, 20    // Bottom face
        };
    }
};
#endif