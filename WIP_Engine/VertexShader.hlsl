attribute vec2 attrPosition;
attribute vec3 attrColor;

varying vec3 varyColor;

void main()
{
	varyColor = attrColor;
	gl_Position = vec4(attrPosition, 0.0, 1.0);
}