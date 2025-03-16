#version 460 core
out vec4 FragColor;

in vec3 myColor; 
in vec2 texCoord; 

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, texCoord) * vec4(myColor, 1.0);
}  
