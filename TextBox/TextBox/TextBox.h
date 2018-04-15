#pragma once
#include <string>
#include <Windows.h>

using namespace std;

class TextBox
{
private:
    COORD position;
    int size;
    string text;
    DWORD bg;
    DWORD fg;

public:
    TextBox(int size, COORD pos) : position(pos) , size(size){
        this->bg = 0;
        this->fg = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    };

    string getValue() {
        return text;
    }

    int getSize() {
        return size;
    }

    COORD getPosition() {
        return position;
    }

    void setBackground(DWORD bg);
    void setForeground(DWORD fg);
    void setSize(int size);

    void draw();

    ~TextBox();
};

