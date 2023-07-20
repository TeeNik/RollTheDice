#include "PresetManager.h"
#include <ofFileUtils.h>

void PresetManager::savePreset(const std::string& presetName)
{
	const string filePath = PRESET_DIR + presetName + ".json";
	ofFile file(filePath);

	if (!file.exists()) {
		std::cout << "The file " + filePath + " is missing\n";
		file.create();
	}
	else
	{
		std::cout << "The file " + filePath + " is found\n";
	}
}

void PresetManager::loadPreset(const std::string& presetName)
{
}
