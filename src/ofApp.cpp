#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(60);
	ofBackground(ofColor::black);

	setupCells();
	setupShaders();
}

void ofApp::setupCells()
{
	const ofVec2f center = ofVec2f(WIDTH / 2, HEIGHT / 2);
	cells.resize(NUM_CELLS);
	for (Cell& agent : cells)
	{
		const float dist = ofRandom(RADIUS);
		const float angle = ofRandom(359);

		const glm::vec2 dir = glm::vec2(cos(angle), sin(angle));
		const glm::vec2 point = center + dir * dist;

		agent.pos = point;
		agent.vel = glm::vec2(angle, 0.0f);
	}

	trailMap.resize(WIDTH * HEIGHT);
}

void ofApp::setupShaders()
{
	fragShader.load("RectShader/shader");
	drawShader.setupShaderFromFile(GL_COMPUTE_SHADER, "DrawShader.glsl");
	drawShader.linkProgram();

	cellsShader.setupShaderFromFile(GL_COMPUTE_SHADER, "CellsShader.glsl");
	cellsShader.linkProgram();

	trailMapShader.setupShaderFromFile(GL_COMPUTE_SHADER, "TrailMapShader.glsl");
	trailMapShader.linkProgram();

	texture.allocate(WIDTH, HEIGHT, GL_RGBA8);
	texture.bindAsImage(2, GL_WRITE_ONLY);
	texture.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

	cellsBuffer.allocate(cells, GL_DYNAMIC_DRAW);
	cellsBuffer.bindBase(GL_SHADER_STORAGE_BUFFER, 0);

	trailMapBuffer.allocate(trailMap, GL_DYNAMIC_DRAW);
	trailMapBuffer.bindBase(GL_SHADER_STORAGE_BUFFER, 1);
}

//--------------------------------------------------------------
void ofApp::update()
{
	trailMapShader.begin();
	trailMapShader.setUniform1i("width", WIDTH);
	trailMapShader.setUniform1i("height", HEIGHT);
	trailMapShader.setUniform1f("evaporateSpeed", 0.25f);
	trailMapShader.setUniform1f("diffuseSpeed", 10.f);
	trailMapShader.setUniform1f("deltaTime", ofGetLastFrameTime());
	trailMapShader.dispatchCompute((WIDTH * HEIGHT + 1024 - 1) / 1024, 1, 1);
	trailMapShader.end();

	cellsShader.begin();
	cellsShader.setUniform1i("width", WIDTH);
	cellsShader.setUniform1i("height", HEIGHT);
	cellsShader.setUniform1i("numOfCells", NUM_CELLS);
	cellsShader.setUniform1f("moveSpeed", 80.0f);
	cellsShader.setUniform1f("time", ofGetElapsedTimef());
	cellsShader.setUniform1f("deltaTime", ofGetLastFrameTime());

	cellsShader.setUniform1f("sensorDistance", 20.0f);
	cellsShader.setUniform1f("senseAngle", 0.4f);
	cellsShader.setUniform1f("turnSpeed", 30.6f);
	cellsShader.setUniform1f("senseWeight", 3.0f);
	cellsShader.setUniform1i("sensorSize", 1);
	cellsShader.dispatchCompute((cells.size() + 1024 - 1) / 1024, 1, 1);
	cellsShader.end();

	drawShader.begin();
	drawShader.setUniform1i("width", WIDTH);
	drawShader.setUniform1i("height", HEIGHT);
	drawShader.dispatchCompute(WIDTH / 1, HEIGHT / 1, 1);
	drawShader.end();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	//fragShader.begin();
	//fragShader.setUniform1i("width", WIDTH);
	//fragShader.setUniform1i("height", HEIGHT);
	//fragShader.setUniform1i("cellSize", 60);
	//fragShader.setUniform1f("xRatio", 1.0f);
	//fragShader.setUniform1f("yRatio", 1.0f);
	//ofDrawRectangle(0, 0, WIDTH, HEIGHT);
	//fragShader.end();

	texture.draw(0, 0, TEXTURE_WIDTH, TEXTURE_HEIGHT);
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
