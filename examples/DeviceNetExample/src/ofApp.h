#pragma once

#include "ofMain.h"
#include "ofxDeviceNet.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 12345

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		float makeValue(unsigned char *buf,int coordIndex);
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofxOscSender sender;
		ofxDeviceNet dNet;
		int slaveDeviceID;
		vector<unsigned char> slaveDeviceList;
		vector<float>robotCoords;

		ofTrueTypeFont	verdana22;
		
};
