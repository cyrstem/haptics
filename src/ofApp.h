#pragma once

#include "ofMain.h"
#include "ofxImGui.h"

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

private:
	bool imGui();
	ofxImGui::Gui gui;
	bool mouseOverGui;
	bool guiVisible;
};
