#include "WorldClient.h"

XWorldClient* g_pWorldClient = nullptr;

XWorldClient::XWorldClient(void)
{

}

XWorldClient::~XWorldClient(void)
{
    
}

void XWorldClient::ErrorCallbackFunc(void* pvUsrData, int nSysErr, int nUsrErr)
{
	g_pWorldClient->ProcessSocketError(pvUsrData, nSysErr, nUsrErr);
}

void XWorldClient::ProcessSocketError(void* pvUsrData, int nSysErr, int nUsrErr)
{
	//Log(eLogError, "[Server] Connection lost, SysErr = %d, UsrErr = %d", nSysErr, nUsrErr);
	//m_bInGame = false;
	//ClientScene::OnEvent(emNOTIFY_SERVER_CONNECT_LOST, nSysErr, nUsrErr);
}
