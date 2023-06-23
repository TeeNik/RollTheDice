#include "SpeciesInfoUIGroup.h"
#include "SpeciesSettings.h"

void SpeciesInfoUIGroup::setup(ofxPanel& panel, const SpeciesInfo& info)
{
	panel.add(group.setup("Collection"));
	group.add(speedSlider.setup("Speed", info.MoveSpeed, 0, 100));
	group.add(turnSpeedSlider.setup("Turn Speed", info.TurnSpeed, 0, 100));
	group.add(senseDistanceSlider.setup("Sense Distance", info.SenseDistance, 1, 100));
	group.add(senseAngleSlider.setup("Sense Angle", info.SenseAngle, 0.0f, 360.0f));
	group.add(sensorSizeSlider.setup("Sensor Size", info.SensorSize, 0, 4));
}
