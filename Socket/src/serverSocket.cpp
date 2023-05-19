
#include "./class/Socket.h"
#include <process.h>
#include <string>
#include <list>
#include<iostream>
typedef std::list<Socket*> socket_list;

socket_list g_connections;

unsigned __stdcall Connection(void* a) {
  Socket* s = (Socket*) a;

  g_connections.push_back(s);

 
  s->SendLine("Welcome to the Message Distributor");
  s->SendLine("Welcome");
  while (1) {
    
    std::string r = s->ReceiveLine();
    if (r.empty()) break;

    std::cout << r << std::endl;
    std::cout.flush();

    for (socket_list::iterator os =g_connections.begin();
                               os!=g_connections.end(); 
                               os++) {
      if (*os != s) (*os)->SendLine(r);
    }
  }

  g_connections.remove(s);

  delete s;

  return 0;
}

int main() {
  SocketServer in(8001,1);
  
  while (1) {
    Socket* s=in.Accept();
  
    unsigned ret;
    _beginthreadex(0,0,Connection,(void*) s,0,&ret);
  }
  
  return 0;
}