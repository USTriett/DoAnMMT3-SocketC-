#include <iostream>
#include <filesystem>
#include <thread>
#include <unordered_set>
#include "fileControl.h"
#include "PathHash.h"
namespace fs = std::filesystem;
void FileController::InitFiles(fs::path path)
{
    for (auto const &entry : fs::directory_iterator(path))
    {
        this->files.insert(entry.path());
    }
}

FileController::~FileController()
{
}

FileController::FileController()
{
    this->path_to_watch = fs::current_path();
    this->InitFiles(path_to_watch);
    this->last_time_edit = fs::last_write_time(path_to_watch);
}

FileController::FileController(std::string path)
{
    this->path_to_watch = path;
    this->InitFiles(path_to_watch);
    this->last_time_edit = fs::last_write_time(path_to_watch);
}

FileController::FileController(const FileController &fc)
{
    this->path_to_watch = fc.path_to_watch;
    this->InitFiles(path_to_watch);
    this->last_time_edit = fs::last_write_time(path_to_watch);
}

fs::file_time_type FileController::get_last_time_edit()
{
    return fs::last_write_time(path_to_watch);
}

bool FileController::isChanged()
{
    if (this->get_last_time_edit() != this->last_time_edit)
    {
        this->last_time_edit = fs::last_write_time(path_to_watch);
        return true;
    }
    return false;
}

bool FileController::isCreateNews()
{

    for (const auto &entry : fs::directory_iterator(path_to_watch))
    {
        if (files.find(entry.path()) == files.end()) // if entry.path() does not have in directory find() return files.end()
        {
            std::cout << "New file: " << entry.path() << '\n';
            this->updateFiles();
            return true;
        }
    }

    return false;
}

bool FileController::isDeleted()
{
    std::unordered_set<fs::path, PathHash> directories;
    for (const auto &entry : fs::directory_iterator(path_to_watch))
    {
        directories.insert(entry.path());
    }
    for (const auto &path : files)
    {
        if (directories.find(path) == directories.end())
        {
            std::cout << "Deleted file: " << path << '\n';
            this->updateFiles();
            directories.clear();
            return true;
        }
    }
    directories.clear();
    return false;
}

void FileController::printMessage()
{
    std::cout << "Start watching at " << this->path_to_watch << '\n';
}

void FileController::updateFiles()
{
    files.clear();
    for (const auto &entry : fs::directory_iterator(path_to_watch))
    {
        files.insert(entry.path());
    }
}

vector<string> FileController::showDirectFiles()
{
    vector<string> directFiles;
    if (!fs::is_directory(this->path_to_watch))
    {
        cout << "Not a directory";
        return directFiles;
    }

    if (fs::is_empty(this->path_to_watch))
    {
        cout << "Empty folder";
        return directFiles;
    }

    fs::path pathWatching = this->path_to_watch;
    for (const auto &entry : fs::directory_iterator(pathWatching))
    {
        std::cout << entry.path().string();
        directFiles.push_back(entry.path().string());
        if (fs::is_directory(entry))
        {
            cout << " (folder)";
        }
        cout << std::endl;
    }
    return directFiles;
}

vector<string> FileController::showAllFiles(string stringPathWatching)
{
    vector<string> allFiles;
    fs::path pathWatching(stringPathWatching);
    if (!fs::is_directory(pathWatching))
    {
        cout << "Not a directory";
        return allFiles;
    }

    if (fs::is_empty(pathWatching))
    {
        cout << "Empty folder";
        return allFiles;
    }

    for (const auto &entry : fs::recursive_directory_iterator(pathWatching))
    {
        // std::cout << entry.path().string() << std::endl;
        allFiles.push_back(entry.path().string());
    }

    return allFiles;
}

string FileController::get_path_to_watch()
{
    return this->path_to_watch.string();
}

string FileController::generalChange()
{
    string currentFolder = get_path_to_watch();

    // string res = "The current path is " + currentFolder + "\n";
    string res = "";
    if (!isChanged())
    {
    }
    // res += "The folder is not changed\n";
    else
    {
        res += "The folder is changed\n";

        // if (isCreateNews())
        // {
        //     for (const auto &entry : fs::directory_iterator(path_to_watch))
        //     {
        //         if (files.find(entry.path()) == files.end()) // if entry.path() does not have in directory find() return files.end()
        //         {
        //             std::cout << "New file: " << entry.path() << '\n';
        //         }
        //     }
        // }

        for (const auto &entry : fs::directory_iterator(path_to_watch))
        {
            if (files.find(entry.path()) == files.end()) // if entry.   path() does not have in directory find() return files.end  ()
            {
                res = res + "New file: " + entry.path().string() + '\n';
                this->updateFiles();
            }
        }

        // if (isDeleted())
        // {
        //     res += "The folder has been deleted one or some files\n";
        //     std::unordered_set<fs::path, PathHash> directories;
        //     for (const auto &entry : fs::directory_iterator(path_to_watch))
        //     {
        //         directories.insert(entry.path());
        //     }
        //     for (const auto &path : files)
        //     {
        //         if (directories.find(path) == directories.end())
        //         {
        //             res += "Deleted file: " + path.string() + '\n';
        //             directories.clear();
        //         }
        //     }
        //     directories.clear();
        // }

        std::unordered_set<fs::path, PathHash> directories;
        for (const auto &entry : fs::directory_iterator(path_to_watch))
        {
            directories.insert(entry.path());
        }
        for (const auto &path : files)
        {
            if (directories.find(path) == directories.end())
            {
                res = res + "Deleted file: " + path.string() + '\n';
                this->updateFiles();
                directories.clear();
            }
        }
        // directories.clear();

        this->updateFiles();
    }

    return res;
}