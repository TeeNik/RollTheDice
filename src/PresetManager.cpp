#include "PresetManager.h"
#include <ofFileUtils.h>

void PresetManager::savePreset(const std::string& presetName)
{
	const string filePath = PRESET_DIR + presetName + ".json";
	ofFile file(filePath);

	Json::Value ev;
	ev["Account"]["name"] = "John123";
	ev["Account"]["surname"] = "Smith";

	std::cout << ev << std::endl;

	ofxJSONElement json(ev);
	bool result = json.save("test.json");

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
