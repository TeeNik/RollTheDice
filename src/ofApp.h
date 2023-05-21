#pragma once

#include "ofMain.h"

#define WIDTH 1080
#define HEIGHT 720

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

	ofBufferObject A1;
	ofBufferObject B1;
	ofBufferObject A2;
	ofBufferObject B2;

	float A1cpu[WIDTH * HEIGHT];
	float B1cpu[WIDTH * HEIGHT];
	float A2cpu[WIDTH * HEIGHT];
	float B2cpu[WIDTH * HEIGHT];

	ofTexture texture;
	ofShader shader;
	
};
