#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H

#include <iostream>
#include <filesystem>
#include <chrono>
#include <thread>
#include <unordered_set>
#include<string>
#include"PathHash.h"
namespace fs = std::filesystem;

class FileController
{
public:
    
    virtual ~FileController();
    FileController();
    FileController(std::string path);
    FileController(const FileController& fc);
    FileController& operator=(const FileController& fc);

    fs::file_time_type get_last_time_edit();
    bool isChanged();
    bool isCreateNews();
    bool isDeleted();
    void printMessage();
    void updateFiles();

private:
    // int count;
    fs::path path_to_watch;
    std::unordered_set<fs::path, PathHash> files; // files in directories
    fs::file_time_type last_time_edit;

    void InitFiles(fs::path path);

};

#endif

// int main()
// {
//     // Đường dẫn đến thư mục cần theo dõi
//     fs::path path_to_watch = fs::current_path();
//     std::cout << "Watching path: " << path_to_watch << '\n';

//     // Lấy thời gian sửa đổi cuối cùng của thư mục
//     auto last_write_time = fs::last_write_time(path_to_watch);
//     std::unordered_set<fs::path, PathHash> files;
//     for (const auto &entry : fs::directory_iterator(path_to_watch))
//     {
//         files.insert(entry.path());
//     }
//     while (true)
//     {
//         // Đợi 1 giây trước khi kiểm tra lại
//         std::this_thread::sleep_for(std::chrono::milliseconds(1000));

//         // Kiểm tra xem có sự thay đổi nào trong thư mục không

//         if (last_write_time != fs::last_write_time(path_to_watch))
//         {
//             last_write_time = fs::last_write_time(path_to_watch);

//             // check file moi
//             for (const auto &entry : fs::directory_iterator(path_to_watch))
//             {
//                 if (files.find(entry.path()) == files.end()) // if entry.path() does not have in directory find() return files.end()
//                 {
//                     std::cout << "New file: " << entry.path() << '\n';
//                 }
//             }
//             // check xoa file
//             std::unordered_set<fs::path, PathHash> directories;
//             for (const auto &entry : fs::directory_iterator(path_to_watch))
//             {
//                 directories.insert(entry.path());
//             }
//             for (const auto &path : files)
//             {
//                 if (directories.find(path) == directories.end())
//                 {
//                     std::cout << "Deleted file: " << path << '\n';
//                 }
//             }
//             // Cập nhật lại danh sách các tệp
//             files.clear();
//             for (const auto &entry : fs::directory_iterator(path_to_watch))
//             {
//                 files.insert(entry.path());
//             }
//         }
//     }

//     return 0;
// }