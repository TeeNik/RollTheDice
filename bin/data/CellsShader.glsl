#version 440

struct Cell 
{
	vec4 pos;
	vec4 vel;
	vec4 speciesMask;
	ivec4 speciesIndex;
};

struct Trail
{
	vec4 value;
};

struct SpeciesInfo
{
	float moveSpeed;
	float turnSpeed;
	float senseDistance;
	float senseAngle;
	int sensorSize;
	vec4 color;
};



layout(std140, binding = 0) buffer cellsBuffer { Cell cells[]; };
layout(std140, binding = 1) buffer trailMapBuffer { Trail trailMap[]; };
layout(rgba8, binding = 2) uniform writeonly image2D texture;

layout(local_size_x = 1024, local_size_y = 1, local_size_z = 1) in;

uniform int width;
uniform int height; 
uniform float deltaTime; 
uniform int numOfCells;
uniform float time;

uniform float trailWeight;

uniform SpeciesInfo speciesSettings[4];

const float PI = 3.1415;

float hash(uint n) 
{
	n = (n << 13U) ^ n;
    n = n * (n * n * 15731U + 789221U) + 1376312589U;
    return float( n & uint(0x7fffffffU))/float(0x7fffffff);
}

float sense(Cell cell, SpeciesInfo info, float angleOffset)
{
	//float angle = mod(cell.vel.x + angleOffset + 360.0f, 360.0f);
	float angle = cell.vel.x + angleOffset;
	vec2 dir = vec2(cos(angle), sin(angle));
	vec2 sensePos = cell.pos.xy + dir * info.senseDistance;

	float sum = 0.0f;
	vec4 senseWeight = cell.speciesMask * 2 - 1;
	for (int offsetX = -info.sensorSize; offsetX <= info.sensorSize; ++offsetX)
	{
		for (int offsetY = -info.sensorSize; offsetY <= info.sensorSize; ++offsetY)
		{
			int x = int(sensePos.x) + offsetX;
			int y = int(sensePos.y) + offsetY;
			if (x >= 0 && x < width && y >= 0 && y < height)
			{
				sum += dot(senseWeight, trailMap[x + y * width].value);
			}
		}
	}

	return sum;
}

void main()
{
	int i, j;
	i = int(gl_GlobalInvocationID.x);
	j = int(gl_GlobalInvocationID.y);

	//int idx = i + j * width;
	int idx = i;

	Cell cell = cells[idx];
	float angle = cell.vel.x;

	SpeciesInfo info = speciesSettings[cell.speciesIndex.x];

	//sense
	float senseAngleRad = info.senseAngle * (PI / 180);
	float forward = sense(cell, info, 0.0f);
	float left = sense(cell, info, -senseAngleRad);
	float right = sense(cell, info, senseAngleRad);
	
	//float rand = hash(uint(cell.pos.x + cell.pos.y * width));
	float rand = 1.0;
	
	if (forward > left && forward > right)
	{
		angle += 0;
	}
	else if (forward < left && forward < right)
	{
		angle = mod(angle + (rand - 0.5) * 2 * info.turnSpeed * deltaTime + 360.0f, 360.0f);
		//angle += (rand - 0.5) * 2 * info.turnSpeed * deltaTime;
	}
	else if (left > right)
	{
		angle = mod(angle - (rand * info.turnSpeed * deltaTime + 360.0f), 360.0f);
		//angle -= rand * info.turnSpeed * deltaTime;
	}
	else if (right > left)
	{
		angle = mod(angle + (rand * info.turnSpeed * deltaTime + 360.0f), 360.0f);
		//angle += rand * info.turnSpeed * deltaTime;
	}

	vec2 dir = vec2(cos(angle), sin(angle));
	vec2 newPos = cell.pos.xy + dir * info.moveSpeed * deltaTime;

	if (newPos.x < 0 || newPos.x > width - 1 || newPos.y < 0 || newPos.y > height - 1)
	{
		newPos.x = min(width - 1, max(0, cell.pos.x));
		newPos.y = min(height - 1, max(0, cell.pos.y));
		angle = mod(angle + 60, 360.0f);
		//float rand = hash(int(cell.pos.y) * width + int(cell.pos.x) + int(idx * hash(idx)));
		//cells[idx].vel.x = rand * 2.0f * PI;
	}

	cells[idx].pos.xy = newPos;
	cells[idx].vel.x = angle;

	int posIdx = int(newPos.x) + int(newPos .y) * width;
	vec4 trailValue = trailMap[posIdx].value;
	trailMap[posIdx].value = min(vec4(1.0f), trailValue + vec4(1,0,0,0) * vec4(trailWeight * deltaTime));
}