#ifndef CUBE_H
#define CUBE_H

#include "Primitive.h"

class Cube : public Primitive {
public:
    Cube(glm::vec3 position);

    void build() override;

	enum Faces {
		FRONT,
		BACK,
		LEFT,
		RIGHT,
		TOP,
		BOTTOM
	};

	std::vector<Vertex> getFace(Faces face);
	glm::vec3 position;


private:
	std::vector<Vertex> front;
	std::vector<Vertex> back;
	std::vector<Vertex> left;
	std::vector<Vertex> right;
	std::vector<Vertex> top;
	std::vector<Vertex> bottom;

};
#endif