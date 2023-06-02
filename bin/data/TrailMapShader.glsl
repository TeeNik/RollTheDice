#version 440

struct Trail
{
	vec4 value;
};

layout(std140, binding = 1) buffer trailMapBuffer { Trail trailMap[]; };
layout(local_size_x = 10, local_size_y = 10, local_size_z = 1) in;

uniform int width;
uniform int height; 
uniform float evaporateSpeed; 
uniform float deltaTime; 

void main()
{
	int i, j;
	i = int(gl_GlobalInvocationID.x);
	j = int(gl_GlobalInvocationID.y);

	int idx = i + j * width;

	vec4 currValue = trailMap[idx].value;
	float evaporatedAmount = evaporateSpeed * deltaTime;
	vec4 delta = vec4(evaporatedAmount, evaporatedAmount, evaporatedAmount, 1);
	vec4 newValue = max(vec4(0,0,0,1), currValue - delta);
	trailMap[idx].value = newValue;
}