#version 440

struct Agent 
{
	vec2 position;
	float angle;
};

struct Cell
{
	vec4 value;
};

layout(binding = 0) buffer agentsBuffer { Agent agents[]; };
layout(rgba8, binding = 1) uniform writeonly image2D trailMap;
layout(local_size_x = 20, local_size_y = 20, local_size_z = 1) in;

uniform int width;
uniform int height; 
uniform float moveSpeed; 
uniform float deltaTime; 

uint hash(uint state) 
{
	state ^= 2747636419u;
	state *= 2654435769u;
	state ^= state >> 16;
	state *= 2654435769u;
	state ^= state >> 16;
	state *= 2654435769u;
	return state;
}

void main()
{
	int i, j;
	i = int(gl_GlobalInvocationID.x);
	j = int(gl_GlobalInvocationID.y);

	int idx = i + j * width;

	Agent agent = agents[idx];

	vec2 dir = vec2(cos(agent.angle), sin(agent.angle));
	vec2 newPos = agent.position + dir * moveSpeed * deltaTime;

	agents[idx].position = newPos;

	//vec4 col = vec4(i / float(width), j / float(height), 0, 1);
    //imageStore(trailMap, ivec2(gl_GlobalInvocationID.xy), col);


    imageStore(trailMap, ivec2(newPos), vec4(1));
}