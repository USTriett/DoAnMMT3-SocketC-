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
#include <cstdlib>
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

    SOCKET serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(serverSocket == INVALID_SOCKET)
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
    PCWSTR pszAddrString = L"127.0.0.1";
    int result = InetPtonW(AF_INET, pszAddrString, &service.sin_addr.s_addr);

    if(bind(serverSocket, (SOCKADDR *)&service, sizeof(service)) == SOCKET_ERROR)
    {
      printf("Error: %s\n", WSAGetLastError());
      closesocket(serverSocket);
      WSACleanup();
    }
    else{
      printf("bind() is OK!\n");
    }

    if(listen(serverSocket, MAX_CONNECTIONS) == SOCKET_ERROR)
    {
      printf("Error: %s\n", WSAGetLastError());
      closesocket(serverSocket);
      WSACleanup();
    }
    else{
      printf("listen() is OK!\n");
      printf("waiting for the connections...\n");
    }
    SOCKET* acceptedSockets = new SOCKET[MAX_CONNECTIONS];
      for(int i = 0 ; i < MAX_CONNECTIONS; i++)
      {
        acceptedSockets[i] = accept(serverSocket, NULL, NULL);
        if(acceptedSockets[i] == INVALID_SOCKET)
        {
          printf("socket %d connects failed!\nError: %s\n", i, WSAGetLastError());
          acceptedSockets[i] = NULL;
        }
        else
        {
          printf_s("socket %d connects successful", i);
          char receivedBuf[1001];
          int BytesCount = recv(acceptedSockets[i], receivedBuf, 1001, 0);
          if(BytesCount == SOCKET_ERROR)
          {
            printf("Something wrong!\nError: %s\n", WSAGetLastError());
          }
          else
          {
            printf("Message received: %s", receivedBuf);
          }
        }
      }
    
    closesocket(serverSocket);
    WSACleanup();
    
  return 0;
}