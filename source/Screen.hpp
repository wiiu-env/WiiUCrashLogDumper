#pragma once

#include "input/Input.h"
#include <string>
#include <utility>
#include <vector>

class Screen {
public:
    Screen() = default;

    virtual ~Screen() = default;

    virtual void Draw() = 0;

    virtual bool Update(Input &input) = 0;

protected:
    static void DrawTopBar(const char *name);

    static void DrawBottomBar(const char *leftHint, const char *centerHint, const char *rightHint);

    static int DrawHeader(int x, int y, int w, uint16_t icon, const char *text);

    struct ScreenListElement {
        explicit ScreenListElement(std::string string, bool monospace = false) : string(std::move(string)), monospace(monospace) {}

        explicit ScreenListElement(const char *string, bool monospace = false) : string(string), monospace(monospace) {}

        std::string string;
        bool monospace;
    };

    using ScreenList = std::vector<std::pair<std::string, ScreenListElement>>;

    static int DrawList(int x, int y, int w, const ScreenList &items);

private:
};
