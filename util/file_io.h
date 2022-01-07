#pragma once

#include <string>
#include <fstream>

#include "spdlog/spdlog.h"

bool readFile(const std::string filename, std::string &file_content)
{
    std::ifstream file(filename);

    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            file_content.append(line);
            file_content.append("\n");
        }
        file.close();
        return true;
    }
    spdlog::error("Failed reading file {}\n", filename);
    return false;
}