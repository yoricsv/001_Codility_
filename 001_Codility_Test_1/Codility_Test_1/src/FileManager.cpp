//
// Created by Yoric on 22-Feb-22.
//
#include "FileManager.h"

namespace
{
    constexpr const char * DEFAULT_FILE_PATH[] =
    {
        "",
        "res/",
        "../res/"
    };
}

std::string FileManager::resourceLocation(std::string filename) const
{
    std::string result;

    std::replace(
        filename.begin(),
        filename.end(),
        '\\',
        '/'
    );

    this ->
        forEachPath(
            [&](const std::string & path)
            {
//                SDL_RWops * file = SDL_RWFromFile((path + filename).c_str(), "r");
//                if (file != nullptr)
//                {
//                    SDL_RWclose(file);
//                    result = path + filename;
//                    return;
//                }
            }
        );

    return result;
}

void FileManager::setFindPaths(
        std::vector<std::string> paths
    )
{
    _path = std::move(paths);
}

void FileManager::forEachPath(
        const std::function<void(std::string)> & callback
    ) const
{
    for (const auto & path : _path)
    {
        callback(path);
//        callback(XSTRINGIFY(PROJECT_ROOT_FOLDER)"/" + path);
    }

    for (const auto & path : DEFAULT_FILE_PATH)
    {
        callback(path);
//        callback(std::string(XSTRINGIFY(PROJECT_ROOT_FOLDER)"/") + path);
    }
}
