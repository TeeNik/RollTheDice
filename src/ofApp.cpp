#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(60);
	ofBackground(ofColor::black);

	setupCells();
	setupShaders();
	setupGui();
}

void ofApp::setupCells()
{
	cells.resize(NUM_CELLS);

	const ofVec2f center = ofVec2f(WIDTH / 2, HEIGHT / 2);
	for (Cell& agent : cells)
	{
		const float dist = ofRandom(RADIUS);
		const float angle = ofRandom(359);

		const glm::vec2 dir = glm::vec2(cos(angle), sin(angle));
		const glm::vec2 point = center + dir * dist;

		agent.pos = point;
		agent.vel = glm::vec2(angle + 180, 0.0f);
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

	cellsBuffer.allocate(cells, GL_DYNAMIC_DRAW);
	cellsBuffer.bindBase(GL_SHADER_STORAGE_BUFFER, 0);

	trailMapBuffer.allocate(trailMap, GL_DYNAMIC_DRAW);
	trailMapBuffer.bindBase(GL_SHADER_STORAGE_BUFFER, 1);

	texture.allocate(WIDTH, HEIGHT, GL_RGBA8);
	texture.bindAsImage(2, GL_WRITE_ONLY);
	texture.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
}

void ofApp::setupGui()
{
	gui.setup();
	// Setup parameter sliders
	gui.add(speedSlider.setup("Speed", simSettings.MoveSpeed, 0, 100));
	gui.add(turnSpeedSlider.setup("Turn Speed", simSettings.TurnSpeed, 0, 100));
	gui.add(senseDistanceSlider.setup("Sense Distance", simSettings.SenseDistance, 1, 100));
	gui.add(senseWeightSlider.setup("Sense Weight", simSettings.SenseWeight, 0, 5));
	gui.add(senseAngleSlider.setup("Sense Angle", simSettings.SenseAngle, 0.0f, 360.0f));
	gui.add(sensorSizeSlider.setup("Sensor Size", simSettings.SensorSize, 0, 4));
	gui.add(evaporationSpeedSlider.setup("Evaporation Speed", simSettings.EvaporateSpeed, 0.0f, 2));
	gui.add(diffuseSpeedSlider.setup("Diffuse", simSettings.DiffuseSpeed, 0, 50));
	gui.add(trailWeightSlider.setup("Trail Weight", simSettings.TrailWeight, 0, 5));
	
	// Setup color sliders
	ofParameter<ofColor> param;
	color.setHsb(0, 100, 200);
	param.set(color);
	gui.add(colorSlider.setup("Color", param, 100, 255));
	color.setHsb(231, 100, 200);
	param.set(color);

	ofSetWindowTitle("Slime Mold");
	gui.setPosition(ofGetWidth() - GUI_WIDTH, 10);
}

void ofApp::updateSettings()
{
	simSettings.MoveSpeed = speedSlider;
	simSettings.TurnSpeed = turnSpeedSlider;
	simSettings.SenseDistance = senseDistanceSlider;
	simSettings.SenseAngle = senseAngleSlider;
	simSettings.SensorSize = sensorSizeSlider;
	simSettings.EvaporateSpeed = evaporationSpeedSlider;
	simSettings.DiffuseSpeed = diffuseSpeedSlider;
	simSettings.TrailWeight = trailWeightSlider;
	color = colorSlider;
}

void ofApp::reset()
{
	setupCells();
	cellsBuffer.updateData(cells);
	trailMapBuffer.updateData(trailMap);
}

//--------------------------------------------------------------
void ofApp::update()
{
	updateSettings();

	trailMapShader.begin();
	trailMapShader.setUniform1i("width", WIDTH);
	trailMapShader.setUniform1i("height", HEIGHT);
	trailMapShader.setUniform1f("evaporateSpeed", simSettings.EvaporateSpeed);
	trailMapShader.setUniform1f("diffuseSpeed", simSettings.DiffuseSpeed);
	trailMapShader.setUniform1f("deltaTime", ofGetLastFrameTime());
	trailMapShader.dispatchCompute((WIDTH * HEIGHT + 1024 - 1) / 1024, 1, 1);
	trailMapShader.end();

	cellsShader.begin();
	cellsShader.setUniform1i("width", WIDTH);
	cellsShader.setUniform1i("height", HEIGHT);
	cellsShader.setUniform1i("numOfCells", NUM_CELLS);
	cellsShader.setUniform1f("moveSpeed", simSettings.MoveSpeed);
	cellsShader.setUniform1f("time", ofGetElapsedTimef());
	cellsShader.setUniform1f("deltaTime", ofGetLastFrameTime());

	cellsShader.setUniform1f("senseDistance", simSettings.SenseDistance);
	cellsShader.setUniform1f("senseAngle", simSettings.SenseAngle);
	cellsShader.setUniform1f("turnSpeed", simSettings.TurnSpeed);
	cellsShader.setUniform1i("sensorSize", simSettings.SensorSize);
	cellsShader.setUniform1f("trailWeight", simSettings.TrailWeight);
	cellsShader.dispatchCompute((cells.size() + 1024 - 1) / 1024, 1, 1);

	SpeciesSettings settings;
	settings.MoveSpeed = 0.0f;
	settings.TurnSpeed = 0.5f;
	cellsShader.setUniformBuffer("SpeciesSettings", settings);
	cellsShader.end();

	drawShader.begin();
	drawShader.setUniform1i("width", WIDTH);
	drawShader.setUniform1i("height", HEIGHT);
	drawShader.setUniform4f("cellColor", color);
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

	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	if (key == 'r')
	{
		reset();
	}
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
