#include "./class/Socket.h"
#include <iostream>
#include<set>
#include <chrono>
#include <thread>
#include "./class/KeyEvent.h"
#include "./class/ProcessController.h"
#include "./class/MyHelper.h"
#include"./class/AppLister.h"
#include <stdlib.h>
using namespace std;
using namespace std;
using namespace this_thread;
using namespace chrono;

struct myProcess
{
  string p_id;
  string mainProg;
  string current_thread;
  string pageFaults;
};

bool operator<(const myProcess& p1, const myProcess& p2) {
  return p1.mainProg < p2.mainProg;  // Compare based on process ID
}

std::vector<Software> convertDataToSoftware(const string &data)
{
  std::vector<Software> rs;
  std::string line[4];
  std::istringstream iss(data);

  int count = 0;
  while (std::getline(iss, line[count]))
  {
    // wcout << MyHelper::strToWstr(line[count]) << endl;
    
    if (count == 3)
    {
      // Software s(MyHelper::strToWstr(line[0]),MyHelper::strToWstr(line[1]),MyHelper::strToWstr(line[2]),MyHelper::strToWstr(line[3]));
      // rs.push_back(s);
      count = 0;
    }
    else
    {
      ++count;
    }
  }

  return rs;
}

std::vector<myProcess> convertData(const string &data)
{
  std::vector<myProcess> rs;
  std::string line[4];
  myProcess p;
  std::istringstream iss(data);

  int count = 0;
  while (std::getline(iss, line[count]))
  {
    if (count == 3)
    {
      p.p_id = line[0];
      p.mainProg = line[1];
      p.current_thread = line[2];
      p.pageFaults = line[3];
      rs.push_back(p);
      count = 0;
    }
    else
    {
      ++count;
    }
  }

  return rs;
}

int Menu()
{
  int choice = 1;
  std::cout << "1.Catch Key\n";
  std::cout << "2.Processes\n";
  std::cout << "3.Screenshot\n";
  std::cout << "4.Application\n";
  std::cout << "5.File\n\n";
  std::cout << "input your Choice: ";
  fflush(stdin);
  do
  {
    try
    {
      std::cin >> choice;
    }
    catch (const char *s)
    {
      std::cerr << s << endl;
    }
    if (choice <= 5 && choice >= 1)
      break;
  } while (true);
  if (choice == 2)
  {
    std::cout << "1.Show Current Processes\n";
    std::cout << "2.Stop Process\n";
    std::cout << "3.Find Processes by Program name\n\n";
    std::cout << "input your Choice: ";
    choice = 20;
    do
    {
      try
      {
        fflush(stdin);
        std::cin >> choice;
      }
      catch (const char *s)
      {
        std::cerr << s << endl;
      }
      if (choice <= 3 && choice >= 1)
        break;
    } while (true);

    return 20 + choice;
  }

  if (choice == 4)
  {
    std::cout << "1.Show Running App\n";
    std::cout << "2.Stop App\n";
    std::cout << "3.Start App\n\n";
    std::cout << "input your Choice: ";
    choice = 40;
    do
    {
      try
      {
        fflush(stdin);
        std::cin >> choice;
      }
      catch (const char *s)
      {
        std::cerr << s << endl;
      }
      if (choice <= 3 && choice >= 1)
        break;
    } while (true);

    return 40 + choice;
  }

  return choice;
}

void process(SocketClient s, string choice)
{
  if (choice == "1")
  {
    int start = time(NULL);
    fflush(stdout);

    cout << "Start Key Catch\n";
    while (difftime(time(NULL), start) < 10)
    {
      // cout << "Running..." << endl;
      cout << ReceivedKeyEvent(s);
      Sleep(200);
      if (difftime(time(NULL), start) >= 10)
      {
        fflush(stdin);
        cout << "Press 'ESC' to escape:\n";
        char code = 98;
        fflush(stdout);
        cin.ignore(10000, '\n');
        code = getch();

        cout << "\n\n"
             << (int)code << endl;
        if ((int)code == 27)
        {
          s.SendBytes("ESC");
          break;
        }
        else
        {
          start = time(NULL);
        }
      }
    }
    cout << "Stopped.\n"
         << endl;
  }
  else if (choice == "21")
  {
    // fflush(stdout);
    int start = time(NULL);

    while (difftime(time(NULL), start) < 20)
    {
      string data = s.ReceiveBytes();
      cout << "Current Processes on Client:\n";
      // cout << data << endl;
      vector<myProcess> pcs = convertData(data);
      cout << pcs.size() << endl;
      for (const auto &i : pcs)
      {
        cout << "Process ID: " << i.p_id << std::endl;
        cout << "Main program: " << i.mainProg << std::endl;
        cout << "Current Threads: " << i.current_thread << std::endl;
        cout << "Page faults: " << i.pageFaults << std::endl;
      }
      if (data != "")
        break;
    }
    // print
  }
  else if (choice == "22")
  {
    // fflush(stdout);
    int start = time(NULL);

    while (difftime(time(NULL), start) < 20)
    {
      string data = s.ReceiveBytes();
      cout << "Current Processes on Client:\n";
      // cout << data << endl;
      vector<myProcess> pcs = convertData(data);
      cout << pcs.size() << endl;
      for (const auto &i : pcs)
      {
        cout << "Main program: " << i.mainProg << std::endl;
      }
      if (data != "")
        break;
    }
    fflush(stdin);
    string name;
    getline(cin, name);
    s.SendBytes(name);
    string message = s.ReceiveBytes();
    cout << message << endl;
  }
  else if (choice == "23")
  {
    fflush(stdin);
    string name;
    cout << "input program name: ";
    getline(cin, name);
    s.SendBytes(name);
    // fflush(stdout);
    int start = time(NULL);

    while (difftime(time(NULL), start) < 20)
    {
      string data = s.ReceiveBytes();
      cout << "The program is running on Processes:\n";
      // cout << data << endl;
      vector<myProcess> pcs = convertData(data);
      cout << pcs.size() << endl;
      for (const auto &i : pcs)
      {
        cout << "Process ID: " << i.p_id << std::endl;
        cout << "Main program: " << i.mainProg << std::endl;
        cout << "Current Threads: " << i.current_thread << std::endl;
        cout << "Page faults: " << i.pageFaults << std::endl;
      }
      if (data != "")
        break;
    }

  }
  else if(choice == "3")
  {

  }
  else if(choice == "41")
  {
    int start = time(NULL);

    while (difftime(time(NULL), start) < 20)
    {
      string data = s.ReceiveBytes();
      cout << "Current App running on server:\n";
      // cout << data << endl;
      vector<myProcess> pcs = convertData(data);
      std::set<myProcess> s(pcs.begin(), pcs.end());
      cout << pcs.size() << endl;
      for (const auto &i : s)
      {     
        cout << "Main program: " << i.mainProg << std::endl;
      }
      if (data != "")
        break;
    }
  }
  else if(choice == "42")
  {
     int start = time(NULL);

    while (difftime(time(NULL), start) < 20)
    {
      string data = s.ReceiveBytes();
      cout << "Current App running on server:\n";
      // cout << data << endl;
      vector<myProcess> pcs = convertData(data);
      std::set<myProcess> s(pcs.begin(), pcs.end());
      cout << pcs.size() << endl;
      for (const auto &i : s)
      {     
        cout << "Main program: " << i.mainProg << std::endl;
      }
      if (data != "")
        break;
    }
    fflush(stdin);
    string name;
    std::cout << "Input app to stop: ";
    getline(cin, name);
    s.SendBytes(name);
    string message = s.ReceiveBytes();
    cout << message << endl;
  }
  else if(choice == "43")
  {
    int start = time(NULL);

    while (difftime(time(NULL), start) < 20)
    {
      
      string data = s.ReceiveBytes();
      // cout << ":\n";
      cout << data << endl;
      // cout << "App in this device:\n";
      vector<Software> pcs = convertDataToSoftware(data);
      // for(const auto& i:pcs)
      // {
      //   std::wcout << i;
      // }
      if (data != "")
        break;
    }
    fflush(stdin);
    string path;
    std::cout << "Input path app to start: ";
    getline(cin, path);
    s.SendBytes(path);
  }
  else
  {
    cout << "Invalid choice\n"
         << endl;
  }
}

int main()
{

  try
  {
    SocketClient s("127.0.0.1", 8001);

    int start = time(NULL);
    while (true)
    {
      fflush(stdin);
      system("cls");
      int number = Menu();
      stringstream ss;
      ss << number;
      string choice = ss.str();
      std::cout << "choice: " << choice << endl;
      s.SendBytes(choice);
      if (choice == "")
        break;
      process(s, choice);
    }
  }
  catch (const char *s)
  {
    cerr << s << endl;
  }
  catch (std::string s)
  {
    cerr << s << endl;
  }
  catch (...)
  {
    cerr << "unhandled exception\n";
  }

  return 0;
}