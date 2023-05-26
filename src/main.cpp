#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main()
{
	ofGLWindowSettings settings;
	settings.setSize(1080, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}
