#version 330 core

in vec3 fragColor; // take in fragmentColor piped in from the vertex shader
in vec2 fragTexCoords;

out vec4 screenColor; // output the screen color (what we are drawing)

uniform sampler2D material; // 0


void main() {
	screenColor = texture(material, fragTexCoords); 
}