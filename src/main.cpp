#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main()
{
	ofGLWindowSettings settings;
	settings.setSize(WIDTH, HEIGHT);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}
