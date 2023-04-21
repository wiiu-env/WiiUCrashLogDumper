#pragma once

#include "Gfx.hpp"
#include "Screen.hpp"
#include <memory>

class MainScreen : public Screen {
public:
    MainScreen() = default;

    ~MainScreen() override;

    void Draw() override;

    bool Update(Input &input) override;

protected:
    static void DrawStatus(std::string status, SDL_Color color = Gfx::COLOR_TEXT);

private:
    enum {
        STATE_INIT,
        STATE_INIT_MOCHA,
        STATE_INIT_FS,
        STATE_LOAD_MENU,
        STATE_IN_MENU,
    } mState           = STATE_INIT;
    bool mStateFailure = false;

    std::unique_ptr<Screen> mMenuScreen;
};
