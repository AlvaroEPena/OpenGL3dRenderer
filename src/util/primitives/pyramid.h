#ifndef PYRAMID_H
#define PYRAMID_H

#include "Primitive.h"

class Pyramid : public Primitive {
public:
    Pyramid() { build(); }

    void build() override {
        vertices = {
            // Define pyramid vertices (positions, colors, texCoords, normals)
            {{0.f, 0.5f, 0.f}, {1.f, 0.f, 0.f}, {0.5f, 1.f}, {0.f, 1.f, 0.f}},   // Top (index 0)
            {{-0.5f, -0.5f, -0.5f}, {0.f, 1.f, 0.f}, {0.f, 0.f}, {0.f, -1.f, 0.f}},  // Base front-left (index 1)
            {{0.5f, -0.5f, -0.5f}, {0.f, 0.f, 1.f}, {1.f, 0.f}, {0.f, -1.f, 0.f}},   // Base front-right (index 2)
            {{0.5f, -0.5f, 0.5f}, {1.f, 1.f, 0.f}, {1.f, 1.f}, {0.f, -1.f, 0.f}},    // Base back-right (index 3)
            {{-0.5f, -0.5f, 0.5f}, {1.f, 0.f, 1.f}, {0.f, 1.f}, {0.f, -1.f, 0.f}},   // Base back-left (index 4)
        };

        indices = {
            // Pyramid sides (CCW winding)
            0, 2, 1,  // Front face (Top, Front-right, Front-left)
            0, 3, 2,  // Right face (Top, Back-right, Front-right)
            0, 4, 3,  // Back face (Top, Back-left, Back-right)
            0, 1, 4,  // Left face (Top, Front-left, Back-left)

            // Base (CCW winding)
            1, 2, 3,  // First triangle
            1, 3, 4   // Second triangle
        };
    }
};

#endif