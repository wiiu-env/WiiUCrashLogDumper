#pragma once
#include "Screen.hpp"
#include "common.h"
#include <dirent.h>
#include <queue>

class DumpLogsScreen : public Screen {
public:
    DumpLogsScreen();
    ~DumpLogsScreen() override;

    void DrawSimpleText(const std::string &text) const;
    void DrawSimpleText(const std::vector<std::string> &texts) const;

    void Draw() override;

    bool Update(Input &input) override;

private:
    enum DumpState {
        DUMP_STATE_SELECT,
        DUMP_STATE_ERROR,
        DUMP_STATE_CREATE_DIRECTORY,
        DUMP_STATE_OPEN_DIR,
        DUMP_STATE_COPY_FILE,
        DUMP_STATE_DUMPING_DONE,
    };
    DumpState mDumpState = DUMP_STATE_SELECT;

    std::string mDestinationDirectory;
    const std::string mSourceDirectory = CRASH_LOG_SOURCE_PATH;
    DIR *mSourceDirectoryHandle        = nullptr;

    std::queue<std::string> mFilesToCopy;

    const int mDefaultXPos     = 32;
    const int mDefaultYPos     = 128;
    const int mDefaultFontSize = 56;
};
