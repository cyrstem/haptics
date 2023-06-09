#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofDisableArbTex();
    ofSetBackgroundColor(25);
    ofSetWindowTitle("--HAPTICS--");
    ofSetFrameRate(60.0f);
    cam.setNearClip(10);
    cam.setPosition(0, 45, 100);

    cubeMap.load("loc00184-22-8k.exr", 512, true);

    // thing
    sphere.set(40, 24);
    cam.lookAt(sphere.getPosition());

    this->gui.setup();
    // gui.setTheme(new MyTheme());
    this->guiVisible = true;

    // shader
    shader.load("shader");
    shader2.load("s");

    ofFboSettings p;
    p.width = 256;
    p.height = 256;
    p.internalformat = GL_RGBA;
    p.maxFilter = GL_LINEAR;
    p.minFilter = GL_LINEAR;
    p.numSamples = 3;
    p.useDepth = true;
    p.useStencil = true;
    p.wrapModeHorizontal = GL_CLAMP_TO_EDGE;
    p.wrapModeVertical = GL_CLAMP_TO_EDGE;

    fbo.allocate(p);
    fbo.begin();
    ofClear(255, 255, 255, 0);
    fbo.end();

    // save
    param.add(xFreq);
    param.add(yFreq);
    param.add(zFreq);
    param.add(xDepth);
    param.add(yDepth);
    param.add(zDepth);
    param.add(reflect);
    param.add(roughtness);
    param.add(metallic);
    XML_load_app(param, XML_path);
}

//--------------------------------------------------------------
void ofApp::update()
{
    fbo.begin();
    ofClear(255, 255, 255, 0);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    // cubeMap.drawPrefilteredCube(0.00f);
    // cubeMap.drawIrradiance();
    fbo.begin();
    shader2.begin();
    shader2.setUniform1f("u_time",ofGetElapsedTimef());
    shader2.setUniform2f("u_resolution", 400,400);
    ofDrawRectangle(0, 0, 400, 400);
    shader2.end();
    fbo.end();
    fbo.draw(0, 0);

    ofEnableDepthTest();
    cam.begin();
    // shader.begin();
    // shader.setUniform1f("time", ofGetElapsedTimef());
    // shader.setUniform3f("freq", xFreq, yFreq, zFreq);
    // shader.setUniformTexture("fboTex", fbo.getTexture(0), 0);
    // shader.setUniform3f("depth", xDepth, yDepth, zDepth);
    mat.begin();
    mat.setRoughness(roughtness);
    mat.setReflectance(reflect);
    mat.setMetallic(metallic);
    mat.setDiffuseColor(ofFloatColor(0.7, 0.16, 0.11, 1.0));
    mat.setDiffuseColor(ofFloatColor(0.0, 6.0));

    sphere.draw();

    mat.end();
    shader.end();
    cam.end();
    ofDisableDepthTest();

    this->mouseOverGui = false;
    if (this->guiVisible)
    {
        this->mouseOverGui = this->imGui();
    }
    if (this->mouseOverGui)
    {
        this->cam.disableMouseInput();
    }
    else
    {
        this->cam.enableMouseInput();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key)
    {
    case OF_KEY_TAB:
        ofLog() << "hide UI";
        guiVisible = !guiVisible;
        break;

    case OF_KEY_RETURN:
        ofToggleFullscreen();
        break;
    case 's':
        XML_save_app(param,XML_path);
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
bool ofApp::imGui()
{
    auto mainSettings = ofxImGui::Settings();
    this->gui.begin();
    {

        mainSettings.windowPos = ofVec2f(ofGetWidth() - 500, 50);
        if (ofxImGui::BeginWindow("DEBUG -- ", mainSettings, true))
        {
            if (ofxImGui::BeginTree(this->cameraOps, mainSettings))
            {
                // ofxImGui::AddParameter(this->radius);
                // ofxImGui::AddParameter(this->distance);
                // ofxImGui::AddParameter(this->fullLenghtOrbit);
                ofxImGui::EndTree(mainSettings);
            }
            ImGui::Separator();
            if (ofxImGui::BeginTree(this->shaderOps, mainSettings))
            {
                ofxImGui::AddParameter(this->xFreq);
                ofxImGui::AddParameter(this->yFreq);
                ofxImGui::AddParameter(this->zFreq);

                ImGui::Separator();
                ofxImGui::AddParameter(this->xDepth);
                ofxImGui::AddParameter(this->yDepth);
                ofxImGui::AddParameter(this->zDepth);
                ImGui::Separator();
                ofxImGui::AddParameter(this->reflect);
                ofxImGui::AddParameter(this->roughtness);
                ofxImGui::AddParameter(this->metallic);

                ofxImGui::EndTree(mainSettings);
            }
            ImGui::Separator();
            if (ofxImGui::BeginTree(this->colors, mainSettings))
            {
                ImGui::ColorEdit4("Diffuse", (float *)&diff_val);

                ofxImGui::EndTree(mainSettings);
            }
            ofxImGui::EndWindow(mainSettings);
        }
    }
    this->gui.end();
    return mainSettings.mouseOverGui;
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

void ofApp::save()
{
    // SETTINGS SAVE
}