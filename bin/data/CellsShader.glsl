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

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

uniform int width;
uniform int height; 
uniform float moveSpeed; 
uniform float deltaTime; 
uniform int numOfCells;
uniform float time;

const float PI = 3.1415;

float hash(uint n) 
{
	n = (n << 13U) ^ n;
    n = n * (n * n * 15731U + 789221U) + 1376312589U;
    return float( n & uint(0x7fffffffU))/float(0x7fffffff);
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
		float rand = hash(int(cell.pos.y) * width + int(cell.pos.x) + int(time));
		cells[idx].vel.x = rand * 2.0f * PI;
	}

	cells[idx].pos = newPos;

	int posIdx = int(newPos.x) + int(newPos .y) * width;
	trailMap[posIdx].value = vec4(1.0f);
}