#ifndef CHUNK_H
#define CHUNK_H

#include <vector>
#include <glm/glm.hpp>

#include "util/primitives/cube.h"
#include "util/shader.h"
#include "util/mesh.h"


class Chunk {

public:
	Chunk(glm::vec3 position);
	~Chunk();
	glm::vec3 position;

	void genChunk(); // gen the data
	void genBlocks(); // gen the block faces given the data
	void buildChunk(); // take data and process for the render
	void renderChunk(Shader* program); // draw

	void addIndices(int faceAmount);


private:
	const int SIZE = 16;
	const int HEIGHT = 32;

	std::vector<Vertex> chunkData;
	std::vector<glm::vec3> chunkVertices;
	std::vector<glm::vec2> chunkUVs;
	std::vector<unsigned> chunkIndices;
	unsigned indexCount = 0;

	Mesh* chunkMesh = NULL;


};
#endif