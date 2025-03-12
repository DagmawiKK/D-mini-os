#include "graphics.h"

int start() {
    ClearScreen(75.0f / 255.0f * 16.0f, 75.0f / 255.0f * 32.0f, 90.0f / 255.0f * 16.0f);
    char welcome[] = "Welcome to D-mini-OS!!\n\nhi!";
    char *p = welcome;

    DrawString(getMonospaceCharacter, font_monospace_width, font_monospace_height, p, 100, 100, 255, 255, 255);
    while(1);
}