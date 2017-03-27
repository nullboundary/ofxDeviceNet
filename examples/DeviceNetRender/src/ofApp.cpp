#include "stdafx.h"
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	this->perspectivePreview.makePerspectiveMatrix(60, 1.0, 0.1, 5);
	this->camera.setDistance(20.0f);
	this->camera.setNearClip(0.01f);
	this->camera.setFarClip(100.0f);

	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
	//all up in here we're gonna make the transform

	// check for waiting messages
	while (receiver.hasWaitingMessages()) {
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(m);

		// check for kuka transform message
		if (m.getAddress() == "/kuka/transform") {
		
			//all arguments are floats
			float x = m.getArgAsFloat(0);
			float y = m.getArgAsFloat(1);
			float z = m.getArgAsFloat(2);
			float a = m.getArgAsFloat(3);
			float b = m.getArgAsFloat(4);
			float c = m.getArgAsFloat(5);
			kukaTransform(x, y, z, a, b, c);
		}
	}
	//kukaTransform(620, 0, 995, 0, 90, 0);
	//kukaTransform(1034.6, 136.9, 893.4,-90, 74.06, -168.69);

	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(40, 10);

	ofEnableDepthTest();
	this->camera.begin();
	{
		ofDrawGrid(1.0f, 10, true);

		ofPushMatrix();
		{
			ofPushStyle();
			{
				ofSetColor(100);
				this->drawFrustum();
			}
			ofPopStyle();

			ofMultMatrix(transform);
			this->drawFrustum();
		}
		ofPopMatrix();
	}
	this->camera.end();
	ofDisableDepthTest();

}
//--------------------------------------------------------------
void ofApp::kukaTransform(float x, float y, float z, float a, float b, float c)
{


	ofVec3f point = ofVec3f(y, z, x);
	point = point / ofVec3f(100, 100, 100); //mm to dm?
	point = point * ofVec3f(1, -1, -1); //inverse Y axis
	
	transform.makeIdentityMatrix();
	
	transform.rotate(b, 1, 0, 0); //y
	transform.rotate(c, 0, 0, -1); //z
	transform.rotate(a, 0, -1, 0); //x
	
	
	transform.translate(point);

}
//--------------------------------------------------------------
void ofApp::drawFrustum() {
	ofPushMatrix();
	{
		ofDrawArrow(ofVec3f(), ofVec3f(0, 1, 0));
		
		ofMultMatrix(this->perspectivePreview.getInverse());
		ofPushStyle();
		{
			ofSetLineWidth(2.0f);
			ofNoFill();
			ofDrawBox(2.0f);
		}
		ofPopStyle();
	}
	ofPopMatrix();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
