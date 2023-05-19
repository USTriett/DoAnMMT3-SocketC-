#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <string>
#include "ProcessController.h"

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

// int _tmain( int argc, TCHAR *argv[] )
// {
//     STARTUPINFO si;
//     PROCESS_INFORMATION pi;

//     ZeroMemory( &si, sizeof(si) );
//     si.cb = sizeof(si);
//     ZeroMemory( &pi, sizeof(pi) );

//     if( argc != 2 )
//     {
//         printf("Usage: %s [cmdline]\n", argv[0]);
//         return 1;
//     }

//     // Start the child process.
//     if( !CreateProcess( NULL,   // No module name (use command line)
//         argv[1],        // Command line
//         NULL,           // Process handle not inheritable
//         NULL,           // Thread handle not inheritable
//         FALSE,          // Set handle inheritance to FALSE
//         0,              // No creation flags
//         NULL,           // Use parent's environment block
//         NULL,           // Use parent's starting directory
//         &si,            // Pointer to STARTUPINFO structure
//         &pi )           // Pointer to PROCESS_INFORMATION structure
//     )
//     {
//         printf( "CreateProcess failed (%d).\n", GetLastError() );
//         return 1;
//     }

//     // Wait until child process exits.
//     WaitForSingleObject( pi.hProcess, INFINITE );

//     // Close process and thread handles.
//     CloseHandle( pi.hProcess );
//     CloseHandle( pi.hThread );
//     return 0;
// }

int main()
{
    // std::wstring appName = L"C:\\Program Files\\MyApp\\MyApp.exe"; // Đường dẫn tới ứng dụng cần mở
    std::wstring keyPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\chrome.exe"; // Đường dẫn tới khóa registry của ứng dụng

    HKEY hKey;
    LONG lResult = RegOpenKeyExW(HKEY_LOCAL_MACHINE, keyPath.c_str(), 0, KEY_READ, &hKey);
    if (lResult != ERROR_SUCCESS)
    {
        // Xử lý lỗi khi không tìm thấy khóa trong registry
        return 1;
    }

    DWORD dataSize = MAX_PATH;
    WCHAR appPath[MAX_PATH];
    lResult = RegQueryValueExW(hKey, nullptr, nullptr, nullptr, (LPBYTE)appPath, &dataSize);
    if (lResult != ERROR_SUCCESS)
    {
        // Xử lý lỗi khi không tìm thấy giá trị của khóa trong registry
        return 1;
    }
    std::wcout << appPath << std::endl;
    system("pause");
    RegCloseKey(hKey);

    // Tạo tiến trình để chạy ứng dụng
    ProcessController pc;
    pc.listAllProgram();
    system("pause");
    try
    {
        // std::string myString(appPath.begin(), appPath.end());
        STARTUPINFOA si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));
        std::wstring myWString1(appPath);
        std::string myString1(myWString1.begin(), myWString1.end());
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
            return 1;
        }

        // Wait until child process exits.
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Close process and thread handles.
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    catch (...)
    {
        // std:: cout << e;
    }
    std::cout << "Success\n";
    pc.listAllProgram();

    return 0;
}

// #include<iostream>
// using namespace std;

// #include"AppLister.h"

// int main()
// {
//     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//     DWORD dwMode = 0;
//     GetConsoleMode(hConsole, &dwMode);
//     dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
//     SetConsoleMode(hConsole, dwMode);
//     AppLister apps;
//     vector<Software>* v = apps.GetAppLister(0);
//     wcout << "Total apps found: " << v->size() << endl;
//     for(int i = 0; i < v->size(); i++)
//     {
//         wcout << L"App " << i << endl;
//         wcout << v->at(i) << endl;
//     }
//     wcout << v->back() << endl;
//     // wcout << v->at(19) << endl;
//     return 0;
// }

// #include <Windows.h>
// #include <iostream>

// int main() {
//     HKEY hKey;
//     LPCWSTR subKey = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion";
//     DWORD options = 0;
//     REGSAM accessRights = KEY_READ;

//     LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, subKey, options, accessRights, &hKey);
//     if (result == ERROR_SUCCESS) {
//         std::wcout << L"Opened registry key: " << subKey << std::endl;
//         RegCloseKey(hKey); // Close the opened key when done
//     }
//     else {
//         std::cerr << "Failed to open registry key. Error code: " << result << std::endl;
//     }

//     return 0;
// }