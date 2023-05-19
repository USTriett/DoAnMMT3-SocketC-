#include "ProcessController.h"

ProcessController::ProcessController()
{
    if (!EnumProcesses(processIDs, sizeof(processIDs), &bytesReturned)) // lay tat ca ca quy trinh id -> bytesReturned
    {
        std::cout << "\nFailed to enumerate processes.\n";
    }
}

ProcessController::~ProcessController()
{
}

DWORD ProcessController::getNumberOfProcessess()
{
    return this->bytesReturned / sizeof(DWORD);
}

std::vector<DWORD> ProcessController::getProcessIdOfProgram(const char *pname)
{
    std::vector<DWORD> vid;
    DWORD numProcesses = this->getNumberOfProcessess();
    
    for (DWORD i = 0; i < numProcesses; ++i)
    {
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE, FALSE, processIDs[i]);
        if (hProcess)
        {
            // std::cout << "\nProcess " << i << "\n";
            HMODULE hMods[1024];
            DWORD cbNeeded;
            char processName[MAX_PATH] = {0};

            // lay ten ung dung tu Process ID (PID)
            if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
            {
                if (GetModuleBaseNameA(hProcess, NULL, processName, sizeof(processName)))
                {
                    // std::cout << processName << std::endl;
                    if (!strcmp(processName, pname))
                    {
                        vid.push_back(processIDs[i]);
                    }
                }
            }

            CloseHandle(hProcess);
        }

        CloseHandle(hProcess);
    }
    
    return vid;
}

void ProcessController::closeProgram(const char *programName)
{
    std::vector<DWORD> vid = this->getProcessIdOfProgram(programName);
    for(auto i = vid.begin(); i != vid.end(); ++i)
    {
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE, FALSE, *i);
        if (hProcess)
        {
            // std::cout << "\nProcess " << i << "\n";
            HMODULE hMods[1024];
            DWORD cbNeeded;
            char processName[MAX_PATH] = {0};

            // lay ten ung dung tu Process ID (PID)
            if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
            {
                if (GetModuleBaseNameA(hProcess, NULL, processName, sizeof(processName)))
                {
                    // std::cout << processName << std::endl;
                    if (!strcmp(processName, programName))
                    {
                        std::cout << "\nProgram Found!\n";
                        try
                        {
                            if (!TerminateProcess(hProcess, 0))
                            {
                                std::cerr << "Failed to terminate process.\n";
                            }
                            else
                            {
                                std::cout << "Success!\n";
                            }
                        }
                        catch(...)//catch all exception
                        {
                            std::cerr<< "Something wrong!\n";
                            throw;
                        }
                    }
                }
            }
            else
            {
                std::cout << "\nFailed to enumerate process modules." << std::endl;
            }

            CloseHandle(hProcess);
        }

        CloseHandle(hProcess);
    }
    this->update();
}

void ProcessController::listAllProgram()
{
    DWORD numProcesses = this->getNumberOfProcessess();

    for (DWORD i = 0; i < numProcesses; ++i)
    {
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processIDs[i]);
        if (hProcess)
        {
            std::cout << "\nProcess " << i << "\n";
            HMODULE hMods[1024];
            DWORD cbNeeded;
            char processName[MAX_PATH] = {0};

            // lay ten ung dung tu Process ID (PID)
            if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
            {
                if (GetModuleBaseNameA(hProcess, NULL, processName, sizeof(processName)))
                {
                    std::cout << processName << std::endl;
                }
            }
            else
            {
                std::cout << "\nFailed to enumerate process modules." << std::endl;
            }

            CloseHandle(hProcess);
        }

        CloseHandle(hProcess);
    }
}

void ProcessController::listAllProcessOfProgram(const char *programName)
{
    std::vector<DWORD> vid = this->getProcessIdOfProgram(programName);
    for(auto i = vid.begin(); i != vid.end(); ++i)
    {
        std::cout <<"Process ID: " << *i << std::endl;
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, *i);
        if (hProcess)
        {
            // std::cout << "\nProcess " << i << "\n";
            HMODULE hMods[1024];
            DWORD cbNeeded;
            char processName[MAX_PATH] = {0};

            // lay ten ung dung tu Process ID (PID)
            if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
            {
                if (GetModuleBaseNameA(hProcess, NULL, processName, sizeof(processName)))
                {
                    // std::cout << processName << std::endl;
                    if (!strcmp(processName, programName))
                    {
                        std::cout << "\nProgram Found!\n";
                        try
                        {
                            if (!TerminateProcess(hProcess, 0))
                            {
                                std::cerr << "Failed to terminate process.\n";
                            }
                            else
                            {
                                std::cout << "Success!\n";
                            }
                        }
                        catch(...)//catch all exception
                        {
                            std::cerr<< "Something wrong!\n";
                            throw;
                        }
                    }
                }
            }
            else
            {
                std::cout << "\nFailed to enumerate process modules." << std::endl;
            }

            CloseHandle(hProcess);
        }

        CloseHandle(hProcess);
    }
}

bool ProcessController::startApp(std::wstring path)
{
     try
    {
        // std::string myString(appPath.begin(), appPath.end());
        STARTUPINFOA si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));
        
        std::string myString1(path.begin(), path.end());
        std::string myResult = "explorer " + myString1;
        char* myLPSTR = new char[myResult.length() + 1];
        strcpy(myLPSTR, myResult.c_str());
        // Start the child process.
        if (!CreateProcessA(NULL,    // No module name (use command line)
                            myLPSTR, // Command line
                            NULL,    // Process handle not inheritable
                            NULL,    // Thread handle not inheritable
                            FALSE,   // Set handle inheritance to FALSE
                            0,       // No creation flags
                            NULL,    // Use parent's environment block
                            NULL,    // Use parent's starting directory
                            &si,     // Pointer to STARTUPINFO structure
                            &pi)     // Pointer to PROCESS_INFORMATION structure
        )
        {
            printf("CreateProcess failed (%d).\n", GetLastError());
            return false;
        }

        // Wait until child process exits.
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Close process and thread handles.
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return true;
    }
    catch (...)
    {
        // std:: cout << e;
    }
    return false;
}

void ProcessController::update()
{
    std::fill(processIDs, processIDs + MAX_PROCESSES, 0);
    if (!EnumProcesses(processIDs, sizeof(processIDs), &bytesReturned)) // lay tat ca ca quy trinh id -> bytesReturned
    {
        std::cout << "\nFailed to enumerate processes.\n";
    }
}
