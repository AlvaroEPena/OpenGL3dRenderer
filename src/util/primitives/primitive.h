#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <vector>
#include "../vertex.h"

class Primitive 
{
protected:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
public:
	
	virtual ~Primitive() = default;
	
	virtual void build() = 0;

	Vertex* getVertices() { return vertices.data(); }
	unsigned int* getIndices() { return indices.data(); }

	unsigned int getVertexCount() const { return (unsigned int)vertices.size(); }
	unsigned int getIndexCount() const { return (unsigned int)indices.size(); }
};

#endif