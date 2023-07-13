#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(60);
	ofBackground(ofColor::black);

	setupGui();
	setupCells();
	setupShaders();
}

void ofApp::setupCells()
{
	countNumOfTeams();
	cells.resize(NUM_CELLS);

	constexpr glm::vec2 center = glm::vec2(WIDTH / 2, HEIGHT / 2);

	for (Cell& cell : cells)
	{
		glm::vec2 startPos { 0, 0 };
		float angle = ofRandomuf() * PI * 2;

		if (simSettings.spawnMode == Point)
		{
			startPos = center;
		}
		else if (simSettings.spawnMode == Random)
		{
			startPos = { ofRandom(WIDTH), ofRandom(HEIGHT) };
		}
		else if (simSettings.spawnMode == RandomCircle)
		{
			const float radius = ofRandomf() * HEIGHT * 0.15f;
			startPos = center + glm::vec2{ cos(angle) * radius, sin(angle) * radius };
		}
		else if (simSettings.spawnMode == CircleIn)
		{
			const float radius = ofRandomf() * HEIGHT * 0.49f;
			startPos = center + glm::vec2{ cos(angle) * radius, sin(angle) * radius };
			const glm::vec2 dir = normalize(center - startPos);
			angle = atan2(dir.y, dir.x);
		}

		cell.pos = glm::vec4(startPos.x, startPos.y, 0, 0);
		cell.vel = glm::vec4(angle, 0.0f, 0.0f, 0.0f);

		const int team = static_cast<int>(ofRandom(0, numTeams));
		cell.speciesMask.r = team == 0;
		cell.speciesMask.g = team == 1;
		cell.speciesMask.b = team == 2;
		cell.speciesMask.a = team > 2;
		cell.speciesIndex.r = team;
	}

	trailMap.resize(WIDTH * HEIGHT);
}

void ofApp::setupShaders()
{
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

	loadPresetButton.addListener(this, &ofApp::loadPreset);
	savePresetButton.addListener(this, &ofApp::savePreset);

	gui.add(loadPresetButton.setup("Load Preset"));
	gui.add(savePresetButton.setup("Save Preset"));
	gui.add(evaporationSpeedSlider.setup("Evaporation Speed", simSettings.EvaporateSpeed, 0.0f, 2));
	gui.add(diffuseSpeedSlider.setup("Diffuse", simSettings.DiffuseSpeed, 0, 50));
	gui.add(trailWeightSlider.setup("Trail Weight", simSettings.TrailWeight, 0, 20));

	for (int i = 0; i < MAX_SPECIES; ++i)
	{
		speciesSettingsGUI[i].setup(gui, speciesSettings[i], i);
	}

	ofSetWindowTitle("Slime Mold");
	gui.setPosition(ofGetWidth() - GUI_WIDTH, 10);
}

void ofApp::updateSettings()
{
	simSettings.EvaporateSpeed = evaporationSpeedSlider;
	simSettings.DiffuseSpeed = diffuseSpeedSlider;
	simSettings.TrailWeight = trailWeightSlider;

	for (int i = 0; i < MAX_SPECIES; ++i)
	{
		speciesSettingsGUI[i].updateInfo(speciesSettings[i]);
	}
}

void ofApp::reset()
{
	setupCells();
	cellsBuffer.updateData(cells);
	trailMapBuffer.updateData(trailMap);
}

void ofApp::loadPreset()
{
	std::cout << "load preset\n";
}

void ofApp::savePreset()
{
}

void ofApp::passSpeciesSettingsToShader(ofShader& shader, int speciesIndex, const SpeciesInfo& info)
{
	const std::string name = "speciesSettings[" + std::to_string(speciesIndex) + "].";
	shader.setUniform1f(name + "moveSpeed", info.moveSpeed);
	shader.setUniform1f(name + "turnSpeed", info.turnSpeed);
	shader.setUniform1f(name + "senseDistance", info.senseDistance);
	shader.setUniform1f(name + "senseAngle", info.senseAngle);
	shader.setUniform1i(name + "sensorSize", info.sensorSize);
	shader.setUniform4f(name + "color", info.color);
}

void ofApp::countNumOfTeams()
{
	numTeams = 0;
	for (auto& species : speciesSettingsGUI)
	{
		if (species.isActive())
		{
			++numTeams;
		}
	}
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
	cellsShader.setUniform1f("time", ofGetElapsedTimef());
	cellsShader.setUniform1f("deltaTime", ofGetLastFrameTime());
	cellsShader.setUniform1f("trailWeight", simSettings.TrailWeight);

	for (int i = 0; i < MAX_SPECIES; ++i)
	{
		passSpeciesSettingsToShader(cellsShader, i, speciesSettings[i]);
	}

	cellsShader.dispatchCompute((cells.size() + 1024 - 1) / 1024, 1, 1);
	cellsShader.end();

	drawShader.begin();
	drawShader.setUniform1i("width", WIDTH);
	drawShader.setUniform1i("height", HEIGHT);

	for (int i = 0; i < MAX_SPECIES; ++i)
	{
		passSpeciesSettingsToShader(drawShader, i, speciesSettings[i]);
	}

	drawShader.dispatchCompute(WIDTH / 1, HEIGHT / 1, 1);
	drawShader.end();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	texture.draw(0, 0, TEXTURE_WIDTH, TEXTURE_HEIGHT);
	gui.draw();
}

void ofApp::exit()
{
	loadPresetButton.removeListener(this, &ofApp::loadPreset);
	savePresetButton.removeListener(this, &ofApp::savePreset);
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
