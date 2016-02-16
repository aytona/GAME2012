#version 330

out vec4 FragColor;

in vec4 Colour;

void main()
{
    FragColor = Colour; //Return a red color
}