#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#define _WIN32_WINNT 0x0600
#define MAX_CONNECTIONS 1
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include<iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")

int main() {
    int iResult;
    WSADATA wsaData;
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }
    else
    {
      printf("Winsock DLL found!\n");
      printf("status: %s\n", wsaData.szSystemStatus);
    }

    SOCKET clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(clientSocket == INVALID_SOCKET)
    {
      printf("Cannot create a socket!\n");
      WSACleanup();
      return 1;
    }
    else
    {
      printf("socket() is OK!\n");
    }

   
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_port = htons(8001); // little endian -> big endian
    PCWSTR serverPszAddrString = L"127.0.0.1";
    int result = InetPtonW(AF_INET, serverPszAddrString, &service.sin_addr.s_addr);
    if(connect(clientSocket, (SOCKADDR*) &service, sizeof(service)) == SOCKET_ERROR)
    {
        printf("connection failed, Error: %s\n", WSAGetLastError());
        closesocket(clientSocket);
        WSACleanup();
    }
    else
    {
        printf("Connect success!\nCan send message here:......\n");
        char* message = new char[1001];
        // while(true){
            printf("Input your message: ");
            cin.getline(message, 1001);
            int BytesCount = send(clientSocket, message, 1001, 0);
            if(BytesCount == SOCKET_ERROR)
            {
                printf("Something wrong!\nError: %s", WSAGetLastError());
            }
            else{
                printf("Send success, send %ld bytes to server\n", BytesCount);
            }
        // }
        delete message;

    }
    

    closesocket(clientSocket);
    WSACleanup();
    
  return 0;
}