#type vertex
#version 450 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexCoord;

struct VertexOutput
{
	vec4 m_Color;
	vec2 m_TexCoord;
};

layout (location = 0) out VertexOutput Output;

void main()
{
	Output.m_Color = a_Color;
	Output.m_TexCoord = a_TexCoord;

	gl_Position = vec4(a_Position, 1.0);
}

#type fragment
#version 450 core

layout (location = 0) out vec4 FragColor;

struct VertexOutput
{
	vec4 m_Color;
	vec2 m_TexCoord;
};

layout (location = 0) in VertexOutput Input;

layout (binding = 0) uniform sampler2D u_Texture;

void main()
{
	FragColor = texture(u_Texture, Input.m_TexCoord) * Input.m_Color;
}
