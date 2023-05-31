#version 440

struct Cell 
{
	vec2 position;
	float angle;
};

struct Trail
{
	vec4 value;
};

layout(binding = 0) buffer cellsBuffer { Cell cells[]; };
layout(binding = 1) buffer trailMapBuffer { Trail trailMap[]; };
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

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

	//if (idx >= numOfCells) return;

	Cell cell = cells[idx];

	//vec2 dir = vec2(cos(cell.angle), sin(cell.angle));
	//vec2 newPos = cell.position + dir * moveSpeed * deltaTime;
	//cells[idx].position = newPos;

	int posIdx = int(cell.position.x + cell.position.y * width);
	//trailMap[int(cell.position.x)].value = vec4(i / float(width), j / float(height), 0, 1);
	trailMap[idx].value = vec4(cell.position.x, cell.position.y, 0, 1);
	//trailMap[idx].value = vec4(i / float(width), j / float(height), 0, 1);

	//trailMap[0].value = vec4(1);
	//trailMap[21].value = vec4( 1);
}