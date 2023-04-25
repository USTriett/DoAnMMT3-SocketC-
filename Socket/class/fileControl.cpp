#include <iostream>
#include <filesystem>
#include <chrono>
#include <thread>
#include <unordered_set>
#include"fileControl.h"

namespace fs = std::filesystem;
void FileController::InitFiles(fs::path path)
{
    for(auto const& entry:fs::directory_iterator(path))
    {
        
    }
}

FileController::FileController()
{
    this->path_to_watch = fs::current_path();

}


FileController::FileController(fs::path path)
{
}

FileController::FileController(const FileController &fc)
{
}

bool FileController::isCreateNews()
{
    return false;
}

bool FileController::isDeleted()
{
    return false;
}

void FileController::printMessage()
{
}
