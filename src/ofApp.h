#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxUbo.h"
#include "SpeciesInfoUIGroup.h"
#include "SpeciesSettings.h"

#define TEXTURE_WIDTH 1280
#define TEXTURE_HEIGHT 720

#define GUI_WIDTH 200

#define SCREEN_WIDTH (TEXTURE_WIDTH + GUI_WIDTH)
#define SCREEN_HEIGHT TEXTURE_HEIGHT

//If WIDTH and HEIGHT are smaller that texture size, image will be pixelated
#define WIDTH 1280
#define HEIGHT 720
#define RADIUS (HEIGHT / 2)

#define NUM_CELLS 1000000

//I used vec4 to keep correct memory layout of struct
struct Cell
{
	glm::vec4 pos;
	glm::vec4 vel;
	glm::vec4 speciesMask;
	glm::ivec4 speciesIndex {1, 1, 0, 0};
};

struct Trail
{
	glm::vec4 value {0,0,0,1};
};

struct SimSettings
{
	float MoveSpeed = 80.0f;
	float TurnSpeed = 30.0f;

	float SenseDistance = 20.0f;
	float SenseAngle = 30.0f;
	int SensorSize = 1;

	float EvaporateSpeed = 0.25f;
	float DiffuseSpeed = 10.0f;
	float TrailWeight = 1.0f;
};

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

private:
	void setupCells();
	void setupShaders();
	void setupGui();

	void updateSettings();
	void reset();

	ofBufferObject cellsBuffer;
	ofBufferObject trailMapBuffer;

	std::vector<Cell> cells;
	std::vector<Trail> trailMap;
	//std::vector<SpeciesSettings> speciesSettings;

	ofTexture texture;
	ofxUboShader cellsShader;
	ofShader trailMapShader;
	ofShader drawShader;
	ofShader fragShader;

	ofxPanel gui;
	ofxFloatSlider speedSlider;
	ofxFloatSlider turnSpeedSlider;
	ofxFloatSlider senseDistanceSlider;
	ofxFloatSlider senseAngleSlider;
	ofxIntSlider sensorSizeSlider;
	ofxFloatSlider evaporationSpeedSlider;
	ofxFloatSlider diffuseSpeedSlider;
	ofxFloatSlider trailWeightSlider;
	ofxColorSlider colorSlider;
	ofColor color;


	SpeciesInfoUIGroup speciesSettingsGUI[MAX_SPECIES];
	SpeciesInfo speciesSettings[MAX_SPECIES];
	//SpeciesSettings speciesSettings;

	int numTeams = 1;

	SimSettings simSettings;

	void passSpeciesSettingsToShader(int speciesIndex, const SpeciesInfo& info);

};