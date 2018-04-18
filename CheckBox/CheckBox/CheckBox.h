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
    int boxes;
    int currentBox;
    bool *IsChecked;
    void CheckAndMark(HANDLE out, CONSOLE_SCREEN_BUFFER_INFO info , int BoxIndex);
    void SetCursorPosit(COORD point, HANDLE out, CONSOLE_SCREEN_BUFFER_INFO info);

public:
    CheckBox(COORD pos, int boxes) : position(pos) , boxes(boxes){
        this->IsChecked = new bool[this->boxes];
        this->bg = 0;
        this->fg = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        for (int i = 0 ; i < this->boxes ; ++i)
            this->IsChecked[i] = false;
        this->currentBox = 0;
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

