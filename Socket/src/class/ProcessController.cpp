#include "ProcessController.h"
#include "MyHelper.h"
#include <cwchar>
#include <cstring>
// init static value
HANDLE ProcessController::hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
DWORD ProcessController::numberOfProcess = 0;

ProcessController::ProcessController()
{
    PROCESSENTRY32W process;
    process.dwSize = sizeof(PROCESSENTRY32W);
    if (Process32FirstW(hSnapShot, &process))
    {
        do
        {
            ProcessController::numberOfProcess++;
            

            this->processes.push_back(process);
        } while (Process32NextW(hSnapShot, &process));
    }
}

ProcessController::~ProcessController()
{
}

DWORD ProcessController::getNumberOfProcessess()
{
    return ProcessController::numberOfProcess;
}

std::vector<DWORD> ProcessController::getProcessIdOfProgram(std::wstring pname)
{
    std::vector<DWORD> vid;
    for (const auto &i : processes)
    {
        int size = wcslen(i.szExeFile) + 1;
        std::wstring name(size, L' ');
        wcscpy_s(const_cast<wchar_t *>(name.data()), name.size() + 1, i.szExeFile);
        if (wcsicmp(name.c_str(), pname.c_str()) == 0)
        {
            std::wcout << "IDs: " << i.th32ProcessID << " ";

            vid.push_back(i.th32ProcessID);
        }
    }

    return vid;
}

void ProcessController::closeProgram(std::wstring programName)
{
    // std::wcout << programName << std::endl;
    std::vector<DWORD> vid = this->getProcessIdOfProgram(programName);
    std::vector<HANDLE> processHandles;

    for (auto id : vid)
    {
        // std::wcout << id << " " ;
        HANDLE handle = OpenProcess(PROCESS_TERMINATE, FALSE, id);
        processHandles.push_back(handle);
    }

    // Terminate processes
    for (auto handle : processHandles)
    {
        TerminateProcess(handle, 0);
    }

    // Close handles
    for (auto handle : processHandles)
    {
        CloseHandle(handle);
    }
    this->update();
}

void ProcessController::listAllProgram()
{
    DWORD numProcesses = this->getNumberOfProcessess();
    std::wcout << L"Number of running processes: " << numProcesses << std::endl;
    for (const auto &i : processes)
    {
        std::wcout << L"\nProcess ID: " << i.th32ProcessID << std::endl;
        std::wcout << "Main program: " << i.szExeFile << std::endl;
        std::wcout << "Current Threads: " << i.cntThreads << std::endl;
        std::wcout << "Page faults: " << i.cntUsage << std::endl;
    }
}

void ProcessController::listAllProcessOfProgram(std::wstring programName)
{
    std::vector<DWORD> vid = this->getProcessIdOfProgram(programName);
    int count = 0;
    for(const auto& i : vid)
    {
        // DWORD temp = i;
        auto it = std::find_if(processes.begin(), processes.end(), 
         [&i](const PROCESSENTRY32W &p) { return p.th32ModuleID == i; });
        if (it != processes.end()) {
            // Element found
            count++;
            std::wcout << L"\nProcess ID: " << it->th32ProcessID << std::endl;
            std::wcout << "Main program: " << it->szExeFile << std::endl;
            std::wcout << "Current Threads: " << it->cntThreads << std::endl;
            std::wcout << "Page faults: " << it->cntUsage << std::endl;

        }
        // std::wcout << i << std::endl;
    }
    if(!count)
    {
        std::cout << "The program is not running now....\n";
    }

}

void ProcessController::update()
{
    ProcessController::hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    ProcessController::numberOfProcess = 0;
    PROCESSENTRY32W process;
    process.dwSize = sizeof(PROCESSENTRY32W);
    if (Process32FirstW(hSnapShot, &process))
    {
        do
        {
            ProcessController::numberOfProcess++;

            this->processes.push_back(process);
        } while (Process32NextW(hSnapShot, &process));
    }
}
