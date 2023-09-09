#pragma once
#include <string>

#include "ofxJSONElement.h"

using std::string;

#define PRESET_DIR "presets/"

class PresetManager
{
public:
	static void savePreset(const string& presetName);
	static void loadPreset(const string& presetName);

	ofxJSONElement jsonElement;

};

