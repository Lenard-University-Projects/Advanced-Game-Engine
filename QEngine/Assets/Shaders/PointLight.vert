#version 430
 
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexNormal;
 
out Data{
	vec4 position;
	vec3 normal;
} data;
 
uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;
 
void main(){
	data.normal = normalize( NormalMatrix * VertexNormal);
	data.position = ModelViewMatrix * vec4( VertexPosition, 1 );
	gl_Position = MVP * vec4( VertexPosition, 1 );
}