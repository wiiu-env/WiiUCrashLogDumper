#pragma once

#include "Screen.hpp"
#include <vector>

class AboutScreen : public Screen {
public:
    AboutScreen();

    ~AboutScreen() override;

    void Draw() override;

    bool Update(Input &input) override;

private:
    ScreenList creditList;
    ScreenList fontList;
    ScreenList linkList;
};
