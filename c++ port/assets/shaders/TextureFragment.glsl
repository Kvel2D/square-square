#version 130

//Texture Color
uniform vec4 TextureColor;

//Texture Unit
uniform sampler2D TextureUnit;

//Texture coordinate
in vec2 texCoord;

//Final color
out vec4 gl_FragColor;



void main()
{
	//Set fragment
	gl_FragColor = texture( TextureUnit, texCoord ) * TextureColor;
}