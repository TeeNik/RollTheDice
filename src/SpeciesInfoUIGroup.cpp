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
	
	// Setup color sliders
	ofParameter<ofColor> param;
	color.setHsb(0, 100, 200);
	param.set(color);
	group.add(colorSlider.setup("Color", param, 100, 255));
	color.setHsb(231, 100, 200);
	param.set(color);
}
