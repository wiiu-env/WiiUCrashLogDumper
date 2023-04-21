#pragma once
#include "version.h"

#define CRASH_LOG_DESTINATION_PATH "fs:/vol/external01/wiiu/crash_logs"
#define SLC_STORAGE_PATH           "storage_slc_wiiuident"
#define CRASH_LOG_SOURCE_PATH      SLC_STORAGE_PATH ":/sys/logs"

#define APP_VERSION                "v0.1"
#define APP_VERSION_FULL           APP_VERSION APP_VERSION_EXTRA