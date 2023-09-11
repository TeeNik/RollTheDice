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
