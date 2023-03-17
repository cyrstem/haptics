#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetWindowTitle("--HAPTICS--");
    ofSetFrameRate(60.0f);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofDisableArbTex();
    ofSetBackgroundColor(11);

    // cam.setNearClip(10);
    // cam.setPosition(0, 45, 100);

    // cubeMap.load("loc00184-22-8k.exr", 512, true);

    // Thing---------------------------------
    // sphere.set(40, 24);
    // cam.lookAt(mesh.getPosition());

    mesh.setMode(OF_PRIMITIVE_LINES);
    ico.set(1, 6);
    mesh = ico.getMesh();

    this->gui.setup();
    // gui.setTheme(new MyTheme());
    this->guiVisible = true;

    // shader
    shader.load("shader");

    ofFboSettings p;
    p.width = 256;
    p.height = 256;
    p.internalformat = GL_RGBA;
    p.maxFilter = GL_LINEAR;
    p.minFilter = GL_LINEAR;
    p.numSamples = 3;
    p.useDepth = true;

    p.wrapModeHorizontal = GL_CLAMP_TO_EDGE;
    p.wrapModeVertical = GL_CLAMP_TO_EDGE;

    fbo.allocate(p);
    fbo.begin();
    ofClear(255, 255, 255, 0);
    fbo.end();

    // save
    param.add(zoom);
    param.add(speed);
    param.add(perlin);
    param.add(decay);
    param.add(waves);
    param.add(eqcolor);
    param.add(red);
    param.add(green);
    param.add(blue);
    XML_load_app(param, XML_path);
}

//--------------------------------------------------------------
void ofApp::update()
{
    cam.setPosition(0, 0, zoom);
    fbo.begin();
    ofClear(255, 255, 255, 0);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw()
{

    ofEnableDepthTest();
    cam.begin();
    shader.begin();
    shader.setUniform1f("perlins", 1.0);
    shader.setUniform1f("time", ofGetElapsedTimef());
    shader.setUniform1f("pointscale", 10.0);
    shader.setUniform1f("decay", decay);
    shader.setUniform1f("complex", 0.0);
    shader.setUniform1f("waves", waves);
    shader.setUniform1f("eqcolor", eqcolor);
    shader.setUniform1i("fragment", false);
    shader.setUniform1f("dnoise", 0.0);
    shader.setUniform1f("qnoise", 4.0);
    shader.setUniform1f("r_color", red);
    shader.setUniform1f("g_color", green);
    shader.setUniform1f("b_color", blue);
    shader.setUniform1i("speed", speed);
    // sphere.draw();
    ofScale(2, 2, 2);
    mesh.draw();

    shader.end();
    cam.end();
    ofDisableDepthTest();

    this->mouseOverGui = false;
    if (this->guiVisible)
    {
        this->mouseOverGui = this->imGui();
    }
    // not neededd on OFCAM
    //  if (this->mouseOverGui)
    //  {
    //      this->cam.disableMouseInput();
    //  }
    //  else
    //  {
    //      this->cam.enableMouseInput();
    //  }
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
        XML_save_app(param, XML_path);
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
                ofxImGui::AddParameter(this->zoom);
                ofxImGui::EndTree(mainSettings);
            }
            ImGui::Separator();
            if (ofxImGui::BeginTree(this->shaderOps, mainSettings))
            {
                ofxImGui::AddParameter(this->speed);
                ofxImGui::AddParameter(this->decay);
                ofxImGui::AddParameter(this->waves);
                ImGui::Separator();

                ofxImGui::EndTree(mainSettings);
            }
            ImGui::Separator();
            if (ofxImGui::BeginTree(this->colors, mainSettings))
            {
                ofxImGui::AddParameter(this->eqcolor);
                ofxImGui::AddParameter(this->red);
                ofxImGui::AddParameter(this->green);
                ofxImGui::AddParameter(this->blue);

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
