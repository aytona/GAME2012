#version 330 //GLSL language version

layout (location = 0) in vec3 Position;

/* Lab 3 */
uniform float gScale;
uniform mat4 gWorld;
/* Lab 3 */

/* Assignment 2 */
uniform float gScaleX;
uniform float gScaleY;
/* Assignment 2 */

void main()
{
	/* Lab 3: Changed variable to gScale & multiplied vector by gWorld */
	/* Assignment: Added gScaleX and gScaleY to have different ratios of scaling on both axis */
	gl_Position = gWorld * vec4(gScaleX * gScale * Position.x, gScaleY * gScale * Position.y, Position.z, 1.0);
}