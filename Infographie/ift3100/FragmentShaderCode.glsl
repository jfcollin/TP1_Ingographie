#version 150

in vec3 vertexShaderColor;
out vec4 fragmentShaderColor;

void main() {
	fragmentShaderColor = vec4(vertexShaderColor, 1.0);
}