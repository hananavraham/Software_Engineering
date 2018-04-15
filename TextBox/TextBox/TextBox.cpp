#include "TextBox.h"

#include <iostream>



TextBox::~TextBox()
{
}


void TextBox::setForeground(DWORD fg) {
    this->fg = fg;
}

void TextBox::setBackground(DWORD bg) {
    this->bg = bg;
}

void TextBox::setSize(int size) {
    this->size = size;
}

void TextBox::draw() {

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(out, &info);
    SetConsoleCursorPosition(out, this->position);
    SetConsoleTextAttribute(out, this->fg | this->bg);
    

    for (int i = 0; i < this->size; ++i)
    {
        if(i == 0)
            cout << '\xDA';
        else
            cout << '\xC4';
    }
    
    cout << '\xBF';

   
    info.dwCursorPosition = {this->position.X, this->position.Y +1};

    SetConsoleCursorPosition(out, info.dwCursorPosition);

    cout << '\xB3';
    info.dwCursorPosition = { this->position.X, this->position.Y +2};
    SetConsoleCursorPosition(out, info.dwCursorPosition);

    for (int i = 0; i < this->size; ++i)
    {
        if (i == 0)
            cout << '\xC0';
        else
            cout << '\xC4';
    }

    cout << '\xD9';

    info.dwCursorPosition = { this->position.X + (SHORT)this->size, this->position.Y +1};

    SetConsoleCursorPosition(out, info.dwCursorPosition);
    cout << '\xB3';

    SetConsoleCursorPosition(out, info.dwCursorPosition);

    info.dwCursorPosition = { this->position.X +1 ,this->position.Y +1 };
    SetConsoleTextAttribute(out, info.wAttributes);
    SetConsoleCursorPosition(out, info.dwCursorPosition);

}