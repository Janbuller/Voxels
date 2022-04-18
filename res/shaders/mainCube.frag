#version 460
precision mediump float;
out vec4 fragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

struct Material {
    sampler2D texture_diffuse1;
};

uniform Material material;

void main()
{
    fragColor = texture(material.texture_diffuse1, TexCoords);
    // fragColor = vec4(0);
}
