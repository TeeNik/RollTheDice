#pragma once
#include <string>

using std::string;

#define PRESET_DIR "presets/"

class PresetManager
{
public:
	static void savePreset(const string& presetName);
	static void loadPreset(const string& presetName);

};

