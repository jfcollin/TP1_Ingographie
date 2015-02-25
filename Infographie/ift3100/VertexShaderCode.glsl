#version 150

in vec3 position;
in vec3 vertexColor;
in mat4 fullTransformMatrix;

out vec3 vertexShaderColor;
	
void main() {
	vec4 v = vec4(position, 1.0);
	gl_Position = fullTransformMatrix * v;
	vertexShaderColor = vertexColor;
}