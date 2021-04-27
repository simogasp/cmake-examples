
#include"WorldClient.h"

// XWorldClient* g_pWorldClient = nullptr;
extern XWorldClient* g_pWorldClient;
bool CoreInit(void* L, const char* pszUserPath, const char* pszTransateLang, int nTranslateMode, int nStep)
{
    g_pWorldClient = new XWorldClient();
    return true;
}

bool Exit()
{
    if(g_pWorldClient)
        delete g_pWorldClient;
    return true;
}
