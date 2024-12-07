#include "primitive.h"

void Primitive::set(const Vertex* vertices, const unsigned int& nVertices, unsigned int* indices, const unsigned int& nIndices)
{
	for (int i = 0; i < nVertices; i++) {
		this->vertices.push_back(vertices[i]);
	}

	for (int i = 0; i < nIndices; i++) {
		this->indices.push_back(indices[i]);
	}

}
