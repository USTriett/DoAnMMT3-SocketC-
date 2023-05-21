#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <string> 
#include <iostream>
#define MAX_KEY_LENGTH 1001
#include"ProcessController.h"

int main() {
    // Mở khóa Registry
    // HKEY hKey;
    // if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths"), 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
    //     std::cout << "Khong tim thay duong dan App Paths trong Registry." << std::endl;
    //     return 1;
    // }

    // TCHAR achKey[MAX_KEY_LENGTH];
    // DWORD cbName;

    // // Duyệt qua tất cả các khóa con trong danh sách ứng dụng
    // for (int i = 0;; i++) {
    //     cbName = MAX_KEY_LENGTH;
    //     if (RegEnumKeyEx(hKey, i, achKey, &cbName, NULL, NULL, NULL, NULL) != ERROR_SUCCESS) {  
    //         break;
    //     }

    //     // Lấy đường dẫn của file thực thi
    //     TCHAR achClass[MAX_PATH] = TEXT("");
    //     DWORD cchClassName = MAX_PATH;     

    //     if(RegGetValue(hKey, achKey, TEXT("(Default)"), RRF_RT_REG_SZ, NULL, achClass, &cchClassName) == ERROR_SUCCESS) {
    //         if (cchClassName > 0 && achClass[0] != '\0') {
    //             std::cout << achClass << std::endl;
    //         }
    //     }
    // }

    // Đóng khóa Registry
    // RegCloseKey(hKey);
    

    return 0;
}