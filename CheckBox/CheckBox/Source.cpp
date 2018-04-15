#include <string>
#include <iostream>

#include "CheckBox.h"

using namespace std;

int main(int argc, char** argv) {

    CheckBox t({ 10,10 });
    t.draw();

    HANDLE in = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD ir;
    while (1)
    {
        
        DWORD count;
        ReadConsoleInput(in, &ir, 1, &count);
        switch (ir.EventType)
        {
            case KEY_EVENT:
                if (ir.Event.KeyEvent.bKeyDown)
                {
                    if (ir.Event.KeyEvent.uChar.AsciiChar == 32)
                    {
                        if (!t.getChecked())
                        {
                            cout << 'X';
                            t.setChecked(true);
                        }

                        else
                            cout << '\x20';      
                    }
                }
                break;

            case MOUSE_EVENT:
               /* if(ir.Event.MouseEvent.dwButtonState)
                    cout << 'X';
                if (ir.Event.MouseEvent.dwMousePosition.X == t.getPosition().X)
                    if (ir.Event.MouseEvent.dwMousePosition.Y == t.getPosition().Y)
                        cout << 'X';*/
                if (ir.Event.MouseEvent.dwButtonState == MOUSEEVENTF_LEFTDOWN)
                    cout << 'X';
                
        }
    }
}