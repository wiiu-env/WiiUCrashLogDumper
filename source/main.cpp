#include "Gfx.hpp"
#include "input/CombinedInput.h"
#include "input/VPADInput.h"
#include "input/WPADInput.h"
#include "screens/MainScreen.hpp"
#include "utils/logger.h"
#include <coreinit/title.h>
#include <memory>
#include <padscore/kpad.h>
#include <sndcore2/core.h>
#include <sysapp/launch.h>
#include <whb/proc.h>

inline bool RunningFromMiiMaker() {
    return (OSGetTitleID() & 0xFFFFFFFFFFFFF0FFull) == 0x000500101004A000ull;
}

int main(int argc, char const *argv[]) {
    initLogging();
    WHBProcInit();

    // call AXInit to stop already playing sounds
    AXInit();
    AXQuit();

    KPADInit();
    WPADEnableURCC(TRUE);

    Gfx::Init();

    std::unique_ptr<Screen> mainScreen = std::make_unique<MainScreen>();

    CombinedInput baseInput;
    VPadInput vpadInput;
    WPADInput wpadInputs[4] = {
            WPAD_CHAN_0,
            WPAD_CHAN_1,
            WPAD_CHAN_2,
            WPAD_CHAN_3};

    while (WHBProcIsRunning()) {
        baseInput.reset();
        if (vpadInput.update(1280, 720)) {
            baseInput.combine(vpadInput);
        }
        for (auto &wpadInput : wpadInputs) {
            if (wpadInput.update(1280, 720)) {
                baseInput.combine(wpadInput);
            }
        }
        baseInput.process();

        if (!mainScreen->Update(baseInput)) {
            // screen requested quit
            if (RunningFromMiiMaker()) {
                // legacy way, just quit
                break;
            } else {
                // launch menu otherwise
                SYSLaunchMenu();
            }
        }

        mainScreen->Draw();
        Gfx::Render();
    }

    mainScreen.reset();

    Gfx::Shutdown();

    WHBProcShutdown();
    deinitLogging();
    return 0;
}
