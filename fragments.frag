#version 330 core

// Variables coming in from the vertex shader
in vec3 Color;
in vec3 Normal;
in vec3 HalfVector;

out vec4 FragColor;

uniform vec3 ambientColor;
uniform float ambientWeight;
uniform vec3 directLightColor;
uniform float directionalWeight;
uniform float Shininess;
uniform float Strength;
uniform vec3 LightDirection;

void main()
{
	// compute cosine of the directions, using dot products,
	// to see how much light would be reflected
	float diffuse = max(0.0, dot(Normal, LightDirection));
	float specular = max(0.0, dot(Normal, HalfVector));

	// surfaces facing away from the light (negative dot products)
	// wont be lit by the directional light
	if (diffuse == 0.0)
		specular = 0.0;
	else
		specular = pow(specular, Shininess); // sharpen the highlight

	vec3 scatteredLight = normalize((ambientWeight * ambientColor) + (directionalWeight * directLightColor ) * diffuse);
	vec3 reflectedLight = directLightColor * specular * Strength;
	// don’t modulate the underlying color with reflected light,
	//   only with scattered light
	vec3 rgb = min(Color.rgb * scatteredLight + reflectedLight, vec3(1.0));
	FragColor = vec4(rgb, 1.0);
}
