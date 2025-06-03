#version 330 core

in vec2 TexCoord;
in float TexID;
in vec3 Color;

uniform sampler2D textures[16];
out vec4 FragColor;

void main()
{
    vec4 texColor;

    int id = int(TexID);
    if (id == 0) texColor = texture(textures[0], TexCoord);
    else if (id == 1) texColor = texture(textures[1], TexCoord);
    else if (id == 2) texColor = texture(textures[2], TexCoord);
    else if (id == 3) texColor = texture(textures[3], TexCoord);
    else if (id == 4) texColor = texture(textures[4], TexCoord);
    else if (id == 5) texColor = texture(textures[5], TexCoord);
    else if (id == 6) texColor = texture(textures[6], TexCoord);
    else if (id == 7) texColor = texture(textures[7], TexCoord);
    else if (id == 8) texColor = texture(textures[8], TexCoord);
    else if (id == 9) texColor = texture(textures[9], TexCoord);
    else if (id == 10) texColor = texture(textures[10], TexCoord);
    else if (id == 11) texColor = texture(textures[11], TexCoord);
    else if (id == 12) texColor = texture(textures[12], TexCoord);
    else if (id == 13) texColor = texture(textures[13], TexCoord);
    else if (id == 14) texColor = texture(textures[14], TexCoord);
    else if (id == 15) texColor = texture(textures[15], TexCoord);
    else texColor = vec4(1.0, 0.0, 1.0, 1.0); // fallback magenta if something’s wrong
    if(texColor.rgb == vec3(1.0, 1.0, 1.0))
    {
        FragColor = vec4(Color,1.0);
    }
    FragColor = vec4(texColor);
}
