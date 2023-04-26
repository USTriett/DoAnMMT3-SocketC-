#include"./class/fileControl.h"

namespace fs = std::filesystem;

int main()
{
    FileController* fc = new FileController("D:\\HCMUS\\Nam2\\semester-4\\computer-network\\socket\\testFolder");
    fc->printMessage();
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if(fc->isChanged()){
            std::cout << "Message: Folder Change!\n\n";
            if(fc->isCreateNews())
            {
                std::cout << "\nMessage: Inserted new file...\n\n";
            }
            if(fc->isDeleted())
            {
                std::cout << "\nMessage: Deleted file...\n\n";
            }
        }
    }

    return 0;
}