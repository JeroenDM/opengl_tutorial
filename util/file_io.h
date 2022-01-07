#pragma once

#include <string>
#include <fstream>

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
    std::cout << "Failed reading file " << filename << "\n";
    return false;
}