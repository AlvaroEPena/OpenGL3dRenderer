#ifndef MESH_H
#define MESH_H

#include <iostream>
#include "shader.h"
#include "texture.h"
#include "vertex.h"


class Mesh {
public:
	Mesh(Vertex* vertexArray, const unsigned int& nVertices, 
		unsigned int* indexArray, const unsigned int& nIndex, 
		glm::vec3 position = glm::vec3(0.f),
		glm::vec3 rotation = glm::vec3(0.f),
		glm::vec3 scale = glm::vec3(1.f)
	);
	~Mesh();

	void updateUniforms(Shader* shader);
	void render(Shader* shader);

	void setPosition(glm::vec3 pos);
	void setRotation(glm::vec3 rot);
	void setScale(glm::vec3 scale);
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	unsigned int nVertices;
	unsigned int nIndices;
	bool useElements;
	bool modelMatrixNeedsUpdate;

	glm::mat4 modelMatrix;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	void initVertexBufferData(Vertex* vertexArray, const unsigned int& nVertices, unsigned int* indexArray, const unsigned int& nIndex);
	void updateModelMatrix();

};


#endif