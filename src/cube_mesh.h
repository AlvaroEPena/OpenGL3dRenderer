#ifndef CUBE_MESH_H
#define CUBE_MESH_H

#include "glad/glad.h"
#include "util/shader.h"

class CubeMesh {
public:
	CubeMesh();
	void draw();
	~CubeMesh();

	void setPosition(const glm::vec3& position);
	void draw(Shader& shader);

	glm::mat4 model;
private:
	unsigned int VBO, VAO, vertex_count, EBO;
};

#endif // CUBE_MESH_H