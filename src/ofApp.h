#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxAutoReloadedShader.h"

class ofApp : public ofBaseApp
{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void mouseMoved(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	// enviroment
	// ofCubeMap cubeMap;
	// int cubeMapMode = 3;

	glm::vec3 center = glm::vec3(0, 0, 0);
	ofCamera cam;
	// THING
	ofMesh mesh;
	ofIcoSpherePrimitive ico;
	ofxAutoReloadedShader shader;
	ofFbo fbo;

private:
	bool imGui();
	ofxImGui::Gui gui;
	bool mouseOverGui;
	bool guiVisible;
	// params
	ofParameterGroup param{"Params"};
	ofParameterGroup cameraOps{"Camera-> CTR"};
	ofParameter<float> zoom{"zoom", 10.0, 0.0, 150.0};

	ofParameterGroup shaderOps{"Shader-> CTR"};
	ofParameter<float> speed{"speed", 0.1, 0.001, 1};
	ofParameter<float> perlins{"perlins", 1, 0.001, 1};
	bool fragment = false;

	ofParameterGroup perlin{"Perlin"};
	ofParameter<float> decay{"decay", 0.35, 0, 1.0};
	ofParameter<float> waves{"waves", 2, 0, 100};

	ofParameterGroup colors{"Colors-> CTR"};
	ofParameter<float> eqcolor{"eqColor", 3.0, 0.0, 50.0};
	ofParameter<float> red{"Red", 0.4, 0.0, 1.0};
	ofParameter<float> green{"Green", 0.4, 0.0, 1.0};
	ofParameter<float> blue{"Blue", 0.4, 0.0, 1.0};

	// save data
	string XML_path = "settings.xml";
	void XML_load_app(ofParameterGroup &g, string path);
	void XML_save_app(ofParameterGroup &g, string path);
	// end save data
};
