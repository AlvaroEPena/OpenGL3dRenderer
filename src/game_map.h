#ifndef MAP_H
#define MAP_H

#include "cube_mesh.h"
#include <vector>
#include <glm/glm.hpp>

#include <iostream>

class Map {
public:
    std::vector<CubeMesh*> cubes;  // A vector to hold our cubes

    Map() {
        // Generate a 10x10 grid of cubes
        generateMap();
    }

    // Method to generate the map (cubes)
    void generateMap() {
        for (int x = -100; x < 100; ++x) {
            for (int z = -100; z < 100; ++z) {
                // You can adjust the Y value to vary the height if needed
                glm::vec3 position(x, -4.0f, z);
                CubeMesh* newCube = new CubeMesh();
                newCube->setPosition(position);  // Set position of each cube
                cubes.push_back(newCube);
            }
        }
    }

    // Method to draw all the cubes in the map
    void draw(Shader& shader) {
        for (auto& cube : cubes) {
            cube->draw(shader);  // Draw each cube with its position transformation
        }
    }

    ~Map() {
        for (auto& cube : cubes) {
            delete cube;  // Clean up the memory
        }
    }
};

#endif // MAP_H