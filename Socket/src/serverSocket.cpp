#include "./class/Socket.h"
#include <process.h>
#include <string>
#include <list>
#include <iostream>
#include "./class/ProcessController.h"
#include "./class/KeyEvent.h"
#include "./class/MyHelper.h"
#include <thread>
#include <future>
#include"./class/AppLister.h"
typedef std::list<Socket *> socket_list;

int Menu(int choice)
{
  if (choice == 1)
  {
  }
}

int main()
{
  SocketServer in(8001, 1);

  Socket *s = in.Accept();
  std::cout << "Client connected\n";

  while (s != 0)
  {

    std::string message = "";
    int start = time(NULL);
    while (difftime(time(NULL), start) < 40)
    {
      message = s->ReceiveBytes();
      if (message == "")
        continue;
      else
      {
        break;
      }
    }
    std::cout << "Client choice: " << message << std::endl;
    if (message == "")
    {
      // s->Close();
      // s = nullptr;
      // s = in.Accept();
      // continue;
      break;
    }
    else if (message == "1")
    {
      int flag = 0;
      while (true)
      {
        message = s->ReceiveBytes();
        if (message == "ESC")
        {
          cout << "Stop Send Key!\n";
          break;
        }
        sendKeyEvent(s, flag);
        Sleep(150);
      }
    }
    else if (message == "21" || message == "41")
    {
      ProcessController pc;
      std::wstring wstr = pc.listAllProgram();
      std::cout << MyHelper::convertWStringtoStr(wstr) << endl;
      s->SendBytes(MyHelper::convertWStringtoStr(wstr));
    }
    else if (message == "22")
    {
      ProcessController pc;

      std::wstring wstr = pc.listAllProgram();
      s->SendBytes(MyHelper::convertWStringtoStr(wstr));
      start = time(NULL);

      while (difftime(time(NULL), start) < 20)
      {
        message = s->ReceiveBytes();
        if (message == "")
          continue;
        else
        {
          break;
        }
      }

      pc.closeProgram(MyHelper::strToWstr(message));
    }
    else if (message == "23")
    {
      ProcessController pc;
      start = time(NULL);

      while (difftime(time(NULL), start) < 20)
      {
        message = s->ReceiveBytes();
        if (message == "")
          continue;
        else
        {
          break;
        }
      }
      std::wstring wstr = pc.listAllProcessOfProgram(MyHelper::strToWstr(message));
      std::wcout << wstr;
      s->SendBytes(MyHelper::convertWStringtoStr(wstr));
    }
    else if (message == "42")
    {
      ProcessController pc;

      std::wstring wstr = pc.listAllProgram();
      s->SendBytes(MyHelper::convertWStringtoStr(wstr));
      start = time(NULL);

      while (difftime(time(NULL), start) < 20)
      {
        message = s->ReceiveBytes();
        if (message == "")
          continue;
        else
        {
          break;
        }
      }

      pc.closeProgram(MyHelper::strToWstr(message));
    }
    else if (message == "43")
    {
      vector<Software>* v = AppLister::GetAppLister(true);
      std::wstringstream ss;
      for(int i = 0; i < v->size(); i++)
      {
        ss << v->at(i);
        // wcout << v->at(i);
      }
      wstring rdata = MyHelper::wstring_to_utf8_wstring(ss.str());
      wcout << rdata;
      s->SendBytes(MyHelper::convertWStringtoStr(rdata));
      start = time(NULL);
      while (difftime(time(NULL), start) < 20)
      {
        message = s->ReceiveBytes();
        if (message == "")
          continue;
        else
        {
          break;
        }
      }
      ProcessController pc;
      
      if(pc.startApp(MyHelper::strToWstr(message)))
      {
        cout << "Start success\n";
      }
    }

    fflush(stdout);
  }
  fflush(stdout);
  return 0;
}