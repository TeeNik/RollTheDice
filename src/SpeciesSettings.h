#pragma once

#define MAX_SPECIES 4

struct SpeciesInfo
{
	float MoveSpeed;
	float TurnSpeed;
	float SenseDistance;
	float SenseAngle;
	int SensorSize;
};

struct SpeciesSettings
{
	SpeciesInfo Species[MAX_SPECIES];
};