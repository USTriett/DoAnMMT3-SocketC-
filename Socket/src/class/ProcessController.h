#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN

#endif
#ifndef ProcessCONTROLLER_H
#define ProcessCONTROLLER_H

#include <Windows.h>
#include <iostream>
#include <Psapi.h> // thư viện để lấy tên ứng dụng từ Process ID (PID)
#include <cstring>
#include<vector>
#include<algorithm>
#define MAX_PROCESSES 1024

class ProcessController
{

public:
    ProcessController();
    ProcessController(const ProcessController &a) = delete;
    virtual ~ProcessController();
    ProcessController &operator=(const ProcessController a) = delete;
    DWORD getNumberOfProcessess(); // co bug
    std::vector<DWORD> getProcessIdOfProgram(const char* pname); 
    void closeProgram(const char *programName);
    // bool openProgram(const char *programName);
    void listAllProgram();
    void listAllProcessOfProgram(const char *programName);
    bool startApp(std::wstring path);
private:
    DWORD processIDs[MAX_PROCESSES], bytesReturned;
    void update();
};

#endif