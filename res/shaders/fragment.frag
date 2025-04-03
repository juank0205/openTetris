#version 460 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D texture1;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    FragColor = texture(texture1, texCoord) * vec4(lightColor, 1.0f);
}  
