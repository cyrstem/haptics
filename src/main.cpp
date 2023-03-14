#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofGLFWWindowSettings settings;
	settings.setGLVersion(3,2);
	settings.setSize(1200, 1000);
	settings.numSamples =4;
	ofCreateWindow(settings);
	ofRunApp(new ofApp());

}
