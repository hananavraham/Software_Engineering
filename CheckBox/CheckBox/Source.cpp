#include "CheckBox.h"

int main(int argc, char** argv) {

    CheckBox t({ 10,10 });
    t.draw();

    while(1)
    {
        t.checkEvents();
    }
}