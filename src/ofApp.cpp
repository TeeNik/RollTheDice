#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	shader.setupShaderFromFile(GL_COMPUTE_SHADER, "computeshader.glsl");
	shader.linkProgram();

	texture.allocate(WIDTH, HEIGHT, GL_RGBA8);
	texture.bindAsImage(4, GL_WRITE_ONLY);

	for (int x = 0; x < WIDTH; ++x)
	{
		for (int y = 0; y < HEIGHT; ++y)
		{
			int index = x + y * WIDTH;
			A1cpu[index] = 1.0f;
			A2cpu[index] = 1.0f;

			B1cpu[index] = (rand() / float(RAND_MAX) < 0.000021f) ? 1.0f : 0.0f;
			B2cpu[index] = 0.0f;
		}

		constexpr GLsizeiptr bytes = WIDTH * HEIGHT * sizeof(float);
		A1.allocate(bytes, A1cpu, GL_STATIC_DRAW);
		A2.allocate(bytes, A2cpu, GL_STATIC_DRAW);
		B1.allocate(bytes, B1cpu, GL_STATIC_DRAW);
		B2.allocate(bytes, B2cpu, GL_STATIC_DRAW);

		A1.bindBase(GL_SHADER_STORAGE_BUFFER, 0);
		A2.bindBase(GL_SHADER_STORAGE_BUFFER, 1);
		B1.bindBase(GL_SHADER_STORAGE_BUFFER, 2);
		B2.bindBase(GL_SHADER_STORAGE_BUFFER, 3);
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
}

//--------------------------------------------------------------
void ofApp::draw()
{
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
