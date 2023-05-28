#version 440

struct Trail
{
	vec4 value;
};

layout(binding = 1) buffer trailMapBuffer { Trail trailMap[]; };

out vec4 fragColor;
uniform int width;
uniform int height; 
uniform float xRatio; 
uniform float yRatio; 

uniform int gridSize;
uniform int cellSize;

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
	// 0..1
	//float x = gl_FragCoord.x / width;
	//float y = gl_FragCoord.y / height;

	//float x = gl_FragCoord.x / cellSize;
	//float y = gl_FragCoord.y / cellSize;
	int numCells = width / cellSize;

	float x = gl_FragCoord.x;
	float y = gl_FragCoord.y;

	int idx = int(x) + int(y) * width;

	vec4 trailVal = vec4(trailMap[idx]);
	
	vec4 backColor = vec4(0,0,0,1);
	vec4 trailColor = vec4(1,1,0,1);

	//fragColor = vec4(int(x) / float(numCells), int(y) / float(numCells), 0, 1);
	fragColor = mix(backColor, trailColor, trailVal);
}