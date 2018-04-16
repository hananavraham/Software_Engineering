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

void TextBox::checkKeyEvent(HANDLE in)
{
    INPUT_RECORD ir;
    DWORD count = 1;
    ReadConsoleInput(in, &ir, 1, &count);
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    switch (ir.EventType)
    {
    case KEY_EVENT:
        if (ir.Event.KeyEvent.bKeyDown)
        {
            GetConsoleScreenBufferInfo(out, &info);
            if (ir.Event.KeyEvent.uChar.AsciiChar == 8)
            {
                if (info.dwCursorPosition.X - 1 == this->getPosition().X)    // if we trying to delete char but we in text border position
                    break;
                cout << '\x08';
                cout << '\x0';
            }

            else if (info.dwCursorPosition.X == this->getPosition().X + this->getSize())    // if we trying to exceed the textbox border
                break;

            cout << ir.Event.KeyEvent.uChar.AsciiChar;      // printing the selected key
        }



    }
}