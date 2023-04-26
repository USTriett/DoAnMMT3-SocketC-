#include <iostream>
#include <filesystem>
#include <chrono>
#include <thread>
#include <unordered_set>
#include "fileControl.h"
#include"PathHash.h"
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
