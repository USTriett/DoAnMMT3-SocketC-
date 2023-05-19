#include"./ProcessController.h"
int main()
{
    ProcessController* a = new ProcessController();
    a->listAllProgram();
    system("Pause");
    std::cout << "before close: " << a->getNumberOfProcessess() << std::endl;
    system("Pause");

    a->closeProgram("FoxitReader.exe");
    system("Pause");
    std::cout << "after close: " << a->getNumberOfProcessess() << std::endl;

    system("Pause");
    a->listAllProgram();
    return 0;
}