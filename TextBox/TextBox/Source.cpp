#include <stdio.h>
#include "TextBox.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    TextBox t(30 , { 10,10 });
    t.setForeground(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    t.draw();

    HANDLE in = GetStdHandle(STD_INPUT_HANDLE);
    while (1) 
    {
        INPUT_RECORD ir;
        DWORD count = 1;
        ReadConsoleInput(in, &ir, 1, &count);
        switch (ir.EventType)
        {
            case KEY_EVENT:
                if (ir.Event.KeyEvent.bKeyDown)
                {                       
                    cout << ir.Event.KeyEvent.uChar.AsciiChar;
                }
                    
        }
    }




}