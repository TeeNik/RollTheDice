#pragma once

#include "ofMain.h"


#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

#define WIDTH 1080
#define HEIGHT 720
#define NUM_CELL 10000

struct Cell
{
	ofVec2f pos;
	float angle;
};

struct Trail
{
	ofVec4f value;
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
