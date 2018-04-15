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

public:
    CheckBox(COORD pos) : position(pos){
        this->bg = 0;
        this->fg = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        this->IsChecked = false;
    };

    COORD getPosition() {
        return position;
    }

    void setChecked(bool checked) {
        this->IsChecked = checked;
    }

    bool getChecked() {
        return this->IsChecked;
    }

    void draw();
public:
    CheckBox();
    ~CheckBox();
};

