#include "CheckBox.h"

#include <iostream>

CheckBox::CheckBox()
{
}

void CheckBox::draw()
{
    COORD pos = this->position;
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(out, &info);
    SetConsoleCursorPosition(out, this->position);
    SetConsoleTextAttribute(out, this->fg | this->bg);
    for (int i = 0; i < this->boxes; ++i)
    {
        cout << '\xDA';
        cout << '\xC4';
        cout << '\xBF';

        SetCursorPosit({ pos.X , pos.Y + 1}, out, info);

        cout << '\xB3';

        SetCursorPosit({ pos.X + 2 , pos.Y + 1}, out, info);

        cout << '\xB3';
        SetCursorPosit({ pos.X , pos.Y + 2}, out, info);

        cout << '\xC0';
        cout << '\xC4';
        cout << '\xD9';
        SetCursorPosit({ pos.X , pos.Y + 1}, out, info);

        pos = {pos.X , pos.Y + 3};
        SetCursorPosit(pos,out,info);
    }

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
                    CheckAndMark(out, info ,this->currentBox);
                }

                else if (ir.Event.KeyEvent.uChar.AsciiChar == 9)
                {
                    this->currentBox += 1;
                    if (this->currentBox >= this->boxes)
                    {
                        this->currentBox = 0;
                        SetCursorPosit({ this->position.X + 1, this->position.Y + 1 }, out, info);
                    }
                    
                    else    
                        SetCursorPosit({this->position.X +1, (SHORT)(this->position.Y + this-> currentBox * 3 +1)}, out,info);
                }
            }
            break;

        case MOUSE_EVENT:   // checking if left mouse button pressed
            COORD pos = this->position;
            if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
            {                
                for (int i = 0; i < this->boxes; ++i)
                {
                    if (ir.Event.MouseEvent.dwMousePosition.X == pos.X + 1 && ir.Event.MouseEvent.dwMousePosition.Y == pos.Y + 1)
                    {
                        CheckAndMark(out, info, i);
                    }
                    pos = { pos.X , pos.Y + 3 };
                }
            }
                
    }
}

// this function check if event happend inside the CheckBox
void CheckBox::CheckAndMark(HANDLE out, CONSOLE_SCREEN_BUFFER_INFO info , int BoxIndex)
{
    if (!this->IsChecked[BoxIndex])
    {
        SetCursorPosit({ this->position.X + 1 , (SHORT)(this->position.Y + BoxIndex * 3 + 1) }, out, info);
        cout << 'X';
        this->IsChecked[BoxIndex] = true;
        SetCursorPosit({ this->position.X + 1 , (SHORT)(this->position.Y + BoxIndex * 3 + 1) }, out , info);
    }
    else
    {
        SetCursorPosit({ this->position.X + 1 , (SHORT)(this->position.Y + BoxIndex * 3 + 1) }, out, info);
        cout << '\x20';
        this->IsChecked[BoxIndex] = false;
        SetCursorPosit({ this->position.X + 1 , (SHORT)(this->position.Y + BoxIndex * 3 + 1) }, out, info);
    }
    this->currentBox = BoxIndex;
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
