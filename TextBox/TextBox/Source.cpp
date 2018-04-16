#include <stdio.h>
#include "TextBox.h"
#include <string>
#include <iostream>


using namespace std;

int main(int argc, char** argv) {

    TextBox t(30 , { 10,10 });
    t.setForeground(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    t.draw();
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    HANDLE in = GetStdHandle(STD_INPUT_HANDLE);
    while (1) 
    {
        t.checkKeyEvent(in);
        //INPUT_RECORD ir;
        
        //DWORD count = 1;
        //ReadConsoleInput(in, &ir, 1, &count);

        //switch (ir.EventType)
        //{
        //    case KEY_EVENT:
        //        if (ir.Event.KeyEvent.bKeyDown)
        //        {   
        //            GetConsoleScreenBufferInfo(out, &info);
        //            if (ir.Event.KeyEvent.uChar.AsciiChar == 8)
        //            {
        //                if (info.dwCursorPosition.X -1 == t.getPosition().X)    // if we trying to delete char but we in text border position
        //                    break;
        //                cout << '\x08';
        //                cout << '\x0';
        //            }

        //            else if(info.dwCursorPosition.X == t.getPosition().X + t.getSize())    // if we trying to exceed the textbox border
        //                break;

        //            cout << ir.Event.KeyEvent.uChar.AsciiChar;      // printing the selected key
        //        }

        //            

        //}
    }




}