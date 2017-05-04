#include "ofxDeviceNet.h"

ofxDeviceNet::ofxDeviceNet()
{

}

ofxDeviceNet::~ofxDeviceNet()
{
	close(); //close module connection
}

void ofxDeviceNet::listModules() {
	
	DWORD err = I7565DNM_NoError;

	err = I7565DNM_TotalI7565DNMModule(&numOfModule, portList);
	DNM_CHECK_FATAL_ERROR;

	std::cout << "Number of Modules:" << int(numOfModule) << std::endl;
	for (BYTE i = 0; i < numOfModule; i++) {
		std::cout << "Module Port Number [" << int(portList[i]) << "]" << std::endl;
	}

}

std::vector<unsigned char> ofxDeviceNet::getModuleList()
{
	DWORD err = I7565DNM_NoError;

	err = I7565DNM_TotalI7565DNMModule(&numOfModule, portList);
	DNM_CHECK_FATAL_ERROR;
	if (numOfModule == 0) {
		return std::vector<unsigned char>();
	}
	return std::vector<unsigned char> (std::begin(portList), portList+numOfModule);
	
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
	DWORD err = DNMXS_NoError;

	portNum = portNumber;
	err = I7565DNM_ActiveModule(portNumber);

	if (err != DNMXS_NoError) {
		std::cout << "Error Activating Module, Error code#" << err << std::endl;
		return false;
	}
	return true;
	
}

void ofxDeviceNet::close()
{
	DWORD err = I7565DNM_NoError;
	err = I7565DNM_CloseModule(portNum);
	DNM_CHECK_ERROR;
}

std::vector <unsigned char> ofxDeviceNet::searchAllDevices()
{
	DWORD err = I7565DNM_NoError;
	int sleepDuration = 300;

	if (portNum == 0xFF) {
		std::cout << "Setup module before searching for slave devices" << std::endl;
		return std::vector<unsigned char>();
	}

	std::cout << "Searching for Devices";
	err = I7565DNM_SearchAllDevices(portNum);
	DNM_CHECK_ERROR;
	
	while (I7565DNM_IsSearchOK(portNum)) {
		std::cout << ".";
		std::this_thread::sleep_for(std::chrono::milliseconds(sleepDuration)); //sleep
	}
	std::cout << std::endl;

	err = I7565DNM_GetSearchedDevices(portNum, &TotalDevices, DesMACID, Type, DeviceInputLen, DeviceOutputLen);
	DNM_CHECK_ERROR;
	if (TotalDevices > 0) {
		for (BYTE i = 0; i < TotalDevices; i++) {
			std::cout << "Slave device mac ID: " << int(*DesMACID) << std::endl;
		}
		return std::vector<unsigned char>(std::begin(DesMACID), DesMACID+TotalDevices);
	}
	
	std::cout << "No slave devices found" << std::endl;
	return std::vector<unsigned char>();
	
		
}

void ofxDeviceNet::getBaudRate()
{
}

void ofxDeviceNet::addConnection(unsigned char deviceMacID,int inByteLen, int outByteLen, int pollRateMS)
{
	DWORD err = I7565DNM_NoError;
	if (portNum == 0xFF) {
		std::cout << "Setup module before connecting to slave device" << std::endl;
		return;
	}

	err = I7565DNM_AddIOConnection(portNum, deviceMacID, ConType_Poll, inByteLen, outByteLen, pollRateMS);
	if (err) {
		printf("Add IO Connection Error Code:%d\n", err);
	}
		

}

void ofxDeviceNet::removeConnection(unsigned char deviceMacID)
{
	DWORD err = I7565DNM_NoError;
	if (portNum == 0xFF) {
		std::cout << "Setup module before disconnecting from slave device" << std::endl;
		return;
	}

	err = I7565DNM_RemoveIOConnection(portNum, deviceMacID, ConType_Poll);
	if (err) {
		printf("Error Code:%d\n", err);
	}
}

void ofxDeviceNet::startDevice(unsigned char deviceMacID)
{
	DWORD err = I7565DNM_NoError;
	if (portNum == 0xFF) {
		std::cout << "Setup module before starting slave device" << std::endl;
		return;
	}

	//std::cout << portNum << std::endl;
	err = I7565DNM_StartDevice(portNum, deviceMacID);
	DNM_CHECK_ERROR;
}

void ofxDeviceNet::stopDevice(unsigned char deviceMacID)
{
	DWORD err = I7565DNM_NoError;
	if (portNum == 0xFF) {
		std::cout << "Setup module before stopping slave device" << std::endl;
		return;
	}

	err= I7565DNM_StopDevice(portNum, deviceMacID);
	DNM_CHECK_ERROR;
}

bool ofxDeviceNet::readBytes(unsigned char deviceMacID, unsigned char * buffer, unsigned short *length)
{
	DWORD err = I7565DNM_NoError;
	
	if (portNum == 0xFF) {
		std::cout << "setup module before reading bytes" << std::endl;
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
	DWORD err = I7565DNM_NoError;


	if (portNum == 0xFF) {
		std::cout << "setup module before writing bytes" << std::endl;
		return false;
	}

	err = I7565DNM_WriteOutputData(portNum, deviceMacID, ConType_Poll, length, buffer);
	if (err == I7565DNM_NoError) {
		return true;
	}
	else {
		std::cout << "Error Writing Output Data, Error code#" << int(err) << std::endl;
		return false;
	}
}
