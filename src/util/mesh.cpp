#include "mesh.h"


Mesh::Mesh(Vertex* vertexArray, const unsigned int& nVertices, unsigned int* indexArray, const unsigned int& nIndex, glm::vec3 pos, glm::vec3 rot, glm::vec3 s)
    : position(pos), rotation(rot), scale(s)
{
    modelMatrixNeedsUpdate = true;
    updateModelMatrix();

    this->initVertexBufferData(vertexArray, nVertices, indexArray, nIndex);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);
}


void Mesh::updateUniforms(Shader* shader)
{
    this->updateModelMatrix(); // send updates to model matrix if needed.

    shader->SetMatrix4("model", modelMatrix, true);
}

void Mesh::render(Shader* shader)
{
    // update model
    this->updateUniforms(shader);
    glBindVertexArray(VAO); // bind the vertex array

    if (useElements)
        glDrawElements(GL_TRIANGLES, this->nIndices, GL_UNSIGNED_INT, 0); // render
    else
        glDrawArrays(GL_TRIANGLES, 0, this->nVertices);
}

void Mesh::setPosition(glm::vec3 pos)
{
    this->position = pos;
    modelMatrixNeedsUpdate = true;
}

void Mesh::setRotation(glm::vec3 rot)
{
    this->rotation = rot;

    if (abs(this->rotation.x) > 360) rotation.x = fmod(rotation.x, 360.f);
    if (abs(this->rotation.y) > 360) rotation.y = fmod(rotation.y, 360.f);
    if (abs(this->rotation.z) > 360) rotation.z = fmod(rotation.z, 360.f);

    modelMatrixNeedsUpdate = true;
}

void Mesh::setScale(glm::vec3 s)
{
    this->scale = s;
    modelMatrixNeedsUpdate = true;
}



void Mesh::initVertexBufferData(Vertex* vertexArray, const unsigned int& nVertices, unsigned int* indexArray, const unsigned int& nIndex)
{
    this->nVertices = nVertices;
    this->nIndices = nIndex;

    useElements = nIndices > 0 ? true : false;
    // VAO = Vertex Array object --> this is basically the object where we will store all vertexes(internally in openGL). so we must first genereate it. Pass count (1 since only one v array) and the unsigned int
    // The unsigned int will basically be the index of the vertex array (an indentifier for  OpenGL to reference it internally). (GLsizei n, GLuint* arrays);
    // The VAO basically wraps up all of the state needed to draw our stuff. The VAO will be recording the VBO/VBOs and its attribute pointers which indiciates how to interpret the data (think in the shaders how we set gl_position etc)
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO); // so after we generate it we can bind it with the indentifier

    // VBO = Vertex Buffer object -> this is basically a big list of data, in this case read from the float list and then it is shipped off to the gpu
    glGenBuffers(1, &this->VBO); // generate our buffers
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO); // bind it with our identifier
    glBufferData(GL_ARRAY_BUFFER, this->nVertices * sizeof(Vertex), vertexArray, GL_STATIC_DRAW); // attach the data, calculate size in bytes, pass pointer to first item

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)); // read in the data. 0 is location (vertexPos in this case), 3 is the number of members in attribute, then type, 
    glEnableVertexAttribArray(0); // always leave false, how many bytes to go until the next one of same attribute, and lastly the starting poisition.
    // after that call gl enable the attrib array

    // color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    // texture coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);

    // normals
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(3);


    // EBO = Element Buffer Object
    glGenBuffers(1, &EBO); // generate the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // bind the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nIndices * sizeof(unsigned int), indexArray, GL_STATIC_DRAW); // attach indices to the EBO

    // unbind
    glBindVertexArray(0);

}


void Mesh::updateModelMatrix()
{
    if (modelMatrixNeedsUpdate)
    {
        // create identity matrix
        this->modelMatrix = glm::mat4(1.f);
        // apply position
        this->modelMatrix = glm::translate(modelMatrix, this->position);
        // apply rotations
        this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians((float)this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
        this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians((float)this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
        this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians((float)this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
        // apply scale
        this->modelMatrix = glm::scale(modelMatrix, this->scale);
        modelMatrixNeedsUpdate = false; // set updated
    }
}

