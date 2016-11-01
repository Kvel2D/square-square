#version 130

//Transformation Matrices
uniform mat4 ProjectionMatrix;
uniform mat4 ModelViewMatrix;

//Vertex position attribute
in vec2 VertexPos2D;

//Texture coordinate attribute
in vec2 TexCoord;
out vec2 texCoord;


void main()
{
	//Process texCoord
	texCoord = TexCoord;

	//Process vertex
	gl_Position = ProjectionMatrix * ModelViewMatrix * vec4( VertexPos2D.x, VertexPos2D.y, 0.0, 1.0 );
}