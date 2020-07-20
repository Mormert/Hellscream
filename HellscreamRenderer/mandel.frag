#version 330 core

#define product(a, b) vec2(a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x)

#define maxN 100.0f

out vec4 FragColor;
in vec3 ourColor;

uniform float time;
uniform vec3 offset;

void main()
{

	vec2 c = vec2(gl_FragCoord.x/2000.0f, gl_FragCoord.y/2000.0f) * 4 - vec2(2.0);	

	vec2 z = vec2(sin(time), 0.0);
	float n = 0;

	while(length(z) < 2.0 && n < maxN)
	{
		z = product(z,z) + c;
		n+=1;
	}

	float iColor = n / maxN; // [0,1]

	float H = iColor;
	float R = abs(H * 6.0f - 3.0f) - 1.0f;
	float G = 2.0f - abs(H * 6.0f - 2.0f);
	float B = 2.0f - abs(H * 6.0f - 4.0f);  

	vec3 color = vec3(G,B,G) * iColor;

	FragColor = vec4(color, 1.0f);

}