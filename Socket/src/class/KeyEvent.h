#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#define _WIN32_WINNT 0x0600
#define MAX_CONNECTIONS 1
#pragma warning(disable : 4996)

#ifndef KEY_EVENT_H
#define KEY_EVENT_H

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <cstdlib>
#include <conio.h>
#include <iostream>
#include <map>
#include "Socket.h"
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include<string>
#include<sstream>

bool IsCapitalized(short int shift, short int caps);

bool isHotKey(short t);
void findHotKey(short t, char *c);
void shiftWith(short t, char *c);
BOOL sendKeyEvent(Socket *s, int& flag);
string ReceivedKeyEvent(SocketClient s);
#endif