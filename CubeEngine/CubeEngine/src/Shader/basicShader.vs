#version 120

attribute vec3 position;
attribute vec3 inColor;

varying vec3 outColor;

void main()
{
	gl_Position = vec4(position, 1.0);
	outColor = inColor;
}