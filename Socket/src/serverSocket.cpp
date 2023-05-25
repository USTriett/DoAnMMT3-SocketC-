#include "./class/Socket.h"
#include <process.h>
#include <string>
#include <list>
#include <iostream>
#include "./class/ProcessController.h"
#include "./class/KeyEvent.h"
#include "./class/MyHelper.h"
#include "./class/Screenshot.h"
#include <thread>
#include "./class/AppLister.h"
#include "./class/fileControl.h"
typedef std::list<Socket *> socket_list;

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
    else if (message == "3")
    {
      std::cout << "Screenshot\n";
      if (fs::exists("screenshot.bmp"))
        {
          std::cout << "imgs exist!\n"; 
          fs::remove("screenshot.bmp");
        }
      string name = "";
      cout << "Waiting...";
      while(name == "")
      {
        name = s->ReceiveBytes();
      }
     
      ScreenShotAndSendToClient(s, "screenshot.bmp");
      // cout << "send" << endl;
      
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
      vector<Software> *v = AppLister::GetAppLister(true);
      std::wstringstream ss;
      for (int i = 0; i < v->size(); i++)
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

      if (pc.startApp(MyHelper::strToWstr(message)))
      {
        cout << "Start success\n";
      }
    }
    // else if (message == "51")
    // {
    //   FileController fc("C:\\");
    //   vector<string> DirectFiles = fc.showDirectFiles();
    //   string newString;
    //   for (int i = 0; i < DirectFiles.size(); i++)
    //     // s->SendBytes(DirectFiles[i]);
    //     newString = newString + DirectFiles[i] + "\n";
    //   cout << newString;
    //   s->SendBytes(newString);

    //   // string choosenFolder = s->ReceiveBytes();
    //   // cout << "Choosen folder: " << choosenFolder << endl;

    //   // vector<string> AllFiles = fc.showAllFiles(choosenFolder);
    //   // for (int i = 0; i < AllFiles.size(); i++) {
    //   //   s->SendBytes(AllFiles[i]);
    //   // }
    // }
    else if (message == "52")
    {
      FileController fc("C:\\");
      string choosenFolder;
      cout << "Start watching\n";
      while (true)
      {
        choosenFolder = s->ReceiveBytes();

        if (choosenFolder != "")
          break;
      }

      cout << "Choosen folder: " << choosenFolder << endl;
      vector<string> AllFiles = fc.showAllFiles(choosenFolder);
      string newString2;
      for (int i = 0; i < AllFiles.size(); i++)
      {
        // s->SendBytes(AllFiles[i]);
        newString2 = newString2 + AllFiles[i] + "\n";
      }

      s->SendBytes(newString2);
    }
    else if (message == "51")
    {
      // cout << "I don't see anything\n\n";
      FileController fc;
      // string currentFolder = fc.get_path_to_watch();
      // cout << "Current path is " << currentFolder << '\n';
      string infoChanged;
      while (difftime(time(NULL), start) < 20)
      {
        infoChanged = fc.generalChange();
        auto now = std::chrono::system_clock::now();

        // Convert to time_t
        std::time_t time = std::chrono::system_clock::to_time_t(now);

        // Convert to tm struct
        std::tm *timeinfo = std::localtime(&time);

        // Convert to string
        std::stringstream ss;
        ss << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S");
        std::string time_string = ss.str();

        // Print the time string
        // std::cout << "Current time: " << time_string << std::endl;

        if (infoChanged != "")
        {
          s->SendBytes(time_string + " " + infoChanged);
        }
      }
      // cout << infoChanged << endl;
    }

    fflush(stdout);
  }
  fflush(stdout);
  return 0;
}