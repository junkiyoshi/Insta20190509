#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofNoFill();
	ofSetLineWidth(5);
	ofSetCircleResolution(72);

}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	auto location_1 = glm::vec2(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	auto radius_1 = 280;

	auto location_2 = glm::vec2(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.008), 0, 1, 0, ofGetWidth()), ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.008), 0, 1, 0, ofGetHeight()));
	auto radius_2 = 120;

	auto theta = 0.0;
	auto a = 0.0;
	auto result = this->compute_angle(location_1, radius_1, location_2, radius_2, theta, a);

	if (result) {

		vector<glm::vec2> vertices;
		for (auto rad = theta + a; rad <= theta + 2 * PI - a; rad += PI / 180) {

			vertices.push_back(location_1 + glm::vec2(radius_1 * cos(rad), radius_1 * sin(rad)));
		}

		this->compute_angle(location_2, radius_2, location_1, radius_1, theta, a);
		for (auto rad = theta + a; rad >= theta - a; rad -= PI / 180) {

			vertices.push_back(location_2 + glm::vec2(radius_2 * cos(rad), radius_2 * sin(rad)));
		}
		
		ofFill();
		ofSetColor(239, 39, 39);
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape();

		ofNoFill();
		ofSetColor(39);
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape();

	}
	else {

		ofFill();
		ofSetColor(239, 39, 39);
		ofDrawCircle(location_1, radius_1);
		ofNoFill();
		ofSetColor(39);
		ofDrawCircle(location_1, radius_1);
		
		ofFill();
		ofSetColor(239);
		ofDrawCircle(location_2, radius_2);
		ofNoFill();
		ofSetColor(39);
		ofDrawCircle(location_2, radius_2);
	}
}

//--------------------------------------------------------------
bool ofApp::compute_angle(glm::vec2 location_1, float radius_1, glm::vec2 location_2, float radius_2, double& theta, double& a) {

	auto distance = glm::distance(location_1, location_2);
	if (distance > radius_1 + radius_2 || distance < radius_1 - radius_2) { return false; }

	theta = atan2(location_2.y - location_1.y, location_2.x - location_1.x);
	auto cos_a = (pow(distance, 2) + pow(radius_1, 2) - pow(radius_2, 2)) / (2 * distance * radius_1);
	a = acos(cos_a);
	return true;
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}