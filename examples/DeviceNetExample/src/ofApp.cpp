#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	
	//app setup
	int frameRate = 30;
	ofBackground(54, 54, 54, 255);
	ofSetFrameRate(frameRate);
	
	//font setup
	ofTrueTypeFont::setGlobalDpi(72);
	verdana22.load("verdana.ttf", 22, true, true);
	verdana22.setLineHeight(34.0f);
	verdana22.setLetterSpacing(1.035);

	//OSC: open an outgoing connection to HOST:PORT
	sender.setup(HOST, PORT);

	//device net
	dNet.listModules();
	if (dNet.setup()) {
		ofLog() << "Connected to DeviceNet Module" << endl;
	}
	//slaveDeviceList = dNet.searchAllDevices();
	//if (!slaveDeviceList.empty()) {
		//slaveDeviceID = slaveDeviceList[0];
		slaveDeviceID = 25;
		dNet.addConnection(slaveDeviceID, 50, 50, int(1000 / frameRate)); //50 bytes input, 50 bytes output, 33msec polling rate
		dNet.startDevice(slaveDeviceID);
	//}
	
}

//--------------------------------------------------------------
void ofApp::update(){
	unsigned char readBuffer[50];
	unsigned short dataLength = 50;
	
		dNet.readBytes(slaveDeviceID, readBuffer, &dataLength);
	
		int numBytes = 4; //bytes per value
		int numEmptyBytes = 23; //22 empty bytes + 1

		for (int i = dataLength- numEmptyBytes; i >= 0; i-=numBytes) {
			//00 DD 0E = 0x0EDD = 3805 = 38.05mm
			//80 33 A6 = 0xA633 = -42547 = -425.47mm
			//00 6F 52 = 0x526F = 21103 = 211.03mm
			float coordValue = makeValue(readBuffer,i);
			robotCoords.push_back(coordValue);
			
			//printf("coordValue: %f mm \n", coordValue);
		}

		if (robotCoords.size() >= 6) {
			//printf("coordValue[1] : %f \n", robotCoords[1]);
			ofxOscMessage m;
			m.setAddress("/kuka/transform");
			if (robotCoords.size() > 6) {
				m.addFloatArg(robotCoords[6]); //X
				m.addFloatArg(robotCoords[5]); //Y
				m.addFloatArg(robotCoords[4]); //Z
				m.addFloatArg(robotCoords[3]); //A
				m.addFloatArg(robotCoords[1]); //B
				m.addFloatArg(robotCoords[0]); //C
			}
			sender.sendMessage(m, false);
		}

}
//--------------------------------------------------------------
float ofApp::makeValue(unsigned char *buf, int coordIndex) {

	//printf("0x%X,0x%X,0x%X,0x%X \n", buf[coordIndex], buf[coordIndex -1], buf[coordIndex -2],buf[coordIndex -3]);

	int msb = int(buf[coordIndex]);
	int shift = msb << 8;
	shift = shift + int(buf[coordIndex - 1]);
	shift = shift << 8;
	int value = shift + int(buf[coordIndex - 2]);
	int sign = int(buf[coordIndex - 3]);
	if (sign == 0x80) {  //0x0 is positive 0x80 negative
		value = value * -1;
	}
	
	return float(value) / 100.0f;
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(225);

	string coordStr;

	string deviceStr = "Kuka Robot Device ID " + to_string(slaveDeviceID);
	verdana22.drawString(deviceStr, 30, 50);

	if (robotCoords.size() > 6) {
		//sprintf(coordStr, "X: %f mm", robotCoords[4]);
		coordStr = "X: " + to_string(robotCoords[6]) + " mm";
		verdana22.drawString(coordStr, 50, 100);

		//sprintf(coordStr, "Y: %f mm", robotCoords[4]);
		coordStr = "Y: " + to_string(robotCoords[5]) + " mm";
		verdana22.drawString(coordStr, 50, 150);

		//sprintf(coordStr, "Z: %f mm", robotCoords[3]);
		coordStr = "Z: " + to_string(robotCoords[4]) + " mm";
		verdana22.drawString(coordStr, 50, 200);

		//sprintf(coordStr, "A: %f deg", robotCoords[2]);
		coordStr = "A: " + to_string(robotCoords[3]) + " deg";
		verdana22.drawString(coordStr, 50, 250);

		//sprintf(coordStr, "B: %f deg", robotCoords[1]);
		coordStr = "B: " + to_string(robotCoords[1]) + " deg";
		verdana22.drawString(coordStr, 50, 300);

		//sprintf(coordStr, "C: %f deg", robotCoords[0]);
		coordStr = "C: " + to_string(robotCoords[0]) + " deg";
		verdana22.drawString(coordStr, 50, 350);
	}
	robotCoords.clear();
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
