#include "MainScreen.hpp"
#include "Gfx.hpp"
#include "MenuScreen.hpp"
#include "common.h"
#include <mocha/mocha.h>
#include <utility>

MainScreen::~MainScreen() {
    if (mState > STATE_INIT_MOCHA) {
        Mocha_DeInitLibrary();
    }
}

void MainScreen::Draw() {
    Gfx::Clear(Gfx::COLOR_BACKGROUND);

    if (mMenuScreen) {
        mMenuScreen->Draw();
        return;
    }

    DrawTopBar(nullptr);

    switch (mState) {
        case STATE_INIT:
            break;
        case STATE_INIT_MOCHA:
            if (mStateFailure) {
                DrawStatus("Failed to initialize mocha!\nMake sure to update or install "
                           "Tiramisu/Aroma.",
                           Gfx::COLOR_ERROR);
                break;
            }

            DrawStatus("Initializing mocha...");
            break;
        case STATE_INIT_FS:
            if (mStateFailure) {
                DrawStatus("Failed to initialized File System!", Gfx::COLOR_ERROR);
                break;
            }
            DrawStatus("Initializing File System...");
            break;
        case STATE_LOAD_MENU:
            DrawStatus("Loading menu...");
            break;
        case STATE_IN_MENU:
            break;
    }

    DrawBottomBar(mStateFailure ? nullptr : "Please wait...", mStateFailure ? "\ue044 Exit" : nullptr, nullptr);
}

bool MainScreen::Update(Input &input) {
    if (mMenuScreen) {
        if (!mMenuScreen->Update(input)) {
            // menu wants to exit
            return false;
        }
        return true;
    }

    if (mStateFailure) {
        return true;
    }

    switch (mState) {
        case STATE_INIT:
            mState = STATE_INIT_MOCHA;
            break;
        case STATE_INIT_MOCHA: {
            MochaUtilsStatus status = Mocha_InitLibrary();
            if (status == MOCHA_RESULT_SUCCESS) {
                mState = STATE_INIT_FS;
                break;
            }

            mStateFailure = true;
            break;
        }
        case STATE_INIT_FS: {
            auto res = Mocha_MountFS(SLC_STORAGE_PATH, "/dev/slc01", "/vol/storage_slc01");
            if (res == MOCHA_RESULT_ALREADY_EXISTS) {
                res = Mocha_MountFS(SLC_STORAGE_PATH, nullptr, "/vol/storage_slc01");
            }
            if (res == MOCHA_RESULT_SUCCESS) {
                mState = STATE_LOAD_MENU;
                break;
            }

            mStateFailure = true;
            break;
        }
        case STATE_LOAD_MENU:
            mMenuScreen = std::make_unique<MenuScreen>();
            break;
        case STATE_IN_MENU:
            break;
    };

    return true;
}

void MainScreen::DrawStatus(std::string status, SDL_Color color) {
    Gfx::Print(Gfx::SCREEN_WIDTH / 2, Gfx::SCREEN_HEIGHT / 2, 64, color, std::move(status), Gfx::ALIGN_CENTER);
}
