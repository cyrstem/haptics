#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofDisableArbTex();
    ofSetBackgroundColor(25);
    ofSetWindowTitle("--HAPTICS--");
    ofSetFrameRate(60.0f);
    cam.setNearClip(10);
    // center = glm::vec3(0, 0, 0);

    cam.setPosition(0, 45, 400);

    cubeMap.load("loc00184-22-8k.exr", 512, true);

    // thing
    sphere.set(40, 24);
    cam.lookAt(sphere.getPosition());
}

//--------------------------------------------------------------
void ofApp::update()
{
    // ofBackgroundGradient(ofFloatColor(1.0,0.0,0.0),ofFloatColor(0.0,0.0,0.0),OF_GRADIENT_CIRCULAR);
}

//--------------------------------------------------------------
void ofApp::draw()
{
    //cubeMap.drawPrefilteredCube(0.00f);
    //cubeMap.drawIrradiance();

    ofEnableDepthTest();
    cam.begin();
    mat.begin();
    mat.setRoughness(0.03f);
    mat.setReflectance(2.0f);
    mat.setMetallic(2.0);
    mat.setDiffuseColor(ofFloatColor(0.07, 0.16, 0.11, 1.0));
    mat.setDiffuseColor(ofFloatColor(0.0, 3.0));
    sphere.draw();
    mat.end();
    cam.end();
    ofDisableDepthTest();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key)
    {
    case OF_KEY_TAB:
        ofLog() << "hide UI";
        break;

    case OF_KEY_RETURN:
        ofToggleFullscreen();
        break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}

//--------------------------------------------------------------
void ofApp::XML_load_app(ofParameterGroup &g, string path)
{
    ofLogNotice("ofApp") << "XML_load_app" << path;
    ofXml settings;
    settings.load(path);
    ofDeserialize(settings, g);
}
//--------------------------------------------------------------
void ofApp::XML_save_app(ofParameterGroup &g, string path)
{
    ofLogNotice("ofApp") << "XML_save_app" << path;
    ofXml settings;
    ofSerialize(settings, g);
    settings.save(path);
}
