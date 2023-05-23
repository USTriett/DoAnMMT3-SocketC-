#include "./class/Socket.h"
#include <process.h>
#include <string>
#include <list>
#include <iostream>
#include "./class/ProcessController.h"
#include "./class/AppLister.h"
#include <thread>
#include <future>
typedef std::list<Socket *> socket_list;

socket_list g_connections;

void printApp(std::promise<wstring> &prom)
{
  std::vector<Software> *ptr = AppLister::GetAppLister(0);
  std::wstringstream ss;
  for (int i = 0; i < ptr->size(); i++)
  {
    ss << ptr->at(i) << std::endl;
  }
  prom.set_value(ss.str());
}

void printProcess(std::promise<wstring> &prom)
{
  ProcessController pc;
  prom.set_value(pc.listAllProgram());
}
unsigned __stdcall Connection(void *a)
{
  Socket *s = (Socket *)a;

  g_connections.push_back(s);

  std::cout << "Connect Success\n";
  std::promise<std::wstring> prom;

  // Lấy future từ promise
  std::future<std::wstring> fut = prom.get_future();
  while (1)
  {

    std::thread t1(printApp, std::ref(prom));
    std::wstring result = fut.get();
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::string str = converter.to_bytes(result);
    std::cout << str;
    s->SendBytes(str);
    t1.join();
    // t2.join();

    s->SendLine("input '.' to end");
    std::string req = s->ReceiveLine();
    std::cout << req << endl;
    // cout << str.length() << endl;
    system("pause");
    if (req.compare(".\n") == 0)
      break;
  }

  g_connections.remove(s);

  delete s;

  return 0;
}

int main()
{
  SocketServer in(8001, 1);

  while (1)
  {
    Socket *s = in.Accept();
    unsigned threadID;
    HANDLE hThread = (HANDLE)_beginthreadex(0, 0, Connection, (void *)s, 0, &threadID);
    // Kiểm tra xem hàm _beginthreadex có thực thi thành công không
    if (hThread == NULL)
    {
      // Xử lý lỗi ở đây
      std::cerr << "cannot init thread" << std::endl;
    }
    //// Sau khi sử dụng luồng, kết thúc luồng bằng cách gọi hàm _endthreadex với tham số là 0
    _endthreadex(0);
    // Sau khi kết thúc luồng, hủy bỏ handle của luồng bằng cách gọi hàm CloseHandle
    CloseHandle(hThread);
  }
  return 0;
}