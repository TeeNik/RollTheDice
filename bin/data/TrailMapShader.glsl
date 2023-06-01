#version 440

struct Cell 
{
	vec2 pos;
	vec2 vel;
};

struct Trail
{
	vec4 value;
};

layout(std140, binding = 0) buffer cellsBuffer { Cell cells[]; };
layout(std140, binding = 1) buffer trailMapBuffer { Trail trailMap[]; };
layout(rgba8, binding = 2) uniform writeonly image2D texture;

layout(local_size_x = 10, local_size_y = 10, local_size_z = 1) in;

uniform int width;
uniform int height; 
uniform float moveSpeed; 
uniform float deltaTime; 
uniform int numOfCells;

const float PI = 3.1415;

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

float scaleToRange01(uint state)
{
    return state / 4294967295.0;
}

void main()
{
	int i, j;
	i = int(gl_GlobalInvocationID.x);
	j = int(gl_GlobalInvocationID.y);

	int idx = i + j * width;

	if (idx >= numOfCells) return;
	
	Cell cell = cells[idx];
	float angle = cell.vel.x;

	vec2 dir = vec2(cos(angle), sin(angle));
	vec2 newPos = cell.pos.xy + dir * moveSpeed * deltaTime;

	if (newPos.x < 0 || newPos.x >= width || newPos.y < 0 || newPos.y >= height)
	{
		newPos.x = min(width - 1, max(0, newPos.x));
		newPos.y = min(height - 1, max(0, newPos.y));

		uint rand = hash(int(cell.pos.y) * width + int(cell.pos.x) + hash(i));
		cells[idx].vel.x = scaleToRange01(rand) * 2 * PI;
		//cells[idx].vel.x += 90.0f;
	}

	cells[idx].pos = newPos;

	int posIdx = int(newPos.x) + int(newPos .y) * width;
	trailMap[posIdx].value = vec4(1.0f);
}