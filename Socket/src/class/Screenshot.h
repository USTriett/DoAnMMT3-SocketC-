#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#define _WIN32_WINNT 0x0600
#ifndef SCREENSHOT_H
#define SCREENSHOT_H
#include<iostream>
// #include"Screenshot.h"
#include"Socket.h"
#include <fstream>
#include<string>
#include<sstream>
#include<vector>

bool SaveScreenShotToFile(SocketClient s, const char* filename);

std::vector<unsigned char> stringToBytes(std::string str) ;
void SaveScreenShotToFile(const char* filename);

void ScreenShotAndSendToClient(Socket* s, const char* filename) ;

std::string intToString(int num);
#endif