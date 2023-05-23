#include "./class/Socket.h"
#include <iostream>
#include<chrono>
#include<thread>
using namespace std;

int main()
{

  try
  {
    SocketClient s("127.0.0.1", 8001);
    
    while (1)
    {
      std::this_thread::sleep_for(std::chrono::seconds(3));
      string l = s.ReceiveBytes();
      if (l.empty()) break;
      cout << "Message: " << l << endl;

      std::string input;
      std::getline(std::cin, input);
      cout << input;
      s.SendLine(input);
      // cout.flush();
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