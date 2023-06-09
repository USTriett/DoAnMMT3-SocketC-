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

std::wstring ProcessController::listAllProgram()
{
    DWORD numProcesses = this->getNumberOfProcessess();
    std::wstringstream ss;
    // ss << L"Number of running processes: " << numProcesses << std::endl;
    for (const auto &i : processes)
    {
        ss << i.th32ProcessID << std::endl;
        ss << i.szExeFile << std::endl;
        ss << i.cntThreads << std::endl;
        ss << i.cntUsage << std::endl;
    }
    return ss.str();
}

std::wstring ProcessController::listAllProcessOfProgram(std::wstring programName)
{
    std::vector<DWORD> vid = this->getProcessIdOfProgram(programName);
    int count = 0;
    std::wstringstream ss;

    for (const auto &i : vid)
    {
        // std::cout << processes.size() << std::endl;

        // DWORD temp = i;
        // std::wcout << i << std::endl;
        for (const auto &j : processes)
        {
            if (j.th32ProcessID == i)
            {
                ss << j.th32ProcessID << std::endl;
                ss << j.szExeFile << std::endl;
                ss << j.cntThreads << std::endl;
                ss << j.cntUsage << std::endl;
                count ++;
                break;
            }
        }
        
        // std::wcout << i << std::endl;
    }

    if (!count)
    {
        std::cout << "The program is not running now....\n";
    }
    return ss.str();
}

bool ProcessController::startApp(std::wstring exePath)
{
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Start the child process.
    if (!CreateProcessW(exePath.c_str(), // No module name (use command line)
                        nullptr,         // Command line
                        nullptr,         // Process handle not inheritable
                        nullptr,         // Thread handle not inheritable
                        FALSE,           // Set handle inheritance to FALSE
                        0,               // No creation flags
                        nullptr,         // Use parent's environment block
                        nullptr,         // Use parent's starting directory
                        &si,             // Pointer to STARTUPINFO structure
                        &pi))            // Pointer to PROCESS_INFORMATION structure
    {
        std::cout << "CreateProcess failed" << std::endl;
    }

    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles.
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return false;
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
