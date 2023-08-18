#version 430
 
struct LightInfo{
	vec3 position;	
	vec4 ambient;		
	vec4 diffuse;		
	vec4 specular;		
};
 
struct MaterialInfo{
	vec4 ambient;			
	vec4 diffuse;			
	vec4 specular;			
	float shininess;	
};
 
in Data{
	vec4 position;
	vec3 normal;
} data;
 
uniform LightInfo light;
uniform MaterialInfo material;
uniform vec3 cameraPosition;

out vec4 fragColor;

void main(void){
	vec3 lightDirection = light.position - vec3(data.position);
	float lightDistance = length(lightDirection);
	vec3 eyeDirection = cameraPosition - data.position.xyz;
	lightDirection = lightDirection / lightDistance;
	// Scale distance for demo room
	float attenuation = clamp(lightDistance / 400.0, 0.0, 1.0);
	vec3 halfVector = normalize(lightDirection + eyeDirection);
	float diffuse = max(0.0, dot(data.normal, lightDirection));
	float specular = max(0.0, dot(data.normal, halfVector));
	if(diffuse == 0.0)
		specular = 0.0;
	else
		specular = pow(specular, material.shininess);

	vec3 scatteredLight = material.ambient.rgb + light.ambient.rgb * diffuse * attenuation;
	vec3 reflectedLight = light.specular.rgb * specular * attenuation;
	vec3 rgb = min(material.diffuse.rgb * scatteredLight + reflectedLight, vec3(1.0));
	fragColor = vec4(rgb, material.diffuse.a);
}
