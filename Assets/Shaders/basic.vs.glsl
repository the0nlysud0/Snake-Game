#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in mat4 aModel;
layout(location = 5) in vec3 aColor;
layout(location = 6) in float aTexID;

out vec2 TexCoord;
out float TexID;
out vec3 Color;

uniform mat4 projection;
uniform mat4 model;
uniform float rotation;

void main()
{
  gl_Position = projection * aModel * vec4(aPos.xy, 0.0, 1.0);
  TexCoord = aPos + vec2(0.5);
  // TexCoord = vec2(
  //   TexCoord.x * cos(rotation) - TexCoord.y * sin(rotation),
  //   TexCoord.x * sin(rotation) + TexCoord.y * cos(rotation)
// );
  TexID = aTexID;
  Color = aColor;
}
