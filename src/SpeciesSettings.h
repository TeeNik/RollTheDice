#pragma once

#define MAX_SPECIES 4

struct SpeciesInfo
{
	float MoveSpeed = 80.0f;
	float TurnSpeed = 30.0f;
	float SenseDistance = 20.0f;
	float SenseAngle = 30.0f;
	int SensorSize = 1;
};

struct SpeciesSettings
{
	SpeciesInfo Species[MAX_SPECIES];
};