#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#define TEXTURE_WIDTH 1280
#define TEXTURE_HEIGHT 720

#define GUI_WIDTH 200

#define SCREEN_WIDTH (TEXTURE_WIDTH + GUI_WIDTH)
#define SCREEN_HEIGHT TEXTURE_HEIGHT

#define WIDTH 1280
#define HEIGHT 720
#define NUM_CELLS 100000
#define RADIUS 30

struct Cell
{
	glm::vec2 pos;
	glm::vec2 vel;
	//float angle;
};

struct Trail
{
	ofVec4f value {0,0,0,1};
};

struct SimSettings
{
	float MoveSpeed = 80.0f;
	float TurnSpeed = 30.0f;

	float SenseDistance = 20.0f;
	float SenseWeight = 3.0f;
	float SenseAngle = 0.4f;
	int SensorSize = 1;

	float EvaporateSpeed = 0.25f;
	float DiffuseSpeed = 10.0f;
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

	ofBufferObject cellsBuffer;
	ofBufferObject trailMapBuffer;

	std::vector<Cell> cells;
	std::vector<Trail> trailMap;

	ofTexture texture;
	ofShader cellsShader;
	ofShader trailMapShader;
	ofShader drawShader;
	ofShader fragShader;

	ofxPanel gui;
	ofxFloatSlider speedSlider;
	ofxFloatSlider turnSpeedSlider;
	ofxFloatSlider senseDistanceSlider;
	ofxFloatSlider senseWeightSlider;
	ofxFloatSlider senseAngleSlider;
	ofxIntSlider sensorSizeSlider;
	ofxFloatSlider evaporationSpeedSlider;
	ofxFloatSlider diffuseSpeedSlider;
	ofxColorSlider colorSlider;
	ofColor color;

	SimSettings simSettings;

};