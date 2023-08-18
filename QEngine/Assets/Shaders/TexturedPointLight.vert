#version 430
 
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexNormal;
layout(location = 2) in vec2 VertexTex;
 
out Data{
	vec4 position;
	vec3 normal;
	vec2 texCoord;
} data;
 
uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;
 
void main(){
	data.normal = normalize( NormalMatrix * VertexNormal);
	data.position = ModelViewMatrix * vec4( VertexPosition, 1 );
	data.texCoord = VertexTex;
	gl_Position = MVP * vec4( VertexPosition, 1 );
}