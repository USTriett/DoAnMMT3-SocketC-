#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN

#endif

#ifndef APPLISTER_H
#define APPLISTER_H
typedef unsigned char cs_byte;
#include <vector>
#include <Windows.h>
#include "RegistryKey.h"
#include<iostream>
#include"MyHelper.h"
using namespace std;

class Software
{
public:
	wstring DisplayName;
	wstring InstallLocation;
	wstring Version;
	Arch Architecture; // 32 or 64
	wstring Icon;
	wstring appPath;
	Software(wstring, wstring, wstring, wstring, Arch, wstring appPath);
	Software(wstring, wstring, wstring, wstring, Arch);
	friend std::wostream& operator<<(std::wostream& os, const Software& sw) {
        os << L"Display Name: " << MyHelper::utf8_to_unicode_escape_sequences(sw.DisplayName) << std::endl;
        os << L"Install Location: " << MyHelper::utf8_to_unicode_escape_sequences(sw.InstallLocation) << std::endl;
        os << L"Version: " << MyHelper::utf8_to_unicode_escape_sequences(sw.Version) << std::endl;
        // os << L"Architecture: " << (sw.Architecture == Arch::X86 ? L"32-bit" : L"64-bit") << std::endl;
        os << L"Icon: " << MyHelper::utf8_to_unicode_escape_sequences(sw.Icon) << std::endl;
        return os;
    }
	
};


class AppLister
{
public:
	AppLister(void);
	~AppLister(void);
	static vector<Software>* GetAppLister(bool IncludeUpdates);
private:
	static vector<Software>* GetAppListerImp(bool IncludeUpdates);
	static vector<Software>* GetUninstallKeyPrograms(RegistryKey* UninstallKey, RegistryKey* ClassesKey, vector<Software>*, bool IncludeUpdates);
	static vector<Software>* GetUserInstallerKeyPrograms(RegistryKey* uInstallerKey, vector<Software>* ExistingProgramList);
};

#endif