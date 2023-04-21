#include "Utils.hpp"
#include <cstring>

#include <coreinit/debug.h>
#include <coreinit/mcp.h>
#include <dirent.h>
#include <mbedtls/aes.h>
#include <mbedtls/sha256.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>

namespace Utils {
    bool CheckFile(const std::string &fullpath) {
        struct stat filestat {};

        char dirnoslash[strlen(fullpath.c_str()) + 2];
        snprintf(dirnoslash, sizeof(dirnoslash), "%s", fullpath.c_str());

        while (dirnoslash[strlen(dirnoslash) - 1] == '/') {
            dirnoslash[strlen(dirnoslash) - 1] = '\0';
        }

        char *notRoot = strrchr(dirnoslash, '/');
        if (!notRoot) {
            strcat(dirnoslash, "/");
        }

        if (stat(dirnoslash, &filestat) == 0) {
            return true;
        }

        return false;
    }

    bool CreateSubfolder(const std::string &fullpath) {
        if (fullpath.empty()) {
            return false;
        }

        int32_t result = 0;

        char dirnoslash[fullpath.length() + 1];
        strcpy(dirnoslash, fullpath.c_str());

        auto pos = strlen(dirnoslash) - 1;
        while (dirnoslash[pos] == '/') {
            dirnoslash[pos] = '\0';
            pos--;
        }

        if (CheckFile(dirnoslash)) {
            return true;
        } else {
            char parentpath[strlen(dirnoslash) + 2];
            strcpy(parentpath, dirnoslash);
            char *ptr = strrchr(parentpath, '/');

            if (!ptr) {
                //! Device root directory (must be with '/')
                strcat(parentpath, "/");
                struct stat filestat {};
                if (stat(parentpath, &filestat) == 0) {
                    return true;
                }

                return false;
            }

            ptr++;
            ptr[0] = '\0';

            result = CreateSubfolder(parentpath);
        }

        if (!result)
            return false;

        if (mkdir(dirnoslash, 0777) < 0) {
            return false;
        }

        return true;
    }

    bool CopyFile(const std::string &in, const std::string &out) {
        size_t size;

        int source = open(in.c_str(), O_RDONLY, 0);
        int dest   = open(out.c_str(), 0x602, 0644);
        if (source < 0) {
            return false;
        }
        if (dest < 0) {
            close(source);
            return false;
        }

        auto bufferSize = 128 * 1024;
        char *buf       = (char *) malloc(bufferSize);
        if (buf == nullptr) {
            return false;
        }

        bool result = true;
        while ((size = read(source, buf, bufferSize)) > 0) {
            if (write(dest, buf, size) < 0) {
                result = false;
                break;
            }
        }

        free(buf);

        close(source);
        close(dest);
        return result;
    }

    bool GetSerialId(std::string &serialID) {
        bool result = false;
        alignas(0x40) MCPSysProdSettings settings{};
        auto handle = MCP_Open();
        if (handle >= 0) {
            if (MCP_GetSysProdSettings(handle, &settings) == 0) {
                serialID = std::string(settings.code_id) + settings.serial_id;
                result   = true;
            } else {
                // DEBUG_FUNCTION_LINE_ERR("Failed to get SerialId");
            }
            MCP_Close(handle);
        } else {
            // DEBUG_FUNCTION_LINE_ERR("MCP_Open failed");
        }
        return result;
    }

} // namespace Utils
