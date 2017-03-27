#include "ofxDeviceNet.h"

ofxDeviceNet::ofxDeviceNet()
{

}

ofxDeviceNet::~ofxDeviceNet()
{
	close(); //close module connection
}

void ofxDeviceNet::listModules() {
	
	DWORD err;

	err = I7565DNM_TotalI7565DNMModule(&numOfModule, portList);
	DNM_CHECK_FATAL_ERROR;

	ofLog() << "Number of Modules:" << int(numOfModule);
	for (BYTE i = 0; i < numOfModule; i++) {
		ofLog() << "Module Port Number [" << int(portList[i]) << "]" << endl;
	}

}

vector<unsigned char> ofxDeviceNet::getModuleList()
{
	DWORD err;

	err = I7565DNM_TotalI7565DNMModule(&numOfModule, portList);
	DNM_CHECK_FATAL_ERROR;
	if (numOfModule == 0) {
		return vector<unsigned char>();
	}
	return vector<unsigned char> (begin(portList), end(portList));
	
}

bool ofxDeviceNet::setup()
{
	
	auto portVector = getModuleList();
	if (!portVector.empty()) {
		return setup(portVector[0]);
	} 
	return false; 
	
}

bool ofxDeviceNet::setup(int portNumber)
{
	DWORD err;

	portNum = portNumber;
	err = I7565DNM_ActiveModule(portNumber);

	if (err != DNMXS_NoError) {
		ofLogError() << "Error Activating Module, Error code#" << err << endl;
		return false;
	}
	return true;
	
}

void ofxDeviceNet::close()
{
	DWORD err;
	err = I7565DNM_CloseModule(portNum);
	DNM_CHECK_ERROR;
}

vector <unsigned char> ofxDeviceNet::searchAllDevices()
{
	DWORD err;

	if (portNum == 0xFF) {
		ofLogError() << "Setup module before searching for slave devices" << endl;
		return vector<unsigned char>();
	}

	cout << "Searching for Devices";
	err = I7565DNM_SearchAllDevices(portNum);
	DNM_CHECK_ERROR;
	
	while (I7565DNM_IsSearchOK(portNum)) {
		cout << ".";
		ofSleepMillis(300);
	}
	cout << endl;

	err = I7565DNM_GetSearchedDevices(portNum, &TotalDevices, DesMACID, Type, DeviceInputLen, DeviceOutputLen);
	DNM_CHECK_ERROR;
	if (TotalDevices > 0) {
		for (BYTE i = 0; i < TotalDevices; i++) {
			ofLog() << "Slave device mac ID: " << int(*DesMACID);
		}
		return vector<unsigned char>(begin(portList), end(portList));
	}
	
	ofLogError() << "No slave devices found";
	return vector<unsigned char>();
	
		
}

void ofxDeviceNet::getBaudRate()
{
}

void ofxDeviceNet::addConnection(unsigned char deviceMacID,int inByteLen, int outByteLen, int pollRateMS)
{
	DWORD err;
	if (portNum == 0xFF) {
		ofLogError() << "Setup module before starting slave device" << endl;
		return;
	}

	err = I7565DNM_AddIOConnection(portNum, deviceMacID, ConType_Poll, inByteLen, outByteLen, pollRateMS);
	if (err) {
		printf("Add IO Connection Error Code:%d\n", err);
	}
		

}

void ofxDeviceNet::removeConnection(unsigned char deviceMacID)
{
	DWORD err;
	if (portNum == 0xFF) {
		ofLogError() << "Setup module before starting slave device" << endl;
		return;
	}

	err = I7565DNM_RemoveIOConnection(portNum, deviceMacID, ConType_Poll);
	if (err) {
		printf("Error Code:%d\n", err);
	}
}

void ofxDeviceNet::startDevice(unsigned char deviceMacID)
{
	DWORD err;
	if (portNum == 0xFF) {
		ofLogError() << "Setup module before starting slave device" << endl;
		return;
	}

	err = I7565DNM_StartDevice(portNum, deviceMacID);
	DNM_CHECK_ERROR;
}

void ofxDeviceNet::stopDevice(unsigned char deviceMacID)
{
	DWORD err;
	if (portNum == 0xFF) {
		ofLogError() << "Setup module before stopping slave device" << endl;
		return;
	}

	err= I7565DNM_StopDevice(portNum, deviceMacID);
	DNM_CHECK_ERROR;
}

bool ofxDeviceNet::readBytes(unsigned char deviceMacID, unsigned char * buffer, unsigned short *length)
{
	DWORD err;
	
	if (portNum == 0xFF) {
		ofLogError() << "setup module before reading bytes"; 
		return false;
	}

	err = I7565DNM_ReadInputData(portNum, deviceMacID, ConType_Poll, length, buffer);
	if (err == I7565DNM_NoError) {
		return true;
	}
	else {
		printf("Error Reading Input Data, Error Code:%d\n", err);
		return false;
	}
	
}

bool ofxDeviceNet::writeBytes(unsigned char deviceMacID, unsigned char * buffer, unsigned short length)
{
	DWORD err;


	if (portNum == 0xFF) {
		ofLogError() << "setup module before writing bytes" << endl;
		return -1;
	}

	err = I7565DNM_WriteOutputData(portNum, deviceMacID, ConType_Poll, length, buffer);
	if (err == I7565DNM_NoError) {
		return true;
	}
	else {
		ofLogError() << "Error Writing Output Data, Error code#" << int(err);
		return false;
	}
}
