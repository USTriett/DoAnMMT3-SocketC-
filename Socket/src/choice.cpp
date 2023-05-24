#include <iostream>
#include "./class/KeyEvent.h"

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
    return choice;
}