varying vec3 varyColor;
varying vec2 varyTexCoords;

uniform sampler2D uniSampler2D;

void main()
{
	gl_FragColor = texture(uniSampler2D, varyTexCoords);
}