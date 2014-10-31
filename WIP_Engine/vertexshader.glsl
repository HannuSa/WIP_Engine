attribute vec2 attrPosition;
attribute vec3 attrColor;
attribute vec2 attrTexCoords;

uniform mat4 unifProjection;
varying vec3 varyColor;
varying vec2 varyTexCoords;

void main()
{
	varyColor = attrColor;
	varyTexCoords = attrTexCoords;
	gl_Position = unifProjection * vec4(attrPosition, 0.0, 1.0);
}