attribute vec2 attrPosition;
attribute vec3 attrColor;
attribute vec2 attrTexCoords;

uniform mat4 unifProjection;
uniform mat4 rotMatrix;
varying vec3 varyColor;
varying vec2 varyTexCoords;

void main()
{
	varyColor = attrColor;
	varyTexCoords = attrTexCoords;
	gl_Position = unifProjection * rotMatrix * vec4(attrPosition, 0.0, 1.0);
}