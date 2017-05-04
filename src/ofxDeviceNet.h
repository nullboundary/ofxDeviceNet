#pragma once

#include <windows.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "I7565DNM_API.h"


#define DNM_CHECK_FATAL_ERROR if(err != I7565DNM_NoError) { std::cout << "Error code #" << int(err) << std::endl;}
#define DNM_CHECK_ERROR if(err != I7565DNM_NoError) { std::cout << "Error code #" << int(err) << std::endl;}

class ofxDeviceNet
{
public:
	ofxDeviceNet();
	~ofxDeviceNet();

	//List port numbers of connected USB Device Net modules
	void listModules();

	//Returns a list of module port numbers
	std::vector <unsigned char> getModuleList();

	//activate the first module in the list
	bool setup();

	//activate a module on a specific com port. 
	bool setup(int portNumber);

	//close the module connection
	void close();

	//scans for connected slave devices on Device Net
	std::vector <unsigned char> searchAllDevices();

	void getBaudRate();

	//make an IO connection with the device
	void addConnection(unsigned char deviceMacID, int inByteLen, int outByteLen, int pollRateMS);

	//delete an IO connection with the device
	void removeConnection(unsigned char deviceMacID);

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
	BYTE portList[100] = {};
	BYTE portNum = 0xFF;
	WORD TotalDevices = 0; 
	WORD DeviceInputLen[100] = {};
	WORD DeviceOutputLen[100] = {};
	BYTE DesMACID[100] = {};
	BYTE Type[100] = {};

};

