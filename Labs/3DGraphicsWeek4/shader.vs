#version 330 //GLSL language version

layout (location = 0) in vec3 Position;

/* Lab 3 */
uniform float gScale;
uniform mat4 gWorld;
/* Lab 3 */

void main()
{
	/* Lab 3: Changed variable to gScale & multiplied vector by gWorld */
	gl_Position = gWorld * vec4(gScale * Position.x, gScale * Position.y, Position.z, 1.0);
}