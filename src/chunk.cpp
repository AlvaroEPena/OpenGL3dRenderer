#include "chunk.h"

Chunk::Chunk(glm::vec3 position){
	this->position = position;

	genBlocks();
	buildChunk();
}

Chunk::~Chunk(){
	delete chunkMesh;
}

void Chunk::genChunk(){
	
}

void Chunk::genBlocks(){
	for (int i = 0; i < 3; i++) {
		Cube cube(glm::vec3(i, 0.f, 0.f));
		
		std::vector<Vertex> face = cube.getFace(cube.FRONT); // get front face data
		//std::cout << "pos x: " << face[0].position.x << std::endl;

		Vertex* dataPtr = face.data();
		// Alternatively, you can use a range-based loop for cleaner code
		//std::cout << "pos x: " << dataPtr[i].position.x << std::endl;


		//for (const Vertex& v : face) { // extract
		//	chunkVertices.push_back(v.position);
		//	chunkUVs.push_back(v.texCoords);
		//}
		for (const Vertex& v : face) { // extract
			chunkData.push_back(v);
			
		}

		addIndices(1);
	
	}
}

void Chunk::buildChunk(){
	chunkMesh = new Mesh(chunkData.data(), chunkData.size(), chunkIndices.data(), chunkIndices.size());
}

void Chunk::renderChunk(Shader* program){
	chunkMesh->render(program);
}

void Chunk::addIndices(int faceAmount)
{
	for (int i = 0; i < faceAmount; i++) {
		chunkIndices.push_back(0 + indexCount);
		chunkIndices.push_back(1 + indexCount);
		chunkIndices.push_back(2 + indexCount);
		chunkIndices.push_back(2 + indexCount);
		chunkIndices.push_back(3 + indexCount);
		chunkIndices.push_back(0 + indexCount);

		indexCount += 4;
	}

}
