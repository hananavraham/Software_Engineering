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

    SetCursorPosit({ this->position.X , this->position.Y + 1 }, out, info);

    cout << '\xB3';

    SetCursorPosit({ this->position.X + 2 , this->position.Y + 1 }, out, info);

    cout << '\xB3';
    SetCursorPosit({ this->position.X , this->position.Y + 2 }, out, info);

    cout << '\xC0';
    cout << '\xC4';
    cout << '\xD9';
    SetCursorPosit({ this->position.X + 1 , this->position.Y + 1 }, out, info);

}

void CheckBox::checkEvents()
{
    HANDLE in = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD ir;
    DWORD count, fdwMode;
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(out, &info);
    fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    SetConsoleMode(in, fdwMode);
    ReadConsoleInput(in, &ir, 1, &count);
    switch (ir.EventType)
    {
        case KEY_EVENT:
            if (ir.Event.KeyEvent.bKeyDown)
            {
                if (ir.Event.KeyEvent.uChar.AsciiChar == 32)     // checking if its "Space" key
                {
                    CheckAndMark(out, info);
                }
            }
            break;

        case MOUSE_EVENT:   // checking if left mouse button pressed
            if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                if (ir.Event.MouseEvent.dwMousePosition.X == this->position.X + 1 &&
                    ir.Event.MouseEvent.dwMousePosition.Y == this->position.Y + 1)
                {
                    CheckAndMark(out, info);
                }
    }
}

// this function check if event happend inside the CheckBox
void CheckBox::CheckAndMark(HANDLE out, CONSOLE_SCREEN_BUFFER_INFO info)
{
    if (!this->IsChecked)
    {
        cout << 'X';
        this->IsChecked = true;
        SetCursorPosit({ this->position.X + 1 , this->position.Y + 1 }, out , info);
    }
    else
    {
        cout << '\x20';
        this->IsChecked = false;
        SetCursorPosit({ this->position.X + 1 , this->position.Y + 1 }, out, info);
    }
}

// this function set the cursorPosition
void CheckBox::SetCursorPosit(COORD point, HANDLE out, CONSOLE_SCREEN_BUFFER_INFO info)
{
    info.dwCursorPosition = point;
    SetConsoleCursorPosition(out,info.dwCursorPosition);
}

CheckBox::~CheckBox()
{
}
