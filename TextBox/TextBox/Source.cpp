#include <stdio.h>
#include "TextBox.h"
#include <string>
#include <iostream>


using namespace std;

int main(int argc, char** argv) {

    TextBox t(30 , { 10,10 });
    t.setForeground(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    t.draw();

    while (1) 
    {
        t.checkKeyEvent();
    }

}