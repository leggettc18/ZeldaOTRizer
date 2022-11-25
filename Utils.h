#pragma once

#ifndef ZELDAOTRIZERUTILS_H
#define ZELDAOTRIZERUTILS_H

#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

namespace FileUtils {
inline std::vector<char> ReadAllBytes(const std::filesystem::path& filePath) {
    std::ifstream file(filePath, std::ios::in | std::ios::binary | std::ios::ate);

    if (!file) {
        return std::vector<char>();
    }

    int32_t fileSize = (int32_t)file.tellg();
    file.seekg(0);
    char* data = new char[fileSize];
    file.read(data, fileSize);
    std::vector<char> result = std::vector<char>(data, data + fileSize);
    delete[] data;

    return result;
};
}; // namespace FileUtils

namespace StringUtils {
inline void ReplaceOriginal(std::string& str, const std::string& from, const std::string& to) {
    size_t startPos = str.find(from);

    while (startPos != std::string::npos) {
        str.replace(startPos, from.length(), to);
        startPos = str.find(from);
    }
}

inline std::vector<std::string> Split(std::string s, const std::string& delimiter) {
    size_t posStart = 0, posEnd, delimLen = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((posEnd = s.find(delimiter, posStart)) != std::string::npos) {
        token = s.substr(posStart, posEnd - posStart);
        posStart = posEnd + delimLen;
        res.push_back(token);
    }

    res.push_back(s.substr(posStart));
    return res;
}
};

#endif
