#pragma once

#include <memory>
#include <string>

namespace Utils {

    template<typename... Args>
    std::string sprintf(const std::string &format, Args... args) {
        int size = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;

        std::unique_ptr<char[]> buf(new char[size]);
        std::snprintf(buf.get(), size, format.c_str(), args...);

        return std::string(buf.get(), buf.get() + size - 1);
    }

    bool CheckFile(const std::string &fullpath);

    bool CreateSubfolder(const std::string &fullpath);

    bool CopyFile(const std::string &in, const std::string &out);

    bool GetSerialId(std::string &serialID);

    bool GetLatestLogName(std::string &name);

} // namespace Utils
