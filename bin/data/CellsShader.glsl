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

layout(local_size_x = 1024, local_size_y = 1, local_size_z = 1) in;

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

float sense(Cell cell, float angleOffset)
{
	return 0.0f;
}

void main()
{
	int i, j;
	i = int(gl_GlobalInvocationID.x);
	j = int(gl_GlobalInvocationID.y);

	//int idx = i + j * width;
	int idx = i;

	if (idx >= numOfCells) return;
	
	Cell cell = cells[idx];
	float angle = cell.vel.x;

	vec2 dir = vec2(cos(angle), sin(angle));
	vec2 newPos = cell.pos.xy + dir * moveSpeed * deltaTime;

	if (newPos.x < 0 || newPos.x > width - 1 || newPos.y < 0 || newPos.y > height - 1)
	{
		newPos.x = min(width - 1, max(0, cell.pos.x));
		newPos.y = min(height - 1, max(0, cell.pos.y));
		cells[idx].vel.x = mod(angle + 60, 360.0f);
		//float rand = hash(int(cell.pos.y) * width + int(cell.pos.x) + int(idx * hash(idx)));
		//cells[idx].vel.x = rand * 2.0f * PI;
	}

	cells[idx].pos = newPos;

	int posIdx = int(newPos.x) + int(newPos .y) * width;
	trailMap[posIdx].value = vec4(1.0f);
}