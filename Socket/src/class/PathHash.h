#ifndef PATHHASH_H
#define PATHHASH_H


#include <iostream>
#include <filesystem>
#include <chrono>
#include <thread>
#include <unordered_set>
#include<string>

namespace fs = std::filesystem;
struct PathHash
{
    std::size_t operator()(const fs::path &p) const
    {
        return std::hash<std::string>{}(p.string());
    }
};

#endif