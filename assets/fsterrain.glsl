#version 400
uniform vec3 EyePos;
uniform vec3 LightPos;
uniform vec3 LightColor;
uniform vec3 DiffuseColor;
uniform vec3 SpecularColor;
uniform vec3 AmbientColor;
uniform float SpecularExp;

uniform sampler2D DetailTex[2];
uniform vec3 Scaling;

in vec3 Position;
in vec3 Normal;
in vec2 Texcoord;
out vec4 FragColor;

float sat( in float a)
{
    return clamp(a, 0.0, 1.0);
}


void main()
{
    vec3 N      = normalize(Normal);
    vec3 L      = normalize(LightPos); // light is treated as directional source
    vec3 D      = EyePos-Position;
    float Dist  = length(D);
    vec3 E      = D/Dist;
    vec3 R      = reflect(-L,N);

    // Diffuse and Specular
    vec3 DiffuseComponent = LightColor * DiffuseColor * sat(dot(N,L));
    vec3 SpecularComponent = LightColor * SpecularColor * pow( sat(dot(R,E)), SpecularExp);

    // Slope Texture Blending
    float GRASS_END = 0.45;
    float STONE_START = 0.25;
    float derivation = abs(dot(N, vec3(0.0, 1.0, 0.0)));
    derivation = clamp((derivation-STONE_START)/(GRASS_END-STONE_START), 0.0, 1.0);
    vec4 TextureTerrain = mix(texture(DetailTex[1], Texcoord), texture(DetailTex[0], Texcoord), derivation);

    // Fog Rendering
    vec4 fogColor = vec4(1.0, 1.0, 1.0, 1.0);
    float d = length(Position - EyePos);
    float dmax = 50;
    float dmin = 20;
    float fogFactor = clamp(((d-dmax)/(dmax-dmin)), 0, 1);

    // Final Output
    FragColor = vec4(((DiffuseComponent + AmbientColor) + SpecularComponent), 1) * TextureTerrain * (1-fogFactor)
            + fogFactor * fogColor;
}
