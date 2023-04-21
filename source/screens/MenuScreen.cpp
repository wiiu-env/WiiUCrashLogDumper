#include "MenuScreen.hpp"
#include "AboutScreen.hpp"
#include "DumpLogsScreen.hpp"
#include "Gfx.hpp"

MenuScreen::MenuScreen()
    : mEntries({
              {MENU_ID_DUMP_LOGS, {0xf022, "Dump Logs"}},
              {MENU_ID_ABOUT, {0xf05a, "About WiiUCrashLogDumper"}},
      }) {}

MenuScreen::~MenuScreen() = default;

void MenuScreen::Draw() {
    if (mSubscreen) {
        mSubscreen->Draw();
        return;
    }

    DrawTopBar(nullptr);

    // draw entries
    for (MenuID id = MENU_ID_MIN; id <= MENU_ID_MAX;
         id        = static_cast<MenuID>(id + 1)) {
        int yOff = 75 + static_cast<int>(id) * 150;
        Gfx::DrawRectFilled(0, yOff, Gfx::SCREEN_WIDTH, 150, Gfx::COLOR_ALT_BACKGROUND);
        Gfx::DrawIcon(68, yOff + 150 / 2, 60, Gfx::COLOR_TEXT, mEntries[id].icon);
        Gfx::Print(128 + 8, yOff + 150 / 2, 60, Gfx::COLOR_TEXT, mEntries[id].name, Gfx::ALIGN_VERTICAL);

        if (id == mSelectedEntry) {
            Gfx::DrawRect(0, yOff, Gfx::SCREEN_WIDTH, 150, 8, Gfx::COLOR_HIGHLIGHTED);
        }
    }

    DrawBottomBar("\ue07d Navigate", "\ue044 Exit", "\ue000 Select");
}

bool MenuScreen::Update(Input &input) {
    if (mSubscreen) {
        if (!mSubscreen->Update(input)) {
            // subscreen wants to exit
            mSubscreen.reset();
        }
        return true;
    }

    if (input.data.buttons_d & Input::BUTTON_DOWN) {
        if (mSelectedEntry < MENU_ID_MAX) {
            mSelectedEntry = static_cast<MenuID>(mSelectedEntry + 1);
        }
    } else if (input.data.buttons_d & Input::BUTTON_UP) {
        if (mSelectedEntry > MENU_ID_MIN) {
            mSelectedEntry = static_cast<MenuID>(mSelectedEntry - 1);
        }
    }

    if (input.data.buttons_d & Input::BUTTON_A) {
        switch (mSelectedEntry) {
            case MENU_ID_DUMP_LOGS:
                mSubscreen = std::make_unique<DumpLogsScreen>();
                break;
            case MENU_ID_ABOUT:
                mSubscreen = std::make_unique<AboutScreen>();
                break;
        }
    }

    return true;
}
