#ifndef GAME_MAP
#define GAME_MAP

#include "util/mesh.h"
#include <vector>
#include <glm/glm.hpp>

#include <iostream>

class Map {
public:
    Mesh* cube;// A vector to hold our cubes
    Shader* shader;

    Map(Mesh* c, Shader* s) {
        // Generate a 10x10 grid of cubes
        cube = c;
        shader = s;
    }

    // Method to draw all the cubes in the map
    void draw() {
        for (float x = -10; x < 10; x++) {
            for (float z = -10; z < 10; z++) {
                // You can adjust the Y value to vary the height if needed
                glm::vec3 position(x, -4.0f, z);
                cube->setPosition(position);  // Set position of each cube
                cube->render(shader);
            }
        }
    }
};

#endif 