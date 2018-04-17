#pragma once
#include <string>
#include <Windows.h>

using namespace std;

class CheckBox
{
private:
    COORD position;
    DWORD bg;
    DWORD fg;
    bool IsChecked;
    void CheckAndMark(HANDLE out, CONSOLE_SCREEN_BUFFER_INFO info);
    void SetCursorPosit(COORD point, HANDLE out, CONSOLE_SCREEN_BUFFER_INFO info);

public:
    CheckBox(COORD pos) : position(pos){
        this->bg = 0;
        this->fg = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        this->IsChecked = false;
    };

    COORD getPosition() {
        return position;
    }

    bool getChecked() {
        return this->IsChecked;
    }

    void draw();
    void checkEvents();

public:
    CheckBox();
    ~CheckBox();
};

