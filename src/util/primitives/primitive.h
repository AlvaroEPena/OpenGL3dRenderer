#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <vector>
#include "../vertex.h"

class Primitive 
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
private:
	Primitive() {}
	virtual ~Primitive() {}

	void set(const Vertex* vertices, const unsigned int& nVertices,
		unsigned int* indices, const unsigned int& nIndices);
};




#endif