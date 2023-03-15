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
	ofCubeMap cubeMap;
	int cubeMapMode = 3;
	ofEasyCam cam;
	// thing
	ofSpherePrimitive sphere;
	ofMaterial mat;
	//ofShader shader,shader2;
	ofxAutoReloadedShader shader,shader2;
	ofFbo fbo;


private:
	bool imGui();
	ofxImGui::Gui gui;
	bool mouseOverGui;
	bool guiVisible;
	// params
	ofParameterGroup param{"Params"};
	ofParameterGroup cameraOps{"Camera-> CTR"};

	ofParameterGroup shaderOps{"Shader-> CTR"};
	ofParameter<float> xFreq{"freq X", 10, 0, 128};
	ofParameter<float> yFreq{"freq Y", 8, 0, 128};
	ofParameter<float> zFreq{"freq Z", 7, 0, 128};
	ofParameter<float> xDepth{"Depth X", 0.15, 0, 2.0};
	ofParameter<float> yDepth{"Depth Y", 0.12, 0, 2.0};
	ofParameter<float> zDepth{"Depth Z", 0.18, 0.0, 2.0};

	ofParameter<float> reflect{"Reflectance", 0.3, 0.0, 2.0};
	ofParameter<float> roughtness{"Roghtness", 0.03, 0.0, 2.0};
	ofParameter<float> metallic{"Metallic", 0.0, 0.0, 2.0};

	ofParameterGroup colors{"ColorMaterial-> CTR"};
	ImVec4 diff_val = ImVec4(0.07f, 0.16f, 0.11f, 1.f);



	// save data
	string XML_path = "settings.xml";
	void XML_load_app(ofParameterGroup &g, string path);
	void XML_save_app(ofParameterGroup &g, string path);
	void save();
	// end save data
};
