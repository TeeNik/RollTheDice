#version 440

struct CellTrail
{
	vec4 value;
};

//layout(binding = 0) buffer trailMapBuffer { CellTrail trailMap[]; };

out vec4 fragColor;
uniform int width;
uniform int height; 
uniform float xRatio; 
uniform float yRatio; 

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
	float x = gl_FragCoord.x / width;
	float y = gl_FragCoord.y / height;
	int idx = int(x) + int(y) * width;

	//vec4 trailVal = vec4(trailMap[idx]);
	
	vec4 backColor = vec4(0,0,0,1);
	vec4 trailColor = vec4(1,1,1,1);

	fragColor = vec4(x, y, 0, 1);
	//fragColor = mix(backColor, trailColor, trailVal);
}