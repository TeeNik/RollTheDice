#pragma once

#include "ofMain.h"


#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

#define WIDTH 20
#define HEIGHT 20
#define NUM_CELLS 20
#define RADIUS 10

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

	ofBufferObject cellsBuffer;
	ofBufferObject trailMapBuffer;

	std::vector<Cell> cells;
	std::vector<Trail> trailMap;

	ofTexture texture;
	ofShader trailMapShader;
	ofShader fragShader;
	
};
