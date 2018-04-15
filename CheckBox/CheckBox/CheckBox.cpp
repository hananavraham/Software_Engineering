#include "CheckBox.h"

#include <iostream>

CheckBox::CheckBox()
{
}


void CheckBox::draw()
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(out, &info);
    SetConsoleCursorPosition(out, this->position);
    SetConsoleTextAttribute(out, this->fg | this->bg);

    cout << '\xDA';
    cout << '\xC4';
    cout << '\xBF';

    info.dwCursorPosition = {this->position.X , this->position.Y +1};
    SetConsoleCursorPosition(out, info.dwCursorPosition);
    


    cout << '\xC0';
    cout << '\xC4';
    cout << '\xD9';

    info.dwCursorPosition = { this->position.X +1 , this->position.Y + 1 };
    SetConsoleCursorPosition(out, info.dwCursorPosition);



}


CheckBox::~CheckBox()
{
}
