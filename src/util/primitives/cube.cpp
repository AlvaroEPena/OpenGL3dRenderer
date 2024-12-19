#include "cube.h"
#include <iostream>


Cube::Cube(glm::vec3 position) : 
	front(), back(), left(), right(), top(), bottom() 
{
	this->position = position;
	build();
}

void Cube::build() {
	vertices = {
		// Front face
		{ { -0.5f,  0.5f,  0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.0f, 2.0f / 3.0f },{ 0.0f, 0.0f, 1.0f } }, // top left
		{ { -0.5f, -0.5f,  0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f / 3.0f },{ 0.0f, 0.0f, 1.0f } }, // bottom left
		{ { 0.5f, -0.5f,  0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.25f, 1.0f / 3.0f },{ 0.0f, 0.0f, 1.0f } }, // bottom right
		{ { 0.5f,  0.5f,  0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.25f, 2.0f / 3.0f },{ 0.0f, 0.0f, 1.0f } }, // top right

		// Back face
		{ { 0.5f,  0.5f, -0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.5f, 2.0f / 3.0f },{ 0.0f, 0.0f, -1.0f } }, // top right
		{ { 0.5f, -0.5f, -0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.5f, 1.0f / 3.0f },{ 0.0f, 0.0f, -1.0f } }, // bottom right
		{ { -0.5f, -0.5f, -0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.75f, 1.0f / 3.0f },{ 0.0f, 0.0f, -1.0f } }, // bottom left
		{ { -0.5f,  0.5f, -0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.75f, 2.0f / 3.0f },{ 0.0f, 0.0f, -1.0f } }, // top left

		// Left face
		{ { -0.5f,  0.5f, -0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.75f, 2.0f / 3.0f },{ -1.0f, 0.0f, 0.0f } }, // top left
		{ { -0.5f, -0.5f, -0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.75f, 1.0f / 3.0f },{ -1.0f, 0.0f, 0.0f } }, // bottom left
		{ { -0.5f, -0.5f,  0.5f },{ 1.0f, 1.0f, 1.0f },{ 1.0f, 1.0f / 3.0f },{ -1.0f, 0.0f, 0.0f } }, // bottom right
		{ { -0.5f,  0.5f,  0.5f },{ 1.0f, 1.0f, 1.0f },{ 1.0f, 2.0f / 3.0f },{ -1.0f, 0.0f, 0.0f } }, // top right

		// Right face
		{ { 0.5f,  0.5f,  0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.25f, 2.0f / 3.0f },{ 1.0f, 0.0f, 0.0f } }, // top left
		{ { 0.5f, -0.5f,  0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.25f, 1.0f / 3.0f },{ 1.0f, 0.0f, 0.0f } }, // bottom left
		{ { 0.5f, -0.5f, -0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.5f, 1.0f / 3.0f },{ 1.0f, 0.0f, 0.0f } }, // bottom right
		{ { 0.5f,  0.5f, -0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.5f, 2.0f / 3.0f },{ 1.0f, 0.0f, 0.0f } }, // top right

		// Top face
		{ { -0.5f,  0.5f, -0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.25f, 1.0f },{ 0.0f, 1.0f, 0.0f } }, // top left
		{ { -0.5f,  0.5f,  0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.25f, 2.0f / 3.0f },{ 0.0f, 1.0f, 0.0f } }, // bottom left
		{ { 0.5f,  0.5f,  0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.5f, 2.0f / 3.0f },{ 0.0f, 1.0f, 0.0f } }, // bottom right
		{ { 0.5f,  0.5f, -0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.5f, 1.0f },{ 0.0f, 1.0f, 0.0f } }, // top right

		// Bottom face
		{ { -0.5f, -0.5f,  0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.25f, 1.0f / 3.0f },{ 0.0f, -1.0f, 0.0f } }, // bottom left
		{ { -0.5f, -0.5f, -0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.25f, 0.0f },{ 0.0f, -1.0f, 0.0f } }, // top left
		{ { 0.5f, -0.5f, -0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.5f, 0.0f },{ 0.0f, -1.0f, 0.0f } }, // top right
		{ { 0.5f, -0.5f,  0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.5f, 1.0f / 3.0f },{ 0.0f, -1.0f, 0.0f } }  // bottom right
	};

	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].position += this->position;

		// Determine which face we're on based on the vertex index using modulo
		Faces face = static_cast<Faces>(i / 4);  // Integer division by 4 gives the face index

		// Use the enum to decide where to push the vertex
		switch (face) {
		case FRONT:
			front.push_back(vertices[i]);
			break;
		case BACK:
			back.push_back(vertices[i]);
			break;
		case LEFT:
			left.push_back(vertices[i]);
			break;
		case RIGHT:
			right.push_back(vertices[i]);
			break;
		case TOP:
			top.push_back(vertices[i]);
			break;
		case BOTTOM:
			bottom.push_back(vertices[i]);
			break;
		}
	}

	indices = {
		0, 1, 2, 2, 3, 0,         // Front face
		4, 5, 6, 6, 7, 4,         // Back face
		8, 9, 10, 10, 11, 8,      // Left face
		12, 13, 14, 14, 15, 12,   // Right face
		16, 17, 18, 18, 19, 16,   // Top face
		20, 21, 22, 22, 23, 20    // Bottom face
	};	
}

std::vector<Vertex> Cube::getFace(Faces face){
	switch (face) {
	case FRONT: // front
		// Directly assign the 4 vertices for the front face
		//std::cout << " front " << front[0].position.x << std::endl;
		
		return front;
		break;
	case BACK: // back
		return back;
		break;
	case LEFT: // left
		return left;
		break;
	case RIGHT: // right
		return right;
		break;
	case TOP: // top
		return top;
		break;
	case BOTTOM: // bottom
		return bottom;
		break;
	}

	std::cout << " none " << std::endl;
	return std::vector<Vertex>(0); // return default
}

