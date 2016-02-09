#version 330 //GLSL language version

layout (location = 0) in vec3 Position;

uniform mat4 gWorld;

void main()
{
	gl_Position = gWorld * vec4(Position.x,
		Position.y,
		Position.z,
		1.0);
}