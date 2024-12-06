#include "cube_mesh.h"

CubeMesh::CubeMesh() {
    model = glm::mat4(1.0f);
    float data[] = {
        // Position (x, y, z)                // Texture Coordinates (u, v)
        // Front face (CCW winding)
        -0.5f,  0.5f,  0.5f,  0.0f,  2.0f / 3.0f, // top left
        -0.5f, -0.5f,  0.5f,  0.0f,  1.0f / 3.0f, // bottom left
         0.5f, -0.5f,  0.5f,  0.25f,  1.0f / 3.0f, // bottom right
         0.5f,  0.5f,  0.5f,  0.25f,  2.0f / 3.0f, // top right

         // Back face (CCW winding)
          0.5f,  0.5f, -0.5f,  0.5f, 2.0f / 3.0f, // top right
          0.5f, -0.5f, -0.5f,  0.5f, 1.0f / 3.0f, // bottom right
         -0.5f, -0.5f, -0.5f,  0.75f, 1.0f / 3.0f, // bottom left
         -0.5f,  0.5f, -0.5f,  0.75f, 2.0f / 3.0f, // top left

         // Left face (CCW winding)
         -0.5f,  0.5f, -0.5f,  0.75f, 2.0f / 3.0f, // top left
         -0.5f, -0.5f, -0.5f,  0.75f, 1.0f / 3.0f, // bottom left
         -0.5f, -0.5f,  0.5f,  1.0f, 1.0f / 3.0f, // bottom right
         -0.5f,  0.5f,  0.5f,  1.0f, 2.0f / 3.0f, // top right

         // Right face (CCW winding)
          0.5f,  0.5f,  0.5f,  0.25f, 2.0f / 3.0f, // top left
          0.5f, -0.5f,  0.5f,  0.25f, 1.0f / 3.0f, // bottom left
          0.5f, -0.5f, -0.5f,  0.5f, 1.0f / 3.0f, // bottom right
          0.5f,  0.5f, -0.5f,  0.5f, 2.0f / 3.0f, // top right

          // Top face (CCW winding)
          -0.5f,  0.5f, -0.5f,  0.25f, 1.0f, // top left
          -0.5f,  0.5f,  0.5f,  0.25f, 2.0f / 3.0f, // bottom left
           0.5f,  0.5f,  0.5f,  0.5f, 2.0f / 3.0f, // bottom right
           0.5f,  0.5f, -0.5f,  0.5f, 1.0f, // top right

           // Bottom face (CCW winding)
           -0.5f, -0.5f,  0.5f,  0.25f, 1.0f / 3.0f, // bottom left
           -0.5f, -0.5f, -0.5f,  0.25f, 0.0f, // top left
            0.5f, -0.5f, -0.5f,  0.5f, 0.0f, // top right
            0.5f, -0.5f,  0.5f,  0.5f, 1.0f / 3.0f  // bottom right
    };
    unsigned int indices[] = {
        // Front face
        0, 1, 2, 2, 3, 0,
        // Back face
        4, 5, 6, 6, 7, 4,
        // Left face
        8, 9, 10, 10, 11, 8,
        // Right face
        12, 13, 14, 14, 15, 12,
        // Top face
        16, 17, 18, 18, 19, 16,
        // Bottom face
        20, 21, 22, 22, 23, 20
    };

    vertex_count = 36;

    // VAO = Vertex Array object --> this is basically the object where we will store all vertexes(internally in openGL). so we must first genereate it. Pass count (1 since only one v array) and the unsigned int
    // The unsigned int will basically be the index of the vertex array (an indentifier for  OpenGL to reference it internally). (GLsizei n, GLuint* arrays);
    // The VAO basically wraps up all of the state needed to draw our stuff. The VAO will be recording the VBO/VBOs and its attribute pointers which indiciates how to interpret the data (think in the shaders how we set gl_position etc)
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); // so after we generate it we can bind it with the indentifier

    // VBO = Vertex Buffer object -> this is basically a big list of data, in this case read from the float list and then it is shipped off to the gpu
    glGenBuffers(1, &VBO); // generate our buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind it with our identifier
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW); // attach the data, calculate size in bytes, pass pointer to first item

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // read in the data. 0 is location (vertexPos in this case), 3 is the number of members in attribute, then type, 
    glEnableVertexAttribArray(0); // always leave false, how many bytes to go until the next one of same attribute, and lastly the starting poisition.
    // after that call gl enable the attrib array

    // uv position
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // EBO = Element Buffer Object
    glGenBuffers(1, &EBO); // generate the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // bind the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // attach indices to the EBO
}

void CubeMesh::setPosition(const glm::vec3& position) {
    model = glm::mat4(1.0f);  // Reset model matrix
    model = glm::translate(model, position);  // Apply translation
}

void CubeMesh::draw(Shader& shader) {
    glBindVertexArray(VAO);
    shader.SetMatrix4("model", model);  // Send model matrix to shader
    glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, 0);
}

CubeMesh::~CubeMesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}