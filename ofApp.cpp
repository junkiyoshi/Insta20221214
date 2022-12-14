#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableDepthTest();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	auto ico_sphere = ofIcoSpherePrimitive(250, 5);
	this->base_mesh = ico_sphere.getMesh();

}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->draw_mesh = this->base_mesh;
	auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
	for (auto& v : this->draw_mesh.getVertices()) {

		for (int i = 0; i < 3; i++) {

			auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.0035, noise_seed.x + ofGetFrameNum() * 0.01)), 0, 1, -30, 30) * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
			auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.0035, noise_seed.y + ofGetFrameNum() * 0.01)), 0, 1, -30, 30) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
			auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.0035, noise_seed.z + ofGetFrameNum() * 0.01)), 0, 1, -30, 30) * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));

			v = glm::vec4(v, 0) * rotation_z * rotation_y * rotation_x;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.9999999999999999);

	ofSetColor(255, 64);
	this->draw_mesh.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}