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

layout(local_size_x = 20, local_size_y = 20, local_size_z = 1) in;

uniform int width;
uniform int height; 
uniform float moveSpeed; 
uniform float deltaTime; 
uniform int numOfCells;

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

	Cell cell = cells[idx];

	//vec2 dir = vec2(cos(cell.angle), sin(cell.angle));
	//vec2 newPos = cell.pos.xy + dir * moveSpeed * deltaTime;

	//cells[idx].pos = newPos;
	int posIdx = int(cell.pos.x) + int(cell.pos.y) * width;
	trailMap[posIdx].value = vec4(1.0f);
	//trailMap[idx].value = vec4(0.5f);

	//vec4 col = vec4(i / float(width), j / float(height), 0, 1);
	//vec4 col = vec4(cell.pos.x / float(width), cell.pos.y / float(height), 0, 1);
	//vec4 col = cell.vel;
    //imageStore(texture, ivec2(i, j), col);
    imageStore(texture, ivec2(i, j), trailMap[idx].value);
}