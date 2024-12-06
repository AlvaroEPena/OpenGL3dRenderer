#version 330 core

layout(location = 0) in vec3 vPos; // Corresponds to glVertexAttribPointer(0)
layout(location = 1) in vec3 vColor;    // Corresponds to glVertexAttribPointer(1)
layout(location = 2) in vec2 vTexCoords; // Corresponds to glVertexAttribPointer(2)
layout(location = 3) in vec3 normal;   // Corresponds to glVertexAttribPointer(3)

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// out vec3 fragmentColor; // output vec3 so fragment shader can use the vertex color (pipe it over)
out vec3 fragColor;
out vec2 fragTexCoords;

void main()	{
	//fragColor = vColor; // set our output vec3 fragment color equal to the input vertexColor we got as input. 

	fragTexCoords = vTexCoords;

	gl_Position = projection * view * model * vec4(vPos, 1.0f); // set vertext position x, y, z in NDC ( origin is middle of screen -1 -> 1). this is an attribute. an attribute is something that has 1-4 numbers describing something
}