#version 330 //GLSL language version

layout (location = 0) in vec3 Position;

uniform mat4 gWorld;

uniform float gScaleX;
uniform float gScaleY;

void main()
{
	gl_Position = gWorld * vec4(gScaleX * Position.x, gScaleY * Position.y, Position.z, 1.0);
}