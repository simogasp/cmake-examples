class XWorldClient
{
public:
    XWorldClient(void);
    ~XWorldClient(void);
public:
    static void ErrorCallbackFunc(void* pvUsrData, int nSysErr, int nUsrErr);
    void        ProcessSocketError(void* pvUsrData, int nSysErr, int nUsrErr);
};

//extern XWorldClient* g_pWorldClient;