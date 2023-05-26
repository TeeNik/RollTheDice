#pragma once

#include "ofMain.h"


#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

#define WIDTH 100
#define HEIGHT 100
#define NUM_AGENTS 100

struct Agent
{
	ofVec2f pos;
	float angle;
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

	ofBufferObject agentsBuffer;

	std::vector<Agent> agents;

	ofTexture texture;
	ofShader shader;
	
};
