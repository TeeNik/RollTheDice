#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	fragShader.load("RectShader/shader");

	trailMapShader.setupShaderFromFile(GL_COMPUTE_SHADER, "TrailMapShader.glsl");
	trailMapShader.linkProgram();

	texture.allocate(WIDTH, HEIGHT, GL_RGBA8);
	texture.bindAsImage(2, GL_WRITE_ONLY);
	texture.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

	const ofVec2f center = ofVec2f(WIDTH / 2, HEIGHT / 2);

	cells.resize(NUM_CELLS);

	for (int i = 0; i < NUM_CELLS; ++i)
	{
		cells[i].pos = glm::vec4(i, i, 0, 0);
		cells[i].vel = glm::vec4(1, 0, 1, 1);
		//cells[i].angle = 10;
	}

	//for (Cell& agent : cells)
	//{
	//	const float dist = ofRandom(RADIUS);
	//	const float angle = ofRandom(359);
	//
	//	const ofVec2f dir = ofVec2f(cos(angle), sin(angle));
	//	const ofVec2f point = center + dir * dist;
	//
	//	agent.pos = point;
	//	agent.angle = angle;
	//}

	cellsBuffer.allocate(cells, GL_DYNAMIC_DRAW);
	cellsBuffer.bindBase(GL_SHADER_STORAGE_BUFFER, 0);

	trailMap.resize(WIDTH * HEIGHT);
	for (int i = 0; i < WIDTH; ++i)
	{
		for (int j = 0; j < HEIGHT; ++j)
		{
			int id = i + j * WIDTH;
			trailMap[id].value = (i == j) ? ofVec4f(1, 0, 0, 1) : ofVec4f(0,0,0,1);
		}
	}

	trailMapBuffer.allocate(trailMap, GL_DYNAMIC_DRAW);
	trailMapBuffer.bindBase(GL_SHADER_STORAGE_BUFFER, 1);
}

//--------------------------------------------------------------
void ofApp::update()
{
	trailMapShader.begin();
	trailMapShader.setUniform1i("width", WIDTH);
	trailMapShader.setUniform1i("height", HEIGHT);
	trailMapShader.setUniform1i("numOfCells", NUM_CELLS);
	trailMapShader.setUniform1f("moveSpeed", 1.0f);
	trailMapShader.dispatchCompute(WIDTH / 20, HEIGHT / 20, 1);
	trailMapShader.end();
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

	texture.draw(0, 0, 600, 600);
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
