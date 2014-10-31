varying vec3 varyColor;
varying vec2 varyTexCoords;

uniform sampler2D uniSampler2D;

void main()
{
	vec4 texColor = texture(uniSampler2D, varyTexCoords);
	gl_FragColor = vec4(varyColor, 1.0) * texColor;
}