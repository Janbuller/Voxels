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

uniform float FogDistance;

float LinearizeDepth(float depth, float near, float far)
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(vec3(1.75, 1.346, 0.74));

  float diff = max(dot(norm, lightDir), 0.0);
  diff = max(0.3, diff * 1.5);
  diff = 1;

  vec4 textureColor = texture(material.texture_diffuse1, TexCoords);
  vec4 textureShaded = textureColor * diff;

  vec4 fogColor = vec4(0.7);

  float near = 0.1;
  float far  = FogDistance;
  float fogAmount = LinearizeDepth(gl_FragCoord.z, near, far) / far;
  fogAmount = max(0.0, min((exp(fogAmount*1.9)-1)*0.2, 1.0));

  fragColor = mix(textureShaded, fogColor, fogAmount);
  // fragColor = texture(material.texture_diffuse1, TexCoords) * diff;
  // fragColor = vec4(vec3(fogAmount ), 1.0);
}
