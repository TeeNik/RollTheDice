#include "PresetManager.h"
#include <ofFileUtils.h>

#include "ofApp.h"

void PresetManager::savePreset(const string& presetName, const SimSettings& simSettings, const SpeciesInfo* speciesSettings)
{
	const string filePath = PRESET_DIR + presetName + ".json";
	ofFile file(filePath);

	Json::Value ev;
	ev["Account"]["name"] = "John123";
	ev["Account"]["surname"] = "Smith";

	if (!file.exists()) {
		std::cout << "The file " + filePath + " is missing\n";
		file.create();
	}
	else
	{
		std::cout << "The file " + filePath + " is found\n";
	}

	ev[presetName]["EvaporateSpeed"] = simSettings.EvaporateSpeed;
	ev[presetName]["DiffuseSpeed"] = simSettings.DiffuseSpeed;
	ev[presetName]["TrailWeight"] = simSettings.TrailWeight;
	ev[presetName]["NumOfTeams"] = simSettings.NumOfTeams;

	for (int i = 0; i < MAX_SPECIES; ++i)
	{
		std::string speciesName = "Species " + std::to_string(i);

		//ev[presetName][speciesName]["isOnToggle"] = speciesSettings[i].isOnToggle;
		ev[presetName][speciesName]["moveSpeed"] = speciesSettings[i].moveSpeed;
		ev[presetName][speciesName]["turnSpeed"] = speciesSettings[i].turnSpeed;
		ev[presetName][speciesName]["senseDistance"] = speciesSettings[i].senseDistance;
		ev[presetName][speciesName]["senseAngle"] = speciesSettings[i].senseAngle;
		ev[presetName][speciesName]["sensorSize"] = speciesSettings[i].sensorSize;
		ev[presetName][speciesName]["color"]["r"] = speciesSettings[i].color.r;
		ev[presetName][speciesName]["color"]["g"] = speciesSettings[i].color.g;
		ev[presetName][speciesName]["color"]["b"] = speciesSettings[i].color.b;
		ev[presetName][speciesName]["color"]["a"] = speciesSettings[i].color.a;
	}


	std::cout << ev << std::endl;

	ofxJSONElement json(ev);
	bool result = json.save(filePath);

	if (!file.exists()) {
		std::cout << "The file " + filePath + " is missing\n";
		file.create();
	}
	else
	{
		std::cout << "The file " + filePath + " is found\n";
	}

	//file.write(ev.asString().c_str(), ev.asString().size());
}

void PresetManager::loadPreset(const std::string& presetName)
{
}
