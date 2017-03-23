
#define EXP  extern "C" __declspec(dllexport)





//Module Functions
EXP DWORD CALLBACK I7565DNM_TotalI7565DNMModule(BYTE *TotalModules ,BYTE *PortList);
EXP DWORD CALLBACK I7565DNM_ActiveModule(BYTE cPort);
EXP DWORD CALLBACK I7565DNM_CloseModule(BYTE cPort);
EXP DWORD CALLBACK I7565DNM_GetDLLVersion(void);

//Firmware Functions
EXP DWORD CALLBACK I7565DNM_GetFirmwareVersion(BYTE cPort);
EXP DWORD CALLBACK I7565DNM_ResetFirmware(BYTE cPort);

//Master Operating Functions
EXP DWORD CALLBACK I7565DNM_GetMasterMACID(BYTE cPort);
EXP DWORD CALLBACK I7565DNM_SetMasterMACID(BYTE cPort,BYTE MasterMACID);
EXP DWORD CALLBACK I7565DNM_GetBaudRate(BYTE cPort);
EXP DWORD CALLBACK I7565DNM_SetBaudRate(BYTE cPort,BYTE BaudRate);
EXP DWORD CALLBACK I7565DNM_GetMasterStatus(BYTE cPort);
EXP DWORD CALLBACK I7565DNM_GetSlaveStatus(BYTE cPort,BYTE DesMACID);

EXP DWORD CALLBACK I7565DNM_StartDevice(BYTE cPort,BYTE DesMACID);
EXP DWORD CALLBACK I7565DNM_StopDevice(BYTE cPort,BYTE DesMACID);
EXP DWORD CALLBACK I7565DNM_StartAllDevice(BYTE cPort);
EXP DWORD CALLBACK I7565DNM_StopAllDevice(BYTE cPort);

EXP DWORD CALLBACK I7565DNM_AddDevice(BYTE cPort,BYTE DesMACID,WORD Explicit_EPR);
EXP DWORD CALLBACK I7565DNM_RemoveDevice(BYTE cPort,BYTE DesMACID);
EXP DWORD CALLBACK I7565DNM_AddIOConnection(BYTE cPort,BYTE DesMACID,BYTE ConType,WORD DeviceInputLen,WORD DeviceOutputLen,WORD EPR);
EXP DWORD CALLBACK I7565DNM_RemoveIOConnection(BYTE cPort,BYTE DesMACID,BYTE ConType);

EXP DWORD CALLBACK I7565DNM_GetAttribute(BYTE cPort,BYTE DesMACID,BYTE ClassID,BYTE InstanceID,BYTE AttributeID);
EXP DWORD CALLBACK I7565DNM_GetAttributeW(BYTE cPort,BYTE DesMACID,WORD ClassID,WORD InstanceID,BYTE AttributeID);

EXP DWORD CALLBACK I7565DNM_IsGetAttributeOK(BYTE cPort,BYTE DesMACID);
EXP DWORD CALLBACK I7565DNM_GetAttributeValue(BYTE cPort,BYTE DesMACID,WORD *DataLen,BYTE *DATA);

EXP DWORD CALLBACK I7565DNM_SetAttribute(BYTE cPort,BYTE DesMACID,BYTE ClassID,BYTE InstanceID,BYTE AttributeID,WORD DataLen,BYTE *DATA);
EXP DWORD CALLBACK I7565DNM_SetAttributeW(BYTE cPort,BYTE DesMACID,WORD ClassID,WORD InstanceID,BYTE AttributeID,WORD DataLen,BYTE *DATA);

EXP DWORD CALLBACK I7565DNM_IsSetAttributeOK(BYTE cPort,BYTE DesMACID);
EXP DWORD CALLBACK I7565DNM_ClearAllConfig(BYTE cPort);

EXP DWORD CALLBACK I7565DNM_SearchAllDevices(BYTE cPort);
EXP DWORD CALLBACK I7565DNM_SearchSpecificDevice(BYTE cPort,WORD ListCount,BYTE *DesMACIDList);
EXP DWORD CALLBACK I7565DNM_IsSearchOK(BYTE cPort);
EXP DWORD CALLBACK I7565DNM_GetSearchedDevices(BYTE cPort,WORD *TotalDevices,BYTE *DesMACID,BYTE *Type,WORD *DeviceInputLen,WORD *DeviceOutputLen);
EXP DWORD CALLBACK I7565DNM_GetDeviceInfoFromScanList(BYTE cPort,BYTE DesMACID,WORD *ListCount,BYTE *ConnectionTypeList,WORD *InputDataLenList,WORD *OutputDataLenList,WORD *EPRList);
EXP DWORD CALLBACK I7565DNM_GetScanList(BYTE cPort,WORD *TotalDevices,BYTE *DesMACIDList,BYTE *ConnectionTypeList,WORD *InputDataLenList,WORD *OutputDataLenList,WORD *EPR_List);
EXP DWORD CALLBACK I7565DNM_ImportEEPROM(BYTE cPort,WORD ListCount,BYTE *DesMACIDList,BYTE *ConnectionTypeList,WORD *InputDataLenList,WORD *OutputDataLenList,WORD *EPR_List);

EXP DWORD CALLBACK I7565DNM_SendExplicitMSG(BYTE cPort,BYTE DesMACID,BYTE ServiceID,BYTE ClassID,BYTE InstanceID,WORD DataLen,BYTE *DATA);
EXP DWORD CALLBACK I7565DNM_SendExplicitMSG_W(BYTE cPort,BYTE DesMACID,BYTE ServiceID,WORD ClassID,WORD InstanceID,WORD DataLen,BYTE *DATA);

EXP DWORD CALLBACK I7565DNM_IsExplicitMSGRespOK(BYTE cPort,BYTE DesMACID);
EXP DWORD CALLBACK I7565DNM_GetExplicitMSGRespValue(BYTE cPort,BYTE DesMACID,WORD *DataLen,BYTE *DATA);

// I/O Configuring Functions
EXP DWORD CALLBACK I7565DNM_ReadInputData(BYTE cPort,BYTE DesMACID,BYTE ConType,WORD *IOLen,BYTE *IODATA);
EXP DWORD CALLBACK I7565DNM_WriteOutputData(BYTE cPort,BYTE DesMACID,BYTE ConType,WORD IOLen,BYTE *IODATA);

EXP DWORD CALLBACK I7565DNM_ReadbackOutputData(BYTE cPort,BYTE DesMACID,BYTE ConType,WORD *IOLen,BYTE *IODATA);

EXP DWORD CALLBACK I7565DNM_PauseIOConnection(BYTE cPort,BYTE DesMACID);
EXP DWORD CALLBACK I7565DNM_ResumeIOConnection(BYTE cPort,BYTE DesMACID);


//ConnectionType
#define ConType_Explicit  0
#define ConType_Poll      1
#define ConType_BitStrobe 2
#define ConType_COS       3
#define ConType_Cyclic    4
#define ConType_MultiPoll 5



//DLL Error Code
#define I7565DNM_NoError               0
#define I7565DNM_PortNotActive         10008
#define I7565DNM_PortNoResp            10015
#define I7565DNM_PortInUse             10025
#define I7565DNM_ReStartPort           10027



//Firmware Error Code
#define DNMXS_NoError               0
#define DNMXS_UnKnowError           5000

//Master Status Error Code
#define DNMXS_BoardNotActive        1000
#define DNMXS_OnlineError           1001
#define DNMXS_CANBusError           1002
#define DNMXS_Booting               1003
#define DNMXS_ModuleNotFound        1004

//General Error Code
#define DNMXS_MACIDError            1050
#define DNMXS_BaudRateError         1051
#define DNMXS_ConnectionTypeError   1052
#define DNMXS_DuplicMasterMACID     1053 //DesMACID»PMaster MACID¬Û¦P 
#define DNMXS_EEPROMError           1054
#define DNMXS_NowScanning           1055
#define DNMXS_ScanListError         1056
#define DNMXS_DeviceExist           1057
#define DNMXS_DeviceNotExist        1058 
#define DNMXS_MapTableError         1059

//IOConnection Error
#define DNMXS_ExplicitNotAllocate   1100
#define DNMXS_PollNotAllocate       1101
#define DNMXS_BitStrobeNotAllocate  1102
#define DNMXS_COSNotAllocate        1103
#define DNMXS_CyclicNotAllocate     1104
#define DNMXS_PollAlreadyExist      1105
#define DNMXS_BitStrobeAlreadyExist 1106
#define DNMXS_COSAlreadyExist       1107
#define DNMXS_CyclicAlreadyExist    1108
#define DNMXS_CommunicationPause    1109

//Slave Error Code
#define DNMXS_SlaveNoResp           1150
#define DNMXS_WaitForSlaveResp      1151
#define DNMXS_SlaveRespError        1152
#define DNMXS_OutputDataLenError    1153
#define DNMXS_InputDataLenError     1154


