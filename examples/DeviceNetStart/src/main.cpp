#include "ofMain.h"
#include "ofApp.h"
#include "ofxDeviceNet.h"

//========================================================================
//	isChange checks if the read byte has changed its bit values
//========================================================================
bool isChange(ofxDeviceNet* dNet, const int slaveID, const unsigned char checkByte) {

	unsigned char readBuffer[50]; //50 bytes because
	unsigned short dataLength = 50;

	dNet->readBytes(slaveID, readBuffer, &dataLength);

	auto nextByte = readBuffer[0];
	cout << int(nextByte) << endl;
	if (nextByte == checkByte) {
		cout << "ready" << endl;
		return true;
	}
	
	else{
		cout << "not ready" << endl;
		return false;
	}
	
}

//========================================================================
int main( ){

	int robotID = 25;
	ofxDeviceNet dNet;
	
	//device net
	dNet.listModules();
	if (dNet.setup()) {
		cout << "Connected to DeviceNet Module" << endl;
	}

	//vector<unsigned char> slaveDeviceList;
	//slaveDeviceList = dNet.searchAllDevices();
	//if (!slaveDeviceList.empty()) {
	//slaveDeviceID = slaveDeviceList[0];
	
	dNet.startDevice(robotID);

	isChange(&dNet, robotID, 0x00);
	bool running = true;


	while (running) {
		char input;
		cin >> input;
		if (input == 'q') {
			running = false;

		}
		else if (input == 'r') {
			if (isChange(&dNet, robotID, 0x01) == true) {
				running = false;
			}
		}
		else if (input == 'w') {
			unsigned char startCommand = 0x01; //0x01
			dNet.writeBytes(robotID, &startCommand, 1); //Send Begin Play
		}
		else if (input == 'e') {
			unsigned char startCommand = 0x00; //0x01
			dNet.writeBytes(robotID, &startCommand, 1); //Send Begin Play
		}
		else {

		}
		
	}

	int readIndex = 0;
	running = true;
	unsigned char startCommand = 0x01; //0x01
	dNet.writeBytes(robotID, &startCommand, 1); //Send Begin Play
	auto startTime = chrono::high_resolution_clock::now();
	auto endTime = chrono::high_resolution_clock::now();
	while (running) {
		cout << "[" << readIndex++ << "] ";
		if (isChange(&dNet, robotID, 0x01) == true) {
			cout << "change" << endl;
			running = false;
			endTime = chrono::high_resolution_clock::now();
			unsigned char startCommand = 0x00; //0x01
			dNet.writeBytes(robotID, &startCommand, 1); //Send Begin Play
		}
		else {
			cout << "no change" << endl;
		}
		this_thread::sleep_for(chrono::milliseconds(50));

		//example code for timing
		{
			
			auto duration = endTime - startTime;
			cout << "duration is " << chrono::duration_cast<chrono::microseconds>(duration).count() << "us" << endl;
		}	
	}
	running = true;
	while (running) {
		char input;
		cin >> input;
		if (input == 'q') {
			running = false;

		}
	}

}

