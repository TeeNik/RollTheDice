#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	fragShader.load("shader");

	trailMapShader.setupShaderFromFile(GL_COMPUTE_SHADER, "TrailMapShader.glsl");
	trailMapShader.linkProgram();

	texture.allocate(WIDTH, HEIGHT, GL_RGBA8);
	texture.bindAsImage(2, GL_WRITE_ONLY);
	texture.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

	constexpr int radius = 15;
	ofVec2f center = ofVec2f(WIDTH / 2, HEIGHT / 2);

	cells.resize(NUM_CELL);
	for (Cell& agent : cells)
	{
		const float dist = ofRandom(radius);
		const float angle = ofRandom(359);

		const ofVec2f dir = ofVec2f(cos(angle), sin(angle));
		const ofVec2f point = center + dir * dist;

		agent.pos = point;
		agent.angle = angle;
	}

	cellsBuffer.allocate(cells, GL_DYNAMIC_DRAW);
	cellsBuffer.bindBase(GL_SHADER_STORAGE_BUFFER, 0);

	trailMap.resize(WIDTH * HEIGHT);
	//trailMap.resize(NUM_CELL);

	//for (auto& trail : trailMap)
	//{
	//	trail.value.set(0.5f);
	//}

	trailMapBuffer.allocate(trailMap, GL_DYNAMIC_DRAW);
	trailMapBuffer.bindBase(GL_SHADER_STORAGE_BUFFER, 1);
}

//--------------------------------------------------------------
void ofApp::update()
{
	trailMapShader.begin();
	trailMapShader.setUniform1i("width", WIDTH);
	trailMapShader.setUniform1i("height", HEIGHT);
	trailMapShader.setUniform1f("moveSpeed", 1.0f);
	trailMapShader.dispatchCompute(WIDTH / 20, HEIGHT / 20, 1);
	trailMapShader.end();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	fragShader.begin();
	fragShader.setUniform1i("width", WIDTH);
	fragShader.setUniform1i("height", HEIGHT);
	fragShader.setUniform1i("cellSize", 60);
	fragShader.setUniform1f("xRatio", 1.0f);
	fragShader.setUniform1f("yRatio", 1.0f);
	
	ofDrawRectangle(0, 0, WIDTH, HEIGHT);
	fragShader.end();

	//texture.draw(0, 0, 600, 600);
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
