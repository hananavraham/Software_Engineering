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

    setCursorPosit({ this->position.X, this->position.Y + 1 }, out , info);

    cout << '\xB3';
    setCursorPosit({ this->position.X, this->position.Y + 2 }, out , info);

    for (int i = 0; i < this->size; ++i)
    {
        if (i == 0)
            cout << '\xC0';
        else
            cout << '\xC4';
    }

    cout << '\xD9';
    setCursorPosit({ this->position.X + (SHORT)this->size, this->position.Y + 1 }, out ,info);
    cout << '\xB3';
    setCursorPosit({ this->position.X + 1 ,this->position.Y + 1 }, out,info);

    SetConsoleTextAttribute(out, info.wAttributes);

    setCursorPosit({ this->position.X + 1 ,this->position.Y + 1 }, out, info);

}

void TextBox::checkKeyEvent()
{
    HANDLE in = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD ir;
    DWORD count , fdwMode;

    ReadConsoleInput(in, &ir, 1, &count);
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    SetConsoleMode(in, fdwMode);

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

            else if (ir.Event.KeyEvent.uChar.AsciiChar == '\x0D')      // if ENTER key pressed
                break;

            cout << ir.Event.KeyEvent.uChar.AsciiChar;      // printing the selected key
        }

        break;

    case MOUSE_EVENT:   
        if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)      // checking if Mouse Left Click 
        {   
            // checking if mouse pressed within textbox area
            if (ir.Event.MouseEvent.dwMousePosition.Y == this->position.Y + 1)
            {
                if (ir.Event.MouseEvent.dwMousePosition.X > this->position.X + 1 &&
                    ir.Event.MouseEvent.dwMousePosition.X < this->position.X + this->size - 1)
                {
                    setCursorPosit(ir.Event.MouseEvent.dwMousePosition, out, info);
                }
            }           
        }
    }
}

// this function set the cursorPosition
void TextBox::setCursorPosit(COORD point, HANDLE out, CONSOLE_SCREEN_BUFFER_INFO info)
{
    info.dwCursorPosition = point;
    SetConsoleCursorPosition(out, info.dwCursorPosition);
}
