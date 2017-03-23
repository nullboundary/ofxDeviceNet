#pragma once

#include <windows.h>
#include "I7565DNM_API.h"
#include "ofMain.h"

#define DNM_CHECK_FATAL_ERROR if(err != I7565DNM_NoError) { ofLogFatalError() << "Error code #" << int(err);}
#define DNM_CHECK_ERROR if(err != I7565DNM_NoError) { ofLogError() << "Error code #" << int(err);}

class ofxDeviceNet
{
public:
	ofxDeviceNet();
	~ofxDeviceNet();

	//List port numbers of connected USB Device Net modules
	void listModules();

	//Returns a list of module port numbers
	vector <unsigned char> getModuleList();

	//activate the first module in the list
	bool setup();

	//activate a module on a specific com port. 
	bool setup(int portNumber);

	//close the module connection
	void close();

	//scans for connected slave devices on Device Net
	vector <unsigned char> searchAllDevices();

	//start communicating with the specific slave device
	void startDevice(unsigned char deviceMacID);

	//stop communicating with the specific slave device
	void stopDevice(unsigned char deviceMacID);

	//read bytes from slave device
	bool readBytes(unsigned char deviceMacID, unsigned char * buffer, unsigned short *length);

	//write bytes to slave device
	bool writeBytes(unsigned char deviceMacID,unsigned char * buffer, unsigned short length);

private:
	BYTE numOfModule = 0;
	BYTE portList[100];
	BYTE portNum = 0xFF;
	WORD TotalDevices, DeviceInputLen[100], DeviceOutputLen[100];
	BYTE DesMACID[100], Type[100];

};

