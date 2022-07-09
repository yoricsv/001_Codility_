//
// Created by Yoric on 22-Feb-22.
//
#pragma once
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <algorithm>
#include <functional>
#include <string>
#include <string_view>
#include <vector>

class FileManager
{
public:
    [[nodiscard]] std::string resourceLocation(std::string filename) const;

    void setFindPaths(std::vector<std::string> findPaths);

    void forEachPath (const std::function<void(std::string)>& callback) const;

private:
    std::vector<std::string> _path;
};

#endif //FILE_MANAGER_H
