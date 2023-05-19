#include "./class/Socket.h"
#include"./class/fileControl.h"
#include <iostream>
namespace fs = std::filesystem;



using namespace std;

int main() {

  try {
    SocketClient s("127.0.0.1", 8001);

    FileController* fc = new FileController("D:\\HCMUS\\Nam2\\semester-4\\computer-network\\socket\\testFolder");
    fc->printMessage();
    
    while (1) {
      cout << 1 << endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if(fc->isChanged()){
            std::cout << "Message: Folder Change!\n\n";
              s.SendLine("Message: Folder Change!\n");

            if(fc->isCreateNews())
            {
              s.SendLine("Message: Inserted new file...\n");
                std::cout << "\nMessage: Inserted new file...\n\n";
            }
            if(fc->isDeleted())
            {
                s.SendLine("Message: Deleted file...\n");

                std::cout << "\nMessage: Deleted file...\n\n";
            }
        } 
      // string l = s.ReceiveLine();
      // if (l.empty()) break;
      // cout << l;
      // cout.flush();
    }

  } 
  catch (const char* s) {
    cerr << s << endl;
  } 
  catch (std::string s) {
    cerr << s << endl;
  } 
  catch (...) {
    cerr << "unhandled exception\n";
  }

  return 0;
}