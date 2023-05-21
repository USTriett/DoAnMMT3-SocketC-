#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN

#endif
#ifndef ProcessCONTROLLER_H
#define ProcessCONTROLLER_H

#include <Windows.h>
#include <iostream> 
#include <cstring>
#include<string>
#include<vector>
#include<algorithm>
#include <process.h>
#include <Psapi.h>
#include <tlhelp32.h>
#define MAX_PROCESSES 1024

class ProcessController
{

public:
    ProcessController();
    ProcessController(const ProcessController &a) = delete;
    virtual ~ProcessController();
    ProcessController &operator=(const ProcessController a) = delete;
    DWORD getNumberOfProcessess(); // co bug
    std::vector<DWORD> getProcessIdOfProgram(std::wstring pname); 
    void closeProgram(std::wstring programName);
    // bool openProgram(const char *programName);
    void listAllProgram();
    void listAllProcessOfProgram(std::wstring programName);
    bool startApp(std::wstring path);
private:
    // std::vector<std::pair<DWORD, std::wstring>> vprocesses;
    void update();
    static DWORD numberOfProcess;
    static HANDLE hSnapShot;
    std::vector<PROCESSENTRY32W> processes;
    
};

#endif